/*************************************************************
* Author:		Garrett Fleischer
* Filename:		Array.h
* Date Created:	1/4/16
* Modifications:
*	N/A
**************************************************************/

#ifndef Array_h__
#define Array_h__

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
public: // CTOR'S & D'TOR
	Array();
	Array(int length, int start_index = 0);
	Array(const Array & copy);
	~Array();

public: // OPERATORS
	Array & operator=(const Array &copy);
	T & operator[](int index) const;

public: // GETTERS & SETTERS
	int getStartIndex();
	void setStartIndex(int index);
	
	void getLength();
	void setLength(int length);

private: //	METHODS
	void CopyData(Array & dest, const Array & source);

private: // MEMBERS
	T * m_array;
	int m_length;
	int m_startIndex;
};



////////////////////////////////////////////////////////////
//	C'TORS & D'TOR
//////

template<typename T>
Array<T>::Array()
	: m_array(nullptr), m_length(0), m_startIndex(0)
{}

template<typename T>
Array<T>::Array(int length, int start_index)
	: m_length(length), m_startIndex(start_index)
{
	m_array = new T[m_length];
}

template<typename T>
Array<T>::Array(const Array & copy)
{
	*this = copy;
}

template<typename T>
Array<T>::~Array()
{
	delete[] m_array;
}

//////
//	END C'TORS & D'TOR
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
//	OPERATORS
//////

template<typename T>
Array & Array<T>::operator=(const Array & copy)
{
	m_startIndex = copy.getStartIndex();
	m_length = copy.getLength();

	delete[] m_array;
	m_array = new T[m_length];
	
	CopyData(*this, copy);

	return *this;
}


/**********************************************************************
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
************************************************************************/
template<typename T>
T & Array<T>::operator[](int index) const
{
	int delta = (index - m_startIndex);

	if (delta < 0)
		throw "index less than lower bound!";
	else if (delta >= m_length)
		throw "index greater than upper bound!";
		
	return m_array[delta];
}

//////
//	END OPERATORS
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
//	GETTERS & SETTERS
//////

template<typename T>
int Array<T>::getStartIndex()
{
	return m_startIndex;
}

template<typename T>
void Array<T>::setStartIndex(int index)
{
	m_startIndex = index;
}

template<typename T>
void Array<T>::getLength()
{
	return m_length;
}

template<typename T>
void Array<T>::setLength(int length)
{
	Array temp = Array(length, m_startIndex);

	CopyData(temp, *this);

	*this = temp;
}

//////
//	END GETTERS & SETTERS
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
//	PRIVATE METHODS
//////

/**********************************************************************
* Purpose: Copies all data in the source Array to the dest Array
*
* Precondition:
*		dest - must have a size >= the size of the source Array
*
* Postcondition:
*		Modifies:	the elements of dest's templated array of values.
*		Returns:	N/A
************************************************************************/
template<typename T>
void Array<T>::CopyData(Array & dest, const Array & source)
{
	for (size_t i = 0; i < source.getLength(); ++i)
		dest[i] = source[i];
}

//////
//	END PRIVATE METHODS
////////////////////////////////////////////////////////////


#endif // Array_h__