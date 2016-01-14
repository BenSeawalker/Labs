#ifndef BOARD_H
#define BOARD_H

#include "Array2D.h"
#include "Cell.h"

class Board : public Array2D<Cell>
{
public:
	// CTORS AND DTOR
	Board(int rows = 0, int columns = 0);
	Board(const Board & copy);
	
	virtual ~Board();

	// OPERATORS
	virtual Board & operator=(const Board & rhs);

private:

};

#endif // BOARD_H

