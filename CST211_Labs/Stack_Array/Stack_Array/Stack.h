/************************************************************************
* Author:		Garrett Fleischer
* Filename:		Stack.h
* Date Created:	1/29/16
* Modifications:
*
*************************************************************************/

#ifndef STACK_H
#define STACK_H

#include "crtdbg_new.h"

#include "Array.h"
#include "Exception.h"


/************************************************************************
* Class: Stack
*
* Purpose: This class creates a dynamic one-dimensional array that can be
* started at any base.
*
* Manager functions:
* 	Stack ( )
* 		The default size is zero.
*
*	Stack (const Stack & copy)
*	operator = (const Stack & copy)
*
*	~Stack()
*
* Methods:
*	operator [ ] (int index)
*		Returns the value located at index in the Array
*
*	Push(T item)	: void
*
*	Pop()			: T
*
*	Peek()			: T
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
class Stack
{
public:
	// CTORS AND DTOR
	Stack(int size = 0);
	Stack(const Stack & copy);

	~Stack();

	// OPERATORS
	Stack & operator=(const Stack & rhs);

	int Size() const;
	int MaxSize() const;
	bool isEmpty() const;
	bool isFull() const;

	void Push(T item);
	T Pop();
	T Peek() const;

private:
	// MEMBERS
	Array<T> m_array;
	int m_size;

};


///////////////////////////////////////////////////////////////
//	C'TORS & D'TOR
//////

template<typename T>
Stack<T>::Stack(int size)
	: m_array(size), m_size(0)
{
	if (size < 0)
		throw Exception("Cannot initialize Stack with size less than zero!");
}

template<typename T>
Stack<T>::Stack(const Stack & copy)
	: m_array(copy.m_array), m_size(copy.m_size)
{}

template<typename T>
Stack<T>::~Stack()
{
	m_array.Purge();
	m_size = 0;
}


//////
//	END C'TORS & D'TOR
///////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////
//	OPERATORS
//////

template<typename T>
Stack<T> & Stack<T>::operator=(const Stack & rhs)
{
	if (this != &rhs)
	{
		m_array = rhs.m_array;
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

template<typename T>
int Stack<T>::Size() const
{
	return m_size;
}

template<typename T>
int Stack<T>::MaxSize() const
{
	return m_array.Length();
}

template<typename T>
bool Stack<T>::isEmpty() const
{
	return m_size <= 0;
}

template<typename T>
bool Stack<T>::isFull() const
{
	return m_size >= m_array.Length();
}

//////
//	END GETTERS
///////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////
//	PUBLIC METHODS
//////

template<typename T>
void Stack<T>::Push(T item)
{
	if (isFull())
		throw Exception("Stack Overflow!");

	m_array[m_size++] = item;
}

template<typename T>
T Stack<T>::Pop()
{
	if(isEmpty())
		throw Exception("Stack Underflow!");

	return m_array[--m_size];
}

template<typename T>
T Stack<T>::Peek() const
{
	if (isEmpty())
		throw Exception("Stack Underflow!");

	return m_array[m_size - 1];
}

//////
//	END PUBLIC METHODS
///////////////////////////////////////////////////////////////


#endif // STACK_H
