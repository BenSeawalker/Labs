#ifndef ROW_H
#define ROW_H

#include "Array2D.h"

template<typename T>
class Row
{
public:
	// C'TORS & D'TOR
	Row(const Array2D<T> & ra, int row);
	~Row();

	// OPERATORS
	T & operator[](int column) const;

private:
	// MEMBERS
	const Array2D<T> & m_array2D;
	int m_row;
};


/////////////////////////////////////////////////////////
// C'TORS & D'TOR
//////

template<typename T>
Row<T>::Row(const Array2D<T> & ra, int row)
	: m_array2D(ra), m_row(row)
{}

template<typename T>
Row<T>::~Row()
{}

//////
// END C'TORS AND D'TOR
/////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////
// OPERATORS
//////

/************************************************************************
* Purpose: To easily access an item in the Array
*
* Precondition:
*		column - must be within the bounds of the array
*
* Postcondition:
*		Modifies:	N/A
*		Throws:	Exception("Column index out of bounds!")
*		Returns:	the item located at the specified row and column by reference
*************************************************************************/
template<typename T>
T & Row<T>::operator[](int column) const
{
	if ((column < 0) || (column >= m_array2D.m_cols))
		throw Exception("Column index out of bounds!");

	return m_array2D.m_array[m_row][column];
}

//////
// END OPERATORS
/////////////////////////////////////////////////////////

#endif // ROW_H
