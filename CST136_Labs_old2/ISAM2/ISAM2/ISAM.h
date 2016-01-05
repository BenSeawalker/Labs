/*
@Author: Garrett Fleischer
@Date:	 10/18/15
*/

#ifndef ISAM_H
#define ISAM_H

#include <ios>
using std::ifstream;
using std::ofstream;

#include <sstream>
using std::stringstream;

#include "ISAM_Block.h"


template<typename FT>
struct FoundItem
{
	FT * const item;
	int row;
	int column;

	FoundItem(FT * const _item, int _row, int _column)
		: item(_item), row(_row), column(_column) {}
};


/************************************************************************
* Class: ISAM<T>
*
* Purpose: This class stores data of type: T in an ISAM matrix
*
* Manager functions:
* 	ISAM (int(*compare_type)(T *, T *), bool(*compare_key)(T *, string &), stringstream * _output)
*		compare_type = how to compare two T pointers
*		compare_key = how to compare a T pointer with a string
*
*	~ISAM()
*
* Methods:
*	Public:
*		Insert(T * _item);
*		Delete(const string & _key);
*		Traverse(int start_index, int end_index, void(*Visit)(T * _item));
*		Find(const string & _key);
*	Private:
*		QSearch(const T * _item);
*		ShiftUp(int _index);
*		ShiftDown(int _index);
*************************************************************************/
template<class T>
class ISAM
{
public:
	ISAM(int(*compare_type)(const T * _t1, const T * _t2), int(*compare_key)(const T * _t, const string & _key), stringstream * _output);
	~ISAM();


	void Insert(T * _item);

	bool Delete(const string & _key);

	void Traverse(int start_index, int end_index, void(*Visit)(T * _item));

	FoundItem<T> * Find(const string & _key);

private:
	// CONSTANTS
	static const int MAX_ITEMS_PER_BLOCK = 10;
	static const int MAX_BLOCKS = 15;

	// MEMBERS
	Block<T> * m_blocks[MAX_BLOCKS];
	stringstream * m_output;

	// MEMBER FUNCTION POINTERS
	int(*CompareType)(const T * _t1, const T * _t2);
	int(*CompareKey)(const T * _t, const string & _key);

	// MEMBER FUNCTIONS
	int QSearch(const T * _item);
	int QSearch(const string & _key);
	
	void ShiftUp(int _index);
	void ShiftDown(int _index);
};


/////////////////////////////////////////////////////////
//	C'tor and D'tor
//////////

	template<class T>
	ISAM<T>::ISAM(int(*compare_type)(const T * _t1, const T * _t2),	int(*compare_key)(const T * _t, const string & _key), stringstream * _output)
		: CompareType(compare_type), CompareKey(compare_key), m_output(_output)
	{
		for (int i = 0; i < MAX_BLOCKS; i++)
			m_blocks[i] = new Block<T>(CompareType, CompareKey);
	}

	template<class T>
	ISAM<T>::~ISAM()
	{
		for (int i = 0; i < MAX_BLOCKS; i++)
			delete m_blocks[i];
	}

//////////
// END C'tor and D'tor
/////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////
//	PUBLIC METHODS
//////////

	/**********************************************************************
	* Purpose: This function uses QSearch() to find the correct row
	*			to insert the item. If the Block is full, it shifts
	*			subsequent Blocks down and inserts the item into a new row.
	*
	* Precondition:
	*     _item = the item to insert
	*
	* Postcondition:
	*		Returns N/A
	*		Modifies m_blocks
	*
	************************************************************************/
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
				ShiftDown(index_to_insert);

				// Attempt to insert _item again
				Insert(_item);
			}
		}
	}


	/**********************************************************************
	* Purpose: This function uses QSearch() to find the correct index
	*			to find the item. If the row is empty after deletion,
	*			it deletes the row and shifts subsequent Blocks up one space
	*			filling in the gap at the end with a new Block
	*
	* Precondition:
	*		_key = the string to match the item with
	*
	* Postcondition:
	*		Returns true if the item was successfully deleted
	*		Modifies m_blocks
	*
	************************************************************************/
	template<class T>
	bool ISAM<T>::Delete(const string & _key)
	{
		bool key_found = false;

		int index = QSearch(_key);

		STATUS delete_status = m_blocks[index]->Delete(_key);

		if (delete_status == NORMAL)
		{
			key_found = true;

			if (m_blocks[index]->Size() == 0)
				ShiftUp(index);
		}

		return key_found;
	}


	/**********************************************************************
	* Purpose: This function loops through rows start_index to end_index
	*			[Visit]ing all the items in each block
	*
	* Precondition:
	*		start_index = the row to begin traversing
	*		end_index	= the row to end traversing
	*		Visit		= the function to perform operations
	*					  on all items in each Block
	*
	* Postcondition:
	*		Returns N/A
	*
	************************************************************************/
	template<class T>
	void ISAM<T>::Traverse(int start_index, int end_index, void(*Visit)(T * _item))
	{
		for (int i = start_index; i <= end_index; ++i)
		{
			*m_output << endl << "Row " << i << " contains: " << m_blocks[i]->Size() << " item" << ((m_blocks[i]->Size() != 1) ? "s" : "") << endl;
			m_blocks[i]->Traverse(Visit);
			*m_output << endl;
		}
	}



	/**********************************************************************
	* Purpose: This function uses QSearch() to find the correct Block,
	*			then finds the matching item in the Block
	*
	* Precondition:
	*		_key = the string to match the item with
	*
	* Postcondition:
	*		Returns a FoundItem<T> instance containing the item,
	*				and the row and column it was found at.
	*
	************************************************************************/
	template<class T>
	FoundItem<T> * ISAM<T>::Find(const string & _key)
	{
		int row = QSearch(_key);
		int column = 0;

		T * const found_item = m_blocks[row]->Find(_key, column);

		return new FoundItem<T>(found_item, row, column);
	}




