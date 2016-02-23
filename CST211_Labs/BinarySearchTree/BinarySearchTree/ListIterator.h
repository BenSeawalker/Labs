/************************************************************************
* Author:		Garrett Fleischer
* Filename:		ListIterator.h
* Date Created:	2/20/16
* Modifications:
*	N/A
*************************************************************************/
#ifndef LISTITERATOR_H
#define LISTITERATOR_H

#include "AbstractIterator.h"
#include "DoubleLinkedList.h"
#include "ListNode.h"

/************************************************************************
* Class: ListIterator
*
* Purpose: To provide base functionality for iterating over all elements in a DoubleLinkedList
*			Default functionality is to start at the beginning and move forward
*
* Manager functions:
* 	ListIterator ( )
*	ListIterator (const ListIterator & copy)
*	operator = (const ListIterator & rhs)
*
*	~ListIterator()
*
* Methods:
*	PUBLIC
*		Reset()			: void
*		MoveNext()		: void
*		GetCurrent()	: T &
*		IsDone()		: void
*
*************************************************************************/
template<typename T>
class ListIterator : public AbstractIterator<T>
{
public:
	// DTOR
	~ListIterator();

	// METHODS
	virtual void Reset();

	virtual void MoveNext();

	virtual T & GetCurrent();

	virtual bool IsDone() const;

protected:
	// CTORS
	ListIterator(DoubleLinkedList<T> * list);
	ListIterator(const ListIterator & copy);

	// OPERATORS
	ListIterator & operator=(const ListIterator & rhs);

	// MEMBERS
	DoubleLinkedList<T> * m_list;
	ListNode<T> * m_current;
};


///////////////////////////////////////////////////////////////
// C'TORS & D'TOR
//////

template<typename T>
ListIterator<T>::ListIterator(DoubleLinkedList<T> * list)
	: m_list(list), m_current(list->m_head)
{}

template<typename T>
ListIterator<T>::ListIterator(const ListIterator & copy)
	: m_list(copy.m_list), m_current(copy.m_current)
{}

template<typename T>
ListIterator<T>::~ListIterator()
{
	m_list = nullptr;
	m_current = nullptr;
}

//////
// END C'TORS & D'TOR
///////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////
// OPERATORS
//////

template<typename T>
ListIterator<T> & ListIterator<T>::operator=(const ListIterator & rhs)
{
	if (this != &rhs)
	{
		m_list = rhs.m_list;
		m_current = rhs.m_current;
	}
	
	return *this;
}

//////
// END OPERATORS
///////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////
// PUBLIC METHODS
//////

/************************************************************************
* Purpose: To reset @m_current to the head of the list
*
* Precondition:
*		@m_list : cannot be nullptr
*
* Postcondition:
*		Modifies:	@m_current
*		Throws:		Exception("Error accessing non-existent list!")
*		Returns:	N/A
*************************************************************************/
template<typename T>
void ListIterator<T>::Reset()
{
	if (!m_list)
		throw Exception("Error accessing non-existent list!");

	m_current = m_list->m_head;
}

/************************************************************************
* Purpose: To move @m_current to the "next" item in the list
*
* Precondition:
*		IsDone() must return false
*
* Postcondition:
*		Modifies:	@m_current
*		Throws:		Exception("Cannot access next element! Iterator is done.")
*		Returns:	N/A
*************************************************************************/
template<typename T>
void ListIterator<T>::MoveNext()
{
	if (IsDone())
		throw Exception("Cannot access next element! Iterator is done.");

	m_current = m_current->Next();
}

/************************************************************************
* Purpose: To get the data stored at the current element
*
* Precondition:
*		IsDone() must return false
*
* Postcondition:
*		Modifies:	N/A
*		Throws:		Exception("Cannot access current element! Iterator is done.")
*		Returns:	N/A
*************************************************************************/
template<typename T>
T & ListIterator<T>::GetCurrent()
{
	if (IsDone())
		throw Exception("Cannot access current element! Iterator is done.");

	return m_current->Data();
}

/************************************************************************
* Purpose: To check if all the elements have been iterated over
*
* Precondition:
*		@m_current is equivalent to nullptr
*
* Postcondition:
*		Modifies:	N/A
*		Throws:		N/A
*		Returns:	TRUE if the iterator has finished
*************************************************************************/
template<typename T>
bool ListIterator<T>::IsDone() const
{
	return m_current == nullptr;
}

//////
// END PUBLIC METHODS
///////////////////////////////////////////////////////////////

#endif // LISTITERATOR_H

