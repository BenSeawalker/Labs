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
*************************************************************************/
template<typename T>
class Array2D
{
	template<typename AT>
	friend class Row;

public:
	// C'TORS AND D'TOR
	Array2D(int rows = 0, int cols = 0);
	Array2D(const Array2D<T> & copy);

	~Array2D();

	// OPERATORS
	Array2D<T> & operator=(const Array2D<T> & rhs);
	const Row<T> operator[](int row) const;

	// GETTERS AND SETTERS
	int getRows() const;
	void setRows(int rows);

	int getColumns() const;
	void setColumns(int columns);

	void setSize(int rows, int columns);

	// METHODS
	T & Select(int row, int column) const;

private:
	// MEMBERS
	Array<T> m_array;
	int m_rows;
	int m_cols;
};


/////////////////////////////////////////////////////////
// C'TORS & D'TOR
//////

template<typename T>
Array2D<T>::Array2D(int rows, int cols)
	: m_rows(rows), m_cols(cols), m_array(rows * cols)
{}

template<typename T>
Array2D<T>::Array2D(const Array2D<T> & copy)
	: m_rows(copy.m_rows), m_cols(copy.m_cols), m_array(copy.m_array)
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
	m_rows(rhs.m_rows);
	m_cols(rhs.m_cols);
	m_array(rhs.m_array);
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
int Array2D<T>::getRows() const
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
void Array2D<T>::setRows(int rows)
{
	if (rows < 0)
		throw Exception("Error: Cannot set rows to a value less than zero!");

	if (rows != m_rows)
	{
		m_rows = rows;
		m_array.setLength(rows * m_cols);
	}
}

template<typename T>
int Array2D<T>::getColumns() const
{
	return m_cols;
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
void Array2D<T>::setColumns(int columns)
{
	if (columns < 0)
		throw Exception("Error: Cannot set columns to a value less than zero!");

	if (columns != m_cols)
	{
		// create a temporary array with the new size
		Array<T> temp(m_rows * columns);
		int cols = MIN(m_cols, columns);
		int new_row = 0;
		int new_index;

		// starting at the beginning
		// jump to the first item of each row
		for (int row = 0; row < m_array.getLength(); row += m_cols)
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
		m_cols = columns;
	}
}

template<typename T>
void Array2D<T>::setSize(int rows, int columns)
{
	setRows(rows);
	setColumns(columns);
}

//////
// END SETTERS AND GETTERS
/////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////
// PUBLIC METHODS
//////

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
*		Returns:	N/A
*************************************************************************/
template<typename T>
T & Array2D<T>::Select(int row, int column) const
{
	if (row < 0 || row >= m_rows)
		throw Exception("Row index out of bounds!");
	else if (column < 0 || column >= m_cols)
		throw Exception("Column index out of bounds!");

	int index = ((row * m_cols) + column);
	return m_array[index];
}

//////
// END PUBLIC METHODS
/////////////////////////////////////////////////////////

#endif // ARRAY2D_H