//////////
// END PUBLIC METHODS
/////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////
//	PRIVATE METHODS
//////////

	/**********************************************************************
	* Purpose: This function finds and returns the row in which _item can be found
	*
	* Precondition:
	*		_item = the instance to find the correct row for
	*
	* Postcondition:
	*		Returns the index of the Block in which _item can be found
	*
	************************************************************************/
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

			const T * const this_first = m_blocks[i]->FirstItem();
			const T * const this_last = m_blocks[i]->LastItem();
			const T * const next_first = m_blocks[i + 1]->FirstItem();

			// compare _item with:
			int cmp_this = CompareType(_item, this_first);
			int cmp_last = CompareType(_item, this_last);
			int cmp_next = CompareType(_item, next_first);

			// if _item is greater than this_item and this_last exists and _item is less than this_last
			// or there is room in this block and next_item doesn't exist or _item is less than next_item
			if ((cmp_this >= 0 || i == 0) && ((this_last && cmp_last <= 0) || (this_size && (!next_first || cmp_next < 0))))
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


	/**********************************************************************
	* Purpose: This function finds and returns the row in which 
	*			the item matching _key can be found
	*
	* Precondition:
	*		_key = the string to match the item with
	*
	* Postcondition:
	*		Returns the index of the Block in which _item can be found
	*
	************************************************************************/
	template<class T>
	int ISAM<T>::QSearch(const string & _key)
	{
		int index = 0;
		bool index_found = false;

		for (int i = 0; i < (MAX_BLOCKS - 1) && !index_found; ++i)
		{
			index = i;

			// if there is room in this block
			bool this_size = (m_blocks[i]->Size() < MAX_ITEMS_PER_BLOCK);

			const T * const this_first = m_blocks[i]->FirstItem();
			const T * const this_last = m_blocks[i]->LastItem();
			const T * const next_first = m_blocks[i + 1]->FirstItem();

			// compare _item with:
			int cmp_this = CompareKey(this_first, _key);
			int cmp_last = CompareKey(this_last, _key);
			int cmp_next = CompareKey(next_first, _key);

			// if _item is greater than this_item and this_last exists and _item is less than this_last
			// or there is room in this block and next_item doesn't exist or _item is less than next_item
			if ((cmp_this >= 0 || i == 0) && ((this_last && cmp_last <= 0) || (this_size && (!next_first || cmp_next < 0))))
			{
				index_found = true;
			}
			else if (i > 0)
			{
				// compare _item with:
				int prev_last = CompareKey(m_blocks[i - 1]->LastItem(), _key);

				// if there is room in this block and _item is greater than prev_last
				// and _item is less than next_first or _item is less than this_first
				if ((prev_last > 0 && (cmp_next <= 0 || cmp_this < 0)))
					index_found = true;
			}
		}

		return index;
	}


	/**********************************************************************
	* Purpose: This function deletes the Block at _index
	*			and shifts all subsequent Blocks up by one
	*			then creates a new block to fill the empty
				Block at the end of m_blocks[]
	*
	* Precondition:
	*		_index = the row where shifting must begin
	*
	* Postcondition:
	*		Returns N/A
	*		Modifies m_blocks
	*
	************************************************************************/
	template<class T>
	void ISAM<T>::ShiftUp(int _index)
	{
		// hold a temporary pointer to this block
		delete m_blocks[_index];

		// move everything past _index up one space
		for (int i = _index; i < (MAX_BLOCKS - 1); ++i)
			m_blocks[i] = m_blocks[i + 1];

		// fill in the gap at the end with the copied blank block
		m_blocks[MAX_BLOCKS - 1] = new Block<T>(CompareType, CompareKey);
	}


	/**********************************************************************
	* Purpose: This function deletes the Block at the end of m_blocks[]
	*			and shifts all Blocks starting at _index down by one
	*			then creates a new block to fill the empty block at _index
	*
	* Precondition:
	*		_index = the row where shifting must begin
	*
	* Postcondition:
	*		Returns N/A
	*		Modifies m_blocks
	*
	************************************************************************/
	template<class T>
	void ISAM<T>::ShiftDown(int _index)
	{
		// delete the last Block in the list
		delete m_blocks[MAX_BLOCKS - 1];

		// move everything past _index down one space
		for (int i = (MAX_BLOCKS - 1); i > _index; --i)
			m_blocks[i] = m_blocks[i - 1];

		// fill in the gap at (index_to_insert + 1) with a new Block<T>
		m_blocks[_index + 1] = new Block<T>(CompareType, CompareKey);
	}

//////////
// END PRIVATE METHODS
/////////////////////////////////////////////////////////

#endif // ISAM_H

