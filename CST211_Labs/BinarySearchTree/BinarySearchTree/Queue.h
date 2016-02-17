/************************************************************************
* Author:		Garrett Fleischer
* Filename:		Queue.h
* Date Created:	1/29/16
* Modifications:
*
*************************************************************************/

#ifndef QUEUE_H
#define QUEUE_H

#include "DoubleLinkedList.h"
#include "Exception.h"


/************************************************************************
* Class: Queue
*
* Purpose: This class creates a dynamic one-dimensional array that can be
* started at any base.
*
* Manager functions:
* 	Queue ( )
* 		The default size is zero.
*
*	Queue (const Queue & copy)
*	operator = (const Queue & rhs)
*
*	~Queue()
*
* Methods:
*
*	Enqueue(T item)	: void
*
*	Dequeue()			: T
*
*	Front()			: T
*
*	Size()			: int
*
*	isEmpty()		: bool
*
*************************************************************************/
template<typename T>
class Queue
{
public:
	// CTORS AND DTOR
	Queue();
	Queue(const Queue & copy);

	~Queue();

	// OPERATORS
	Queue & operator=(const Queue & rhs);

	int Size() const;
	bool isEmpty() const;

	void Enqueue(T item);
	T Dequeue();

	T & Front();
	const T & Front() const;

private:
	// MEMBERS
	DoubleLinkedList<T> m_list;
	int m_size;

};


///////////////////////////////////////////////////////////////
//	C'TORS & D'TOR
//////

template<typename T>
Queue<T>::Queue()
	: m_size(0)
{}

template<typename T>
Queue<T>::Queue(const Queue & copy)
	: m_list(copy.m_list), m_size(copy.m_size)
{}

template<typename T>
Queue<T>::~Queue()
{
	m_list.Purge();
	m_size = 0;
}


//////
//	END C'TORS & D'TOR
///////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////
//	OPERATORS
//////

template<typename T>
Queue<T> & Queue<T>::operator=(const Queue & rhs)
{
	if (this != &rhs)
	{
		m_list = rhs.m_list;
		m_size = rhs.m_size;
	}

	return *this;
}

//////
//	END OPERATORS
///////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////
//	GETTERS
//////

/************************************************************************
* Purpose: To get the current number of items in the queue
*
* Precondition:
*
* Postcondition:
*		Modifies:	N/A
*		Throws:		N/A
*		Returns:	The current number of items in the queue
*************************************************************************/
template<typename T>
int Queue<T>::Size() const
{
	return m_size;
}

/************************************************************************
* Purpose: To check if there are no items on the queue
*
* Precondition:
*
* Postcondition:
*		Modifies:	N/A
*		Throws:		N/A
*		Returns:	TRUE if the queue is empty
*************************************************************************/
template<typename T>
bool Queue<T>::isEmpty() const
{
	return m_size <= 0;
}

//////
//	END GETTERS
///////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////
//	PUBLIC METHODS
//////

/************************************************************************
* Purpose: To push a new item on top of the queue
*
* Precondition:
*
* Postcondition:
*		Modifies:	The queue itself, and the number of items on the queue
*		Throws:		N/A
*		Returns:	N/A
*************************************************************************/
template<typename T>
void Queue<T>::Enqueue(T item)
{
	m_list.Append(item);
	m_size++;
}

/************************************************************************
* Purpose: To remove an item off the top of the queue and return it
*
* Precondition:
*		The queue cannot be empty
*
* Postcondition:
*		Modifies:	The queue itself, and the number of items on the queue
*		Throws:	Exception("Queue Underflow!")
*		Returns:	The item that was removed from the top of the queue by value
*************************************************************************/
template<typename T>
T Queue<T>::Dequeue()
{
	if(isEmpty())
		throw Exception("Queue Underflow!");

	T first = m_list.First();
	m_list.Extract(first);
	m_size--;

	return first;
}

/************************************************************************
* Purpose: To look at the item on the top of the queue
*
* Precondition:
*		The queue cannot be empty
*
* Postcondition:
*		Modifies:	N/A
*		Throws:	Exception("Queue Underflow!")
*		Returns:	The item on top of the queue by value
*************************************************************************/
template<typename T>
T & Queue<T>::Front()
{
	if (isEmpty())
		throw Exception("Queue Underflow!");

	return m_list.First();
}

template<typename T>
const T & Queue<T>::Front() const
{
	if (isEmpty())
		throw Exception("Queue Underflow!");

	return m_list.First();
}

//////
//	END PUBLIC METHODS
///////////////////////////////////////////////////////////////


#endif // QUEUE_H
