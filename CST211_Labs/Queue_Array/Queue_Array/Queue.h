/************************************************************************
* Author:		Garrett Fleischer
* Filename:		Queue.h
* Date Created:	1/29/16
* Modifications:
*
*************************************************************************/

#ifndef QUEUE_H
#define QUEUE_H

#include "crtdbg_new.h"

#include "Array.h"
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
*	Dequeue()		: T
*
*	Front()			: T
*
*	Size()			: int
*
*	MaxSize()		: int
*
*	isEmpty()		: bool
*
*	isFull()		: bool
*
*************************************************************************/
template<typename T>
class Queue
{
public:
	// CTORS AND DTOR
	Queue(int size = 0);
	Queue(const Queue & copy);

	~Queue();

	// OPERATORS
	Queue & operator=(const Queue & rhs);

	int Size() const;
	int MaxSize() const;
	bool isEmpty() const;
	bool isFull() const;

	void Enqueue(T item);
	T Dequeue();
	T & Front();
	const T & Front() const;

private:
	// MEMBERS
	Array<T> m_array;
	int m_size;
	int m_first;
	int m_last;

};


///////////////////////////////////////////////////////////////
//	C'TORS & D'TOR
//////

/************************************************************************
* Purpose: To initialize a queue with a given size
*
* Precondition:
*		size - must be non-negative
*
* Postcondition:
*		Modifies:	N/A
*		Throws:	Exception("Cannot initialize Queue with size less than zero!")
*		Returns:	N/A
*************************************************************************/
template<typename T>
Queue<T>::Queue(int size)
	: m_size(0), m_first(0), m_last(0)
{
	if (size < 0)
		throw Exception("Cannot initialize Queue with size less than zero!");

	m_array = Array<T>(size);
}

template<typename T>
Queue<T>::Queue(const Queue & copy)
	: m_array(copy.m_array), m_size(copy.m_size), m_first(copy.m_first), m_last(copy.m_last)
{}

template<typename T>
Queue<T>::~Queue()
{
	m_array.Purge();
	m_size = 0;
	m_first = 0;
	m_last = 0;
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
		m_array = rhs.m_array;
		m_size = rhs.m_size;
		m_first = rhs.m_first;
		m_last = rhs.m_last;
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
* Purpose: To get the current number of items on the queue
*
* Precondition:
*
* Postcondition:
*		Modifies:	N/A
*		Throws:		N/A
*		Returns:	The current number of items on the queue
*************************************************************************/
template<typename T>
int Queue<T>::Size() const
{
	return m_size;
}

/************************************************************************
* Purpose: To get the maximum number of items the queue can hold
*
* Precondition:
*
* Postcondition:
*		Modifies:	N/A
*		Throws:		N/A
*		Returns:	The the maximum number of items the queue can hold
*************************************************************************/
template<typename T>
int Queue<T>::MaxSize() const
{
	return m_array.Length();
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

/************************************************************************
* Purpose: To check if the number of items on the queue meets or exceeds
			the maximum number of items the queue can hold
*
* Precondition:
*
* Postcondition:
*		Modifies:	N/A
*		Throws:		N/A
*		Returns:	TRUE if the queue is full
*************************************************************************/
template<typename T>
bool Queue<T>::isFull() const
{
	return m_size >= m_array.Length();
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
*		The queue cannot be full
*
* Postcondition:
*		Modifies:	The queue itself, and the number of items on the queue
*		Throws:	Exception("Queue Overflow!");
*		Returns:	N/A
*************************************************************************/
template<typename T>
void Queue<T>::Enqueue(T item)
{
	if (isFull())
		throw Exception("Queue Overflow!");

	// don't worry about overwriting first as the exception prevents this
	if (m_last >= m_array.Length())
		m_last = 0;

	m_size++;
	m_array[m_last++] = item;
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

	// don't worry about overwriting last as the exception prevents this
	if (m_first >= m_array.Length())
		m_first = 0;

	m_size--;
	return m_array[m_first++];
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

	return m_array[m_first];
}

template<typename T>
const T & Queue<T>::Front() const
{
	if (isEmpty())
		throw Exception("Queue Underflow!");

	return m_array[m_first];
}

//////
//	END PUBLIC METHODS
///////////////////////////////////////////////////////////////


#endif // QUEUE_H
