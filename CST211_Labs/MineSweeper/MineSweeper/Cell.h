#ifndef CELL_H
#define CELL_H


class Cell
{
public:
	enum TYPE { BOMB = -1, COVERED = 0};
	// C'TORS AND D'TOR
	Cell();
	Cell(const Cell & copy);
	~Cell();

	// OPERATORS
	Cell & operator=(const Cell & rhs);

private:
	bool m_checked;
	int m_value;
};

#endif // Cell_h__
