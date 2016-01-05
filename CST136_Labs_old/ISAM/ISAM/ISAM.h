/*
@Author: Garrett Fleischer
@Date:	 10/18/15
*/

#ifndef ISAM_H
#define ISAM_H

#include <ios>
using std::ifstream;
using std::ofstream;


#include "ISAM_Block.h"

template<class T>
class ISAM
{
public:
	ISAM(ifstream & _file, stringstream * _output, int(*compare_type)(const T * _t1, const T * _t2),
		bool(*compare_key)(const T * _t, const string & _key), void(*display)(const T * _item));
	~ISAM();

private:
	// CONSTANTS
	static const int MAX_ITEMS_PER_BLOCK = 10;
	static const int MAX_BLOCKS = 15;

	// MEMBERS
	stringstream * m_output;
	Block<T> * m_blocks[MAX_BLOCKS];

	// MEMBER FUNCTION POINTERS
	int(*CompareType)(const T * _t1, const T * _t2);
	bool(*CompareKey)(const T * _t, const string & _key);
	void(*DisplayItem)(const T * _item);

	// MEMBER FUNCTIONS
	void ProcessFile(ifstream & _file);

	void ProcessCommand(char _command, string _arguments, bool & _programRunning);

	void Insert(T * _item);
	
	bool Delete(const string & _key);
	
	int QSearch(const T * _item);

	void Display(int start_index, int end_index);
	
	void Shift(int _index, bool _down);
};


template<class T>
ISAM<T>::ISAM(ifstream & _file, stringstream * _output, int(*compare_type)(const T * _t1, const T * _t2),
	bool(*compare_key)(const T * _t, const string & _key), void(*display)(const T * _item))
	: CompareType(compare_type), CompareKey(compare_key), DisplayItem(display), m_output(_output)
{
	for (int i = 0; i < MAX_BLOCKS; i++)
		m_blocks[i] = new Block<T>(CompareType, CompareKey);

	ProcessFile(_file);
}

template<class T>
ISAM<T>::~ISAM()
{
	for (int i = 0; i < MAX_BLOCKS; i++)
		delete m_blocks[i];
}

/////////////////////////////////////////////////////////
//	PRIVATE METHODS
//////////

template<class T>
void ISAM<T>::Insert(T * _item)
{
	int index_to_insert = QSearch(_item);

	if (m_blocks[index_to_insert]->Size() < MAX_ITEMS_PER_BLOCK)
		m_blocks[index_to_insert]->Insert(_item);
	else
	{
		if (m_blocks[index_to_insert + 1]->Size() < MAX_ITEMS_PER_BLOCK)
		{
			m_blocks[index_to_insert]->MoveTailNode(*(m_blocks[index_to_insert + 1]));
			m_blocks[index_to_insert]->Insert(_item);
		}
		else
		{
			// shift everything past index_to_insert down one space
			Shift(index_to_insert, true);

			// Attempt to insert _item again
			Insert(_item);
		}
	}
}

template<class T>
bool ISAM<T>::Delete(const string & _key)
{
	bool key_found = false;

	T * item_to_search_for = new T(_key, m_output);

	int index = QSearch(item_to_search_for);

	STATUS delete_status = m_blocks[index]->Delete(_key);

	if (delete_status == NORMAL)
	{
		key_found = true;

		if (m_blocks[index]->Size() == 0)
			Shift(index, false);
	}

	delete item_to_search_for;
	
	return key_found;
}

template<class T>
int ISAM<T>::QSearch(const T * _item)
{
	int index = 0;
	bool index_found = false;

	for (int i = 0; i < (MAX_BLOCKS - 1) && !index_found; ++i)
	{
		index = i;

		// if there is room in this block
		bool this_size = (m_blocks[i]->Size() < MAX_ITEMS_PER_BLOCK);
		
		const T * const this_item = m_blocks[i]->FirstItem();
		const T * const this_last = m_blocks[i]->LastItem();
		const T * const next_item = m_blocks[i + 1]->FirstItem();

		// compare _item with:
		int cmp_this = CompareType(_item, this_item);
		int cmp_last = CompareType(_item, this_last);
		int cmp_next = CompareType(_item, next_item);

		// if _item is greater than this_item and this_last exists and _item is less than this_last
		// or there is room in this block and next_item doesn't exist or _item is less than next_item
		if ((cmp_this >= 0 || i == 0) && ((this_last && cmp_last <= 0) || (this_size && (!next_item || cmp_next < 0))))
		{
			index_found = true;
		}
		else if (i > 0)
		{
			// compare _item with:
			int prev_last = CompareType(_item, m_blocks[i - 1]->LastItem());

			// if there is room in this block and _item is greater than prev_last
			// and _item is less than next_first or _item is less than this_first
			if ((prev_last > 0 && (cmp_next <= 0 || cmp_this < 0)))
				index_found = true;
		}
	}

	return index;
}

