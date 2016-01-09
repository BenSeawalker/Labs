#ifndef ROW_H
#define ROW_H

template<typename T>
class Row
{
public:
	// C'TORS & D'TOR
	Row(Array2D<T> & ra, int row);
	~Row();

	// OPERATORS
	T & operator[](int column) const;

private:
	// MEMBERS
	Array2D<T> & m_array2D;
	int m_row;
};


/////////////////////////////////////////////////////////
// C'TORS & D'TOR
//////

template<typename T>
Row<T>::Row(Array2D<T> & ra, int row)
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

template<typename T>
T & Row<T>::operator[](int column)
{
	int index = ((m_array2D.m_cols * m_row) + column);
	return m_array2D.m_array[index];
}

//////
// END OPERATORS
/////////////////////////////////////////////////////////

#endif // ROW_H
