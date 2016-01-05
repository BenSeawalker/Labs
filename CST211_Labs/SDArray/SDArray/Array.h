/************************************************************************
* Author:		Garrett Fleischer
* Filename:		Array.h
* Date Created:	1/4/16
* Modifications:
*	N/A
*************************************************************************/

#ifndef ARRAY_H
#define ARRAY_H

#include "Exception.h"

#define MIN(arg1, arg2) ((arg1 <= arg2) ? arg1 : arg2)

/************************************************************************
* Class: Array
*
* Purpose: This class creates a dynamic one-dimensional array that can be
* started at any base.
*
* Manager functions:
* 	Array ( )
* 		The default size is zero and the base is zero.
*
*	Array (int length, int start_index = 0)
*		Creates an appropriate sized array with the starting index
*       either zero or the supplied starting value.
*
*	Array (const Array & copy)
*	operator = (const Array & copy)
*
*	~Array()
*
* Methods:
*	operator [ ] (int index)
*		Returns the value located at index in the Array
*
*************************************************************************/
template<typename T>
class Array
{
public:
	// CTOR'S & D'TOR
	Array();
	Array(int length, int start_index = 0);
	Array(const Array & copy);
	~Array();

	// OPERATORS
	Array<T> & operator=(const Array & rhs);
	T & operator[](int index) const;

	// GETTERS & SETTERS
	int getStartIndex() const;
	void setStartIndex(int index);
	
	int getLength() const;
	void setLength(int length);

private: 
	//	METHODS
	void CopyData(Array & dest, const Array & source);

	// MEMBERS
	T * m_array;
	int m_length;
	int m_startIndex;
};



///////////////////////////////////////////////////////////////
//	C'TORS & D'TOR
//////

template<typename T>
Array<T>::Array()
	: m_array(nullptr), m_length(0), m_startIndex(0)
{}

template<typename T>
Array<T>::Array(int length, int start_index)
	: m_array(nullptr), m_length(length), m_startIndex(start_index)
{
	m_array = new T[m_length];
}

template<typename T>
Array<T>::Array(const Array & copy)
	: m_array(nullptr), m_length(0), m_startIndex(0)
{
	*this = copy;
}

template<typename T>
Array<T>::~Array()
{
	delete[] m_array;
	m_array = nullptr;
	m_length = 0;
	m_startIndex = 0;
}

//////
//	END C'TORS & D'TOR
///////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////
//	OPERATORS
//////

template<typename T>
Array<T> & Array<T>::operator=(const Array & rhs)
{
	if (this != &rhs)
	{
		m_startIndex = rhs.getStartIndex();
		m_length = rhs.getLength();

		delete[] m_array;
		m_array = new T[m_length + 1];

		CopyData(*this, rhs);
	}

	return *this;
}


/************************************************************************
* Purpose: To easily access values stored in the Array
*
* Precondition:
*		index - must be within the bounds of the array
*
* Postcondition:
*		Modifies:	N/A
*		Throws:	Exception("index less than lower bound!")
				Exception("index greater than upper bound!")
*		Returns:	the value located at index
*************************************************************************/
template<typename T>
T & Array<T>::operator[](int index) const
{
	int delta = (index - m_startIndex);

	if (delta < 0)
		throw Exception("index less than lower bound!");
	else if (delta >= m_length)
		throw Exception("index greater than upper bound!");
		
	return m_array[delta];
}

//////
//	END OPERATORS
///////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////
//	GETTERS & SETTERS
//////

template<typename T>
int Array<T>::getStartIndex() const
{
	return m_startIndex;
}

template<typename T>
void Array<T>::setStartIndex(int index)
{
	m_startIndex = index;
}

template<typename T>
int Array<T>::getLength() const
{
	return m_length;
}

template<typename T>
void Array<T>::setLength(int length)
{
	if (length != m_length)
	{
		T * temp = new T[length + 1];
		
		// copy everything up to length
		for (size_t i = 0; i < length; ++i)
			temp[i] = m_array[i];

		delete[] m_array;
		m_array = temp;

		m_length = length;
	}
}

//////
//	END GETTERS & SETTERS
///////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////
//	PRIVATE METHODS
//////

/************************************************************************
* Purpose: Copies all data in the source Array to the dest Array
*
* Precondition:
*		dest - must have a size >= the size of the source Array
*
* Postcondition:
*		Modifies:	the elements of dest's templated array of values.
*		Returns:	N/A
*************************************************************************/
template<typename T>
void Array<T>::CopyData(Array & dest, const Array & source)
{
	size_t size = MIN(dest.getLength(), source.getLength());

	for (size_t i = 0; i < size; ++i)
		dest.m_array[i] = source.m_array[i];
}

//////
//	END PRIVATE METHODS
///////////////////////////////////////////////////////////////


#endif // ARRAY_H