template<class T>
void ISAM<T>::ProcessFile(ifstream & _file)
{
	bool program_running = true;

	while (!_file.eof() && program_running)
	{
		char command[2];
		_file.read(command, 2); // read in the command, and the space

		string arguments;
		getline(_file, arguments);

		// process the command
		ProcessCommand(command[0], arguments, program_running);
		
	}
}

template<class T>
void ISAM<T>::ProcessCommand(char _command, string _arguments, bool & _programRunning)
{
	// COMMAND 'I'
	if (_command == 'I')
	{
		*m_output << "Inserting: " << _arguments << endl;

		Insert(new T(stringstream(_arguments), m_output));
	}

	// COMMAND 'R'
	else if (_command == 'R')
	{

		stringstream rows(_arguments);
		int start = 0;
		int end = 0;
		rows >> start >> end;

		if (start == end)
			*m_output << endl << "===================Displaying Row: " << start << "===================";
		else
			*m_output << endl << "=============Displaying Rows: " << start << " through " << end << "==============";

		Display(start, end);

		*m_output << "=======================================================" << endl;
	}

	// COMMAND 'S'
	else if (_command == 'S')
	{
		*m_output << endl << "Searching for: \"" << _arguments << "\"" << endl;

		T * item_to_search_for = new T(_arguments, m_output);

		int index = QSearch(item_to_search_for);
		int columnIndex = 0;

		T * const found = m_blocks[index]->Find(_arguments, columnIndex);
		if (found)
		{
			*m_output << "Found at: Element " << columnIndex << " of Row " << index << endl;
			DisplayItem(found);
		}
		else
			*m_output << "Unable to find \"" << _arguments << "\"..." << endl;

		*m_output << endl;

		delete item_to_search_for;
	}

	// COMMAND 'D'
	else if (_command == 'D')
	{
		*m_output << endl << "Deleting: \"" << _arguments << "\"" << endl;

		if (Delete(_arguments))
			*m_output << "Success!" << endl;
		else
			*m_output << "Failure!" << endl;

	}

	// COMMAND 'E'
	else if (_command == 'E')
	{
		*m_output << endl << "Program ending...\n" << endl;
		_programRunning = false;
	}

	// COMMAND ???
	else
	{
		*m_output << "\nInvalid Command: \"" << _command << "\"!\n" << endl;
	}
}

template<class T>
void ISAM<T>::Shift(int _index, bool _down)
{
	if (_down)
	{
		// delete the last Block in the list
		delete m_blocks[MAX_BLOCKS - 1];

		// move everything past _index down one space
		for (int i = (MAX_BLOCKS - 1); i > _index; --i)
			m_blocks[i] = m_blocks[i - 1];

		// fill in the gap at (index_to_insert + 1) with a new Block<T>
		m_blocks[_index + 1] = new Block<T>(CompareType, CompareKey);
	}
	else
	{
		// hold a temporary pointer to this block
		delete m_blocks[_index];

		// move everything past _index up one space
		for (int i = _index; i < (MAX_BLOCKS - 1); ++i)
			m_blocks[i] = m_blocks[i + 1];

		// fill in the gap at the end with the copied blank block
		m_blocks[MAX_BLOCKS - 1] = new Block<T>(CompareType, CompareKey);
	}
}


template<class T>
void ISAM<T>::Display(int start_index, int end_index)
{
	for (int i = start_index; i <= end_index; ++i)
	{
		*m_output << endl << "Row " << i << " contains: " << m_blocks[i]->Size() << " item" << ((m_blocks[i]->Size() != 1) ? "s" : "") << endl;
		m_blocks[i]->DisplayAll(DisplayItem);
		*m_output << endl;
	}
}

#endif // ISAM_H

