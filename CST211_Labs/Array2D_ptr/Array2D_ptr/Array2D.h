#ifndef ARRAY2D_H
#define ARRAY2D_H

#define MIN(arg1, arg2) ((arg1 <= arg2) ? arg1 : arg2)

/************************************************************************
* Class: Array2D
*
* Purpose: This class provides two dimensional functionality using an array of arrays of T's
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
	Array2D(int rows = 0, int cols = 0);
	Array2D(const Array2D<T> & copy);

	~Array2D();

	// OPERATORS
	Array2D<T> & operator=(const Array2D<T> & rhs);
	const Row<T> operator[](int row) const;

	// GETTERS AND SETTERS
	int Rows() const;
	void SetRows(int rows);

	int Columns() const;
	void SetColumns(int columns);

	void SetSize(int rows, int columns);

	// METHODS
	T & Select(int row, int column) const;

	bool Contains(int row, int column) const;

	void Purge();

private:
	// METHODS
	void DeepCopy(const Array2D<T> & source);

	// MEMBERS
	T ** m_array;
	int m_rows;
	int m_columns;
};


/////////////////////////////////////////////////////////
// C'TORS & D'TOR
//////

template<typename T>
Array2D<T>::Array2D(int rows, int cols)
	: m_rows(rows), m_columns(cols), m_array(nullptr)
{
	if ((rows * cols) < 0)
		throw Exception("Array size must be non-negative!");

	m_array = new T *[m_rows];
	for (int i = 0; i < (m_rows); ++i)
		m_array[i] = new T[m_columns];
}

template<typename T>
Array2D<T>::Array2D(const Array2D<T> & copy)
	: m_rows(0), m_columns(0), m_array(nullptr)
{
	DeepCopy(copy);
}

template<typename T>
Array2D<T>::~Array2D()
{
	Purge();
}

//////
// END C'TORS AND D'TOR
/////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////
// OPERATORS
//////

template<typename T>
Array2D<T> & Array2D<T>::operator=(const Array2D<T> & rhs)
{
	DeepCopy(rhs);
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
*		Returns:	the specified Row
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
		int min_len = MIN(m_rows, rows);
		T ** temp = new T *[rows];

		for (int i = 0; i < min_len; ++i)
			temp[i] = m_array[i];

		for (int i = min_len; i < rows; ++i)
			temp[i] = new T[m_columns];

		for (int i = min_len; i < m_rows; i++)
			delete[] m_array[i];

		delete[] m_array;
		m_array = temp;

		m_rows = rows;
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
		int min_len = MIN(m_columns, columns);
		for (int i = 0; i < m_rows; ++i)
		{
			T * temp = new T[columns];

			for (int j = 0; j < min_len; ++j)
				temp[j] = m_array[i][j];

			delete[] m_array[i];
			m_array[i] = temp;
		}

		m_columns = columns;
	}
}

template<typename T>
void Array2D<T>::SetSize(int rows, int columns)
{
	SetColumns(columns);
	SetRows(rows);
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
*		Returns:	The specified item by reference
*************************************************************************/
template<typename T>
T & Array2D<T>::Select(int row, int column) const
{
	if (row < 0 || row >= m_rows)
		throw Exception("Row index out of bounds!");
	else if (column < 0 || column >= m_columns)
		throw Exception("Column index out of bounds!");

	return m_array[row][column];
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
	for (int i = 0; i < m_rows; ++i)
		delete[] m_array[i];

	delete[] m_array;
	m_array = nullptr;

	m_rows = 0;
	m_columns = 0;
}

//////
// END PUBLIC METHODS
/////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////
// PRIVATE METHODS
//////

template<typename T>
void Array2D<T>::DeepCopy(const Array2D<T> & source)
{
	Purge();
	m_columns = source.m_columns;
	m_rows = source.m_rows;

	m_array = new T *[m_rows];
	for (int i = 0; i < m_rows; ++i)
	{
		m_array[i] = new T[m_columns];

		for (int j = 0; j < m_columns; ++j)
			m_array[i][j] = source.m_array[i][j];
	}
}

//////
// END PRIVATE METHODS
/////////////////////////////////////////////////////////

#endif // ARRAY2D_H