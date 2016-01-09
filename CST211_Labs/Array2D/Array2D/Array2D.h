#ifndef ARRAY2D_H
#define ARRAY2D_H

#include "Array.h"
#include "Row.h"

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
	const Row<T> operator[](int row);

	// GETTERS AND SETTERS
	int getRows();
	void setRows(int rows);

	int getColumns();
	void setColumns(int columns);

	// METHODS
	T & Select(int row, int column);

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

template<typename T>
const Row<T> Array2D<T>::operator[](int row)
{
	return Row<T>(*this, row);
}

//////
// END OPERATORS
/////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////
// SETTERS AND GETTERS
//////

template<typename T>
int Array2D<T>::getRows()
{
	return m_rows;
}

template<typename T>
void Array2D<T>::setRows(int rows)
{
	if (rows != m_rows)
	{
		m_rows = rows;
		m_array.setLength(rows * m_cols);
	}
}

template<typename T>
int Array2D<T>::getColumns()
{
	return m_cols;
}

template<typename T>
void Array2D<T>::setColumns(int columns)
{
	if (columns != m_cols)
	{
		int diff = columns - m_cols;
		int len = m_array.getLength();

		if (diff < 0) // less columns
		{
			diff = abs(diff);
			int new_index = (m_cols - diff);

			// jump to the first item of each row
			for (int i = m_cols; i < len; i += m_cols)
			{
				// move diff number of items to their new index
				for (int j = i; j < (i + diff); ++j)
				{
					m_array[new_index++] = m_array[j];
				}
			}

			// decrease the length
			m_array.setLength(m_rows * columns);
		}
		else if (diff > 0) // more columns
		{
			// increase the length
			m_array.setLength(m_rows * columns);
			int new_index = ((m_array.getLength() - 1) - diff);

			// jump to the last item of each row
			for (int i = (len - 1); i > m_cols; i -= m_cols)
			{
				// move each item to their new index
				for (int j = i; j > (i - m_cols); --j)
				{
					m_array[new_index--] = m_array[j];
				}
				new_index -= diff;
			}
		}

		m_cols = columns;
	}
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
	int index = ((row * m_cols) + column);
	return m_array[index];
}

//////
// END PUBLIC METHODS
/////////////////////////////////////////////////////////

#endif // ARRAY2D_H