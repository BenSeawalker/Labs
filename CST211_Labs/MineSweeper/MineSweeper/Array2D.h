/************************************************************************
* Author:		Garrett Fleischer
* Filename:		Array2D.h
* Date Created:	1/6/16
* Modifications:
*	1/12/16 - Fixed constness of operator[]
*			- Fixed constness of Select()
*************************************************************************/
#ifndef ARRAY2D_H
#define ARRAY2D_H

#include "Array.h"


/************************************************************************
* Class: Array2D
*
* Purpose: This class provides two dimensional functionality using a single dimensional Array.
*
* Manager functions:
* 	Array2D (int rows = 0, int columns = 0 )
*
*	Array2D (const Array2D & copy)
*	operator = (const Array2D & rhs)
*
*	~Array2D()
*
* Methods:
*	operator [ ] (int row)
*		Returns an instance of Row which has operator [ ] (int column)
*
*	Rows()
*	SetRows ( int rows )
*	Columns()
*	SetColumns ( int columns )
*	SetSize ( int rows, int columns )
*
*	Select ( int row, int column )
*	Contains( int row, int column )
*	Purge()
*
*************************************************************************/
template<typename T>
class Array2D
{
	template<typename AT>
	friend class Row;

public:
	// C'TORS AND D'TOR
	Array2D(int rows = 0, int columns = 0);
	Array2D(const Array2D<T> & copy);

	~Array2D();

	// OPERATORS
	Array2D<T> & operator=(const Array2D<T> & rhs);
	const Row<T> operator[](int row) const;
	Row<T> operator[](int row);

	// GETTERS AND SETTERS
	int Rows() const;
	void SetRows(int rows);

	int Columns() const;
	void SetColumns(int columns);

	void SetSize(int rows, int columns);

	// METHODS
	const T & Select(int row, int column) const;
	T & Select(int row, int column);

	bool Contains(int row, int column) const;

	void Purge();

private:
	// MEMBERS
	Array<T> m_array;
	int m_rows;
	int m_columns;
};


/////////////////////////////////////////////////////////
// C'TORS & D'TOR
//////

template<typename T>
Array2D<T>::Array2D(int rows, int columns)
	: m_rows(rows), m_columns(columns), m_array(rows * columns)
{}

template<typename T>
Array2D<T>::Array2D(const Array2D<T> & copy)
	: m_rows(copy.m_rows), m_columns(copy.m_columns), m_array(copy.m_array)
{}

template<typename T>
Array2D<T>::~Array2D()
{}

//////
// END C'TORS AND D'TOR
/////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////
// OPERATORS
//////

template<typename T>
Array2D<T> & Array2D<T>::operator=(const Array2D<T> & rhs)
{
	m_rows = rhs.m_rows;
	m_columns = rhs.m_columns;
	m_array = rhs.m_array;

	return *this;
}

/************************************************************************
* Purpose: To easily access a Row in the Array
*
* Precondition:
*		row - must be within the bounds of the array
*
* Postcondition:
*		Modifies:	N/A
*		Throws:	Exception("Row index out of bounds!")
*		Returns:	the Row located at index
*************************************************************************/
template<typename T>
Row<T> Array2D<T>::operator[](int row)
{
	if (row < 0 || row >= m_rows)
		throw Exception("Row index out of bounds!");

	return Row<T>(*this, row);
}

/************************************************************************
* Purpose: To easily access a Row in a const Array
*
* Precondition:
*		row - must be within the bounds of the array
*
* Postcondition:
*		Modifies:	N/A
*		Throws:	Exception("Row index out of bounds!")
*		Returns:	the Row located at index
*************************************************************************/
template<typename T>
const Row<T> Array2D<T>::operator[](int row) const
{
	if (row < 0 || row >= m_rows)
		throw Exception("Row index out of bounds!");

	return Row<T>(*this, row);
}

//////
// END OPERATORS
/////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////
// SETTERS AND GETTERS
//////

