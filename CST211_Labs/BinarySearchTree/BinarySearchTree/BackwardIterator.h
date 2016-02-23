/************************************************************************
* Author:		Garrett Fleischer
* Filename:		BackwardIterator.h
* Date Created:	2/20/16
* Modifications:
*	N/A
*************************************************************************/
#ifndef BACKWARDITERATOR_H
#define BACKWARDITERATOR_H

#include "ListIterator.h"


/************************************************************************
* Class: BackwardIterator
*
* Purpose: To iterate over all elements in a DoubleLinkedList starting from the end
*			and moving backward
*
* Manager functions:
* 	BackwardIterator ( )
*	BackwardIterator (const BackwardIterator & copy)
*	operator = (const BackwardIterator & rhs)
*
*	~BackwardIterator()
*
* Methods:
*	PUBLIC
*		Reset()			: void
*		MoveNext()		: void
*
*************************************************************************/
template<typename T>
class BackwardIterator : public ListIterator<T>
{
public:
	// CTORS & DTOR
	BackwardIterator(DoubleLinkedList<T> * list);
	BackwardIterator(const BackwardIterator<T> & copy);

	virtual ~BackwardIterator();

	// OPERATORS
	BackwardIterator<T> & operator=(const BackwardIterator<T> & rhs);

	// METHODS
	virtual void Reset();

	virtual void MoveNext();
};


///////////////////////////////////////////////////////////////
// C'TORS & D'TOR
//////

template<typename T>
BackwardIterator<T>::BackwardIterator(DoubleLinkedList<T> * list)
	: ListIterator(list)
{}

template<typename T>
BackwardIterator<T>::BackwardIterator(const BackwardIterator<T> & copy)
	: ListIterator(copy)
{}

template<typename T>
BackwardIterator<T>::~BackwardIterator()
{}

//////
// END C'TORS & D'TOR
///////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////
// OPERATORS
//////

template<typename T>
BackwardIterator<T>& BackwardIterator<T>::operator=(const BackwardIterator<T> & rhs)
{
	if (this != &rhs)
	{
		ListIterator::operator=(rhs);
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
* Purpose: To reset @m_current to the tail of the list
*
* Precondition:
*		@m_list : cannot be nullptr
*
* Postcondition:
*		Modifies:	N/A
*		Throws:		Exception("Error accessing non-existent list!")
*		Returns:	N/A
*************************************************************************/
template<typename T>
void BackwardIterator<T>::Reset()
{
	if (!m_list)
		throw Exception("Error accessing non-existent list!");

	m_current = m_list->m_tail;
}

/************************************************************************
* Purpose: To move @m_current to the "previous" item in the list
*
* Precondition:
*		IsDone() must return false
*
* Postcondition:
*		Modifies:	N/A
*		Throws:		Exception("Cannot access previous element! Iterator is done.")
*		Returns:	N/A
*************************************************************************/
template<typename T>
void BackwardIterator<T>::MoveNext()
{
	if (IsDone())
		throw Exception("Cannot access previous element! Iterator is done.");

	m_current = m_current->Prev();
}

//////
// END PUBLIC METHODS
///////////////////////////////////////////////////////////////

#endif // BACKWARDITERATOR_H