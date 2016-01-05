/*
@Author: Garrett Fleischer
@Date:	 10/18/15
*/

#ifndef ISAM_Block_h
#define ISAM_Block_h

#include "LinkedList.h"



/************************************************************************
* Class: Block<T>
*
* Purpose: This class acts as a wrapper around the LinkedList class
*			with a few convenience methods
*
* Manager functions:
* 	Block ()
*
*	~Block()
*
* Methods:
*	Public:
*		Insert(T * _item);
*		Delete(const string & _key);
*		Traverse(int start_index, int end_index, void(*Visit)(T * _item));
*		Find(const string & _key);
*		Size();
*	Private:
*		QSearch(const T * _item);
*		ShiftUp(int _index);
*		ShiftDown(int _index);
*************************************************************************/
template<class T>
class Block
{
public:
	template<class IT>
	friend class ISAMIterator;

	Block();
	~Block();


	void Insert(T * _data);

	STATUS Delete(const string & _key);
	
	void Traverse(void(*Visit)(T * _item));
	
	T * const Find(const string & _key, int & _foundIndex);
	
	int Size() { return m_list->Size(); }

	void MoveTailNode(Block & _to);
	void MoveHeadNode(Block & _to);

	const T * const FirstItem() { return (m_list->Head() ? m_list->Head()->data : nullptr); }
	const T * const LastItem() { return (m_list->Tail() ? m_list->Tail()->data : nullptr); }

private:
	LinkedList<T> * m_list;
};


/////////////////////////////////////////////////////////
//	C'tor and D'tor
//////////
	
	template<class T>
	Block<T>::Block()
	{
		m_list = new LinkedList<T>();
	}

	template<class T>
	Block<T>::~Block()
	{
		delete m_list;
	}

//////////
// END C'tor and D'tor
/////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////
//	PUBLIC METHODS
//////////

	/**********************************************************************
	* Wrapper around LinkedList::Insert()
	************************************************************************/
	template<class T>
	void Block<T>::Insert(T * _data)
	{
		m_list->Insert(_data);
	}


	/**********************************************************************
	* Wrapper around LinkedList::Delete()
	************************************************************************/
	template<class T>
	STATUS Block<T>::Delete(const string & _key)
	{
		return m_list->Delete(_key);
	}


	/**********************************************************************
	* Wrapper around LinkedList::Traverse()
	************************************************************************/
	template<class T>
	void Block<T>::Traverse(void(*Visit)(T * _item))
	{
		m_list->Traverse(Visit);
	}

	/**********************************************************************
	* Wrapper around LinkedList::Find()
	************************************************************************/
	template<class T>
	T * const Block<T>::Find(const string & _key, int & _foundIndex)
	{
		return m_list->Find(_key, _foundIndex);
	}


	/**********************************************************************
	* Purpose: This function Inserts a copy of this instance's tail node
	*			into another Block and deletes this tail node.
	*
	* Precondition:
	*		_to = the block to move the tail node to
	*
	* Postcondition:
	*		Returns N/A
	*
	************************************************************************/
	template<class T>
	void Block<T>::MoveTailNode(Block & _to)
	{
		_to.Insert(m_list->Tail()->data->Copy());
		m_list->Delete(m_list->Tail());
	}


	/**********************************************************************
	* Purpose: This function Inserts a copy of this instance's head node
	*			into another Block and deletes this head node.
	*
	* Precondition:
	*		_to = the block to move the head node to
	*
	* Postcondition:
	*		Returns N/A
	*
	************************************************************************/
	template<class T>
	void Block<T>::MoveHeadNode(Block & _to)
	{
		_to.Insert(m_list->Head()->data->Copy());
		m_list->Delete(m_list->Head());
	}

//////////
// END PUBLIC METHODS
/////////////////////////////////////////////////////////


#endif // ISAM_Block_h