template<typename T>
int Array2D<T>::Rows() const
{
	return m_rows;
}

/************************************************************************
* Purpose: To set the number of rows in the Array
*
* Precondition:
*		rows - must be greater than zero
*
* Postcondition:
*		Modifies:	The length of the Array
*		Throws:	Exception("Error: Cannot set rows to a value less than zero!")
*		Returns:	N/A
*************************************************************************/
template<typename T>
void Array2D<T>::SetRows(int rows)
{
	if (rows < 0)
		throw Exception("Error: Cannot set rows to a value less than zero!");

	if (rows != m_rows)
	{
		m_rows = rows;
		m_array.SetLength(rows * m_columns);
	}
}

template<typename T>
int Array2D<T>::Columns() const
{
	return m_columns;
}

/************************************************************************
* Purpose: To set the number of columns in the Array
*
* Precondition:
*		columns - must be greater than zero
*
* Postcondition:
*		Modifies:	The length of the Array,
*					and the indexes at which the values are stored
*		Throws:	Exception("Error: Cannot set columns to a value less than zero!")
*		Returns:	N/A
*************************************************************************/
template<typename T>
void Array2D<T>::SetColumns(int columns)
{
	if (columns < 0)
		throw Exception("Error: Cannot set columns to a value less than zero!");

	if (columns != m_columns)
	{
		// create a temporary array with the new size
		Array<T> temp(m_rows * columns);
		int cols = MIN(m_columns, columns);
		int new_row = 0;
		int new_index;

		// starting at the beginning
		// jump to the first item of each row
		for (int row = 0; row < m_array.Length(); row += m_columns)
		{
			// move each item in the column to their new index
			for (int i = row; i < (row + cols); ++i)
			{
				new_index = (new_row + (i - row));
				temp[new_index] = m_array[i];
			}

			// shift new_row to the next row
			new_row += columns;
		}

		m_array = temp;
		m_columns = columns;
	}
}

template<typename T>
void Array2D<T>::SetSize(int rows, int columns)
{
	SetRows(rows);
	SetColumns(columns);
}

//////
// END SETTERS AND GETTERS
/////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////
// PUBLIC METHODS
//////

template<typename T>
T & Array2D<T>::Select(int row, int column)
{
	if (row < 0 || row >= m_rows)
		throw Exception("Row index out of bounds!");
	else if (column < 0 || column >= m_columns)
		throw Exception("Column index out of bounds!");

	int index = ((row * m_columns) + column);
	return m_array[index];
}

/************************************************************************
* Purpose: To grab an item in the array
*
* Precondition:
*		row		- must be within the bounds of the array
*		column	- must be within the bounds of the array
*
* Postcondition:
*		Modifies:	N/A
*		Throws:	Exception("Row index out of bounds!")
Exception("Column index out of bounds!")
*		Returns:	The specified item by reference
*************************************************************************/
template<typename T>
const T & Array2D<T>::Select(int row, int column) const
{
	if (row < 0 || row >= m_rows)
		throw Exception("Row index out of bounds!");
	else if (column < 0 || column >= m_columns)
		throw Exception("Column index out of bounds!");

	int index = ((row * m_columns) + column);
	return m_array[index];
}

/************************************************************************
* Purpose: To determine if a specified row and column
*		   are within the bounds of the array
*
* Precondition:
*
* Postcondition:
*		Modifies:	N/A
*		Throws:		N/A
*		Returns:	TRUE if row and column are within the bounds of the array
*************************************************************************/
template<typename T>
bool Array2D<T>::Contains(int row, int column) const
{
	return ((row >= 0 && row < m_rows) && (column >= 0 && column < m_columns));
}

template<typename T>
void Array2D<T>::Purge()
{
	m_array = Array<T>();
	m_rows = 0;
	m_columns = 0;
}

//////
// END PUBLIC METHODS
/////////////////////////////////////////////////////////

#endif // ARRAY2D_H