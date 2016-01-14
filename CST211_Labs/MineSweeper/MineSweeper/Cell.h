#ifndef CELL_H
#define CELL_H


class Cell
{
public:
	enum { BOMB = -1, EMPTY = 0 };

	// C'TORS AND D'TOR
	Cell(int value = int(EMPTY));
	Cell(const Cell & copy);
	~Cell();

	// OPERATORS
	Cell & operator=(const Cell & rhs);

private:
	int m_value;
	bool m_checked;
	
};

#endif // Cell_h__
