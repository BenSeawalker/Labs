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

#include "DoubleLinkedList.h"
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
*	operator = (const Stack & rhs)
*
*	~Stack()
*
* Methods:
*
*	Push(T item)	: void
*
*	Pop()			: T
*
*	Peek()			: T
*
*	Size()			: int
*
*	isEmpty()		: bool
*
*************************************************************************/
template<typename T>
class Stack
{
public:
	// CTORS AND DTOR
	Stack();
	Stack(const Stack & copy);

	~Stack();

	// OPERATORS
	Stack & operator=(const Stack & rhs);

	int Size() const;
	bool isEmpty() const;

	void Push(T item);
	T Pop();
	T Peek() const;

private:
	// MEMBERS
	DoubleLinkedList<T> m_list;
	int m_size;

};


///////////////////////////////////////////////////////////////
//	C'TORS & D'TOR
//////

template<typename T>
Stack<T>::Stack()
	: m_size(0)
{}

template<typename T>
Stack<T>::Stack(const Stack & copy)
	: m_list(copy.m_list), m_size(copy.m_size)
{}

template<typename T>
Stack<T>::~Stack()
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
Stack<T> & Stack<T>::operator=(const Stack & rhs)
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
* Purpose: To get the current number of items on the stack
*
* Precondition:
*
* Postcondition:
*		Modifies:	N/A
*		Throws:		N/A
*		Returns:	The current number of items on the stack
*************************************************************************/
template<typename T>
int Stack<T>::Size() const
{
	return m_size;
}

/************************************************************************
* Purpose: To check if there are no items on the stack
*
* Precondition:
*
* Postcondition:
*		Modifies:	N/A
*		Throws:		N/A
*		Returns:	TRUE if the stack is empty
*************************************************************************/
template<typename T>
bool Stack<T>::isEmpty() const
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
* Purpose: To push a new item on top of the stack
*
* Precondition:
*
* Postcondition:
*		Modifies:	The stack itself, and the number of items on the stack
*		Throws:		N/A
*		Returns:	N/A
*************************************************************************/
template<typename T>
void Stack<T>::Push(T item)
{
	m_list.Prepend(item);
	m_size++;
}

/************************************************************************
* Purpose: To remove an item off the top of the stack and return it
*
* Precondition:
*		The stack cannot be empty
*
* Postcondition:
*		Modifies:	The stack itself, and the number of items on the stack
*		Throws:	Exception("Stack Underflow!")
*		Returns:	The item that was removed from the top of the stack by value
*************************************************************************/
template<typename T>
T Stack<T>::Pop()
{
	if(isEmpty())
		throw Exception("Stack Underflow!");

	T first = m_list.First();
	m_list.Extract(first);
	m_size--;

	return first;
}

/************************************************************************
* Purpose: To look at the item on the top of the stack
*
* Precondition:
*		The stack cannot be empty
*
* Postcondition:
*		Modifies:	N/A
*		Throws:	Exception("Stack Underflow!")
*		Returns:	The item on top of the stack by value
*************************************************************************/
template<typename T>
T Stack<T>::Peek() const
{
	if (isEmpty())
		throw Exception("Stack Underflow!");

	return m_list.First();
}

//////
//	END PUBLIC METHODS
///////////////////////////////////////////////////////////////


#endif // STACK_H
