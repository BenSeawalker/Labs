#include "Board.h"


Board::Board(int rows, int columns)
	: Array2D(rows, columns)
{}

Board::Board(const Board & copy)
	: Array2D(copy)
{}

Board::~Board()
{
	Purge();
}

Board & Board::operator=(const Board & rhs)
{
	Array2D::operator=(rhs);
	return *this;
}
