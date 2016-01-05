/*
@Author: Garrett Fleischer
@Date:	 10/18/15
*/

#ifndef ISAM_H
#define ISAM_H

#include <sstream>
using std::stringstream;

#include "ISAMBlock.h"


/************************************************************************
* Class: ISAM<T, KT>
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
template<typename T, typename KT>
class ISAM
{
public:
	template<typename IT, typename IKT>
	friend class ISAMIterator;

	ISAM(stringstream * _output);
	~ISAM();


	void Insert(T * _item);

	bool Delete(const KT & _key);

	void Traverse(int start_index, int end_index, void(*Visit)(T * _item));

	T * const Find(const KT & _key, int & _row, int & _column);

private:
	// CONSTANTS
	static const int MAX_ITEMS_PER_BLOCK = 10;
	static const int MAX_BLOCKS = 15;

	// MEMBERS
	ISAMBlock<T, KT> * m_blocks[MAX_BLOCKS];
	stringstream * m_output;

	// MEMBER FUNCTIONS
	int QSearchItem(const T * _item);
	int QSearchKey(const KT & _key);
	
	void ShiftUp(int _index);
	void ShiftDown(int _index);
};


/////////////////////////////////////////////////////////
//	C'tor and D'tor
//////////

	template<typename T, typename KT>
	ISAM<T, KT>::ISAM(stringstream * _output)
		: m_output(_output)
	{
		for (int i = 0; i < MAX_BLOCKS; ++i)
			m_blocks[i] = new ISAMBlock<T, KT>;
	}

	template<typename T, typename KT>
	ISAM<T, KT>::~ISAM()
	{
		for (int i = 0; i < MAX_BLOCKS; ++i)
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
	template<typename T, typename KT>
	void ISAM<T, KT>::Insert(T * _item)
	{
		int index_to_insert = QSearchItem(_item);

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
	template<typename T, typename KT>
	bool ISAM<T, KT>::Delete(const KT & _key)
	{
		bool key_found = false;

		int index = QSearchKey(_key);

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
	template<typename T, typename KT>
	void ISAM<T, KT>::Traverse(int start_index, int end_index, void(*Visit)(T * _item))
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
	template<typename T, typename KT>
	T * const ISAM<T, KT>::Find(const KT & _key, int & _row, int & _column)
	{
		_row = QSearchKey(_key);
		_column = 0;

		T * const found_item = m_blocks[_row]->Find(_key, _column);

		return found_item;
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
	template<typename T, typename KT>
	int ISAM<T, KT>::QSearchItem(const T * _item)
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

			if ((!this_first || *_item >= *this_first || i == 0) && ((this_last && *_item <= *this_last) || (this_size && (!next_first || *_item < *next_first))))
			{
				index_found = true;
			}
			else if (i > 0)
			{
				const T * const prev_last = m_blocks[i - 1]->LastItem();

				if (prev_last && ((*_item > *prev_last) && ((next_first && (*_item <= *next_first)) || (this_last && (*_item <= *this_last)) || *_item < *this_first)))
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
	template<typename T, typename KT>
	int ISAM<T, KT>::QSearchKey(const KT & _key)
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

			if ((!this_first || *this_first <= _key || i == 0) && ((this_last && *this_last >= _key) || (this_size && (!next_first || *next_first > _key))))
			{
				index_found = true;
			}
			else if (i > 0)
			{
				const T * const prev_last = m_blocks[i - 1]->LastItem();

				if (prev_last && (*prev_last < _key && (*next_first >= _key || *this_first > _key)))
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
	template<typename T, typename KT>
	void ISAM<T, KT>::ShiftUp(int _index)
	{
		// hold a temporary pointer to this block
		delete m_blocks[_index];

		// move everything past _index up one space
		for (int i = _index; i < (MAX_BLOCKS - 1); ++i)
			m_blocks[i] = m_blocks[i + 1];

		// fill in the gap at the end with the copied blank block
		m_blocks[MAX_BLOCKS - 1] = new ISAMBlock<T, KT>();
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
	template<typename T, typename KT>
	void ISAM<T, KT>::ShiftDown(int _index)
	{
		// delete the last Block in the list
		delete m_blocks[MAX_BLOCKS - 1];

		// move everything past _index down one space
		for (int i = (MAX_BLOCKS - 1); i > _index; --i)
			m_blocks[i] = m_blocks[i - 1];

		// fill in the gap at (index_to_insert + 1) with a new ISAMBlock<T, KT>
		m_blocks[_index + 1] = new ISAMBlock<T, KT>();
	}

//////////
// END PRIVATE METHODS
/////////////////////////////////////////////////////////

#endif // ISAM_H

