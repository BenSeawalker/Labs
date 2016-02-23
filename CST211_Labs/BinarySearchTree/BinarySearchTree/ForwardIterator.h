/************************************************************************
* Author:		Garrett Fleischer
* Filename:		ForwardIterator.h
* Date Created:	2/20/16
* Modifications:
*	N/A
*************************************************************************/
#ifndef FORWARDITERATOR_H
#define FORWARDITERATOR_H

#include "ListIterator.h"


/************************************************************************
* Class: ForwardIterator
*
* Purpose: To iterate over all elements in a DoubleLinkedList starting from the beginning
*			and moving forward
*
* Manager functions:
* 	ForwardIterator ( )
*	ForwardIterator (const ForwardIterator & copy)
*	operator = (const ForwardIterator & rhs)
*
*	~ForwardIterator()
*
* Methods:
*	(passthrough, as ListIterator moves forward by default)
*
*************************************************************************/
template<typename T>
class ForwardIterator : public ListIterator<T>
{
public:
	// CTORS & DTOR
	ForwardIterator(DoubleLinkedList<T> * list);
	ForwardIterator(const ForwardIterator & copy);

	virtual ~ForwardIterator();

	// OPERATORS
	ForwardIterator<T> & operator=(const ForwardIterator & rhs);
};


///////////////////////////////////////////////////////////////
// C'TORS & D'TOR
//////

template<typename T>
ForwardIterator<T>::ForwardIterator(DoubleLinkedList<T> * list)
	: ListIterator(list)
{}

template<typename T>
ForwardIterator<T>::ForwardIterator(const ForwardIterator<T> & copy)
	: ListIterator(copy)
{}

template<typename T>
ForwardIterator<T>::~ForwardIterator()
{}

//////
// END C'TORS & D'TOR
///////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////
// OPERATORS
//////

template<typename T>
ForwardIterator<T> & ForwardIterator<T>::operator=(const ForwardIterator<T> & rhs)
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

#endif // FORWARDITERATOR_H