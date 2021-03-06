/************************************************************************
* Author:		Garrett Fleischer
* Filename:		Board.cpp
* Date Created:	1/15/16
* Modifications: N/A
*************************************************************************/

#include "MSBoard.h"


///////////////////////////////////////////////////////////////
//	CTORS AND DTOR
//////

MSBoard::MSBoard(int rows, int columns)
	: Array2D(rows, columns)
{}

MSBoard::MSBoard(const MSBoard & copy)
	: Array2D(copy)
{}

MSBoard::~MSBoard()
{
	Purge();
}

//////
//	END CTORS AND DTOR
///////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////
//	OPERATORS
//////

MSBoard & MSBoard::operator=(const MSBoard & rhs)
{
	Array2D::operator=(rhs);
	return *this;
}

//////
//	END OPERATORS
///////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////
//	PUBLIC METHODS
//////

//////
//	END PUBLIC METHODS
///////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////
//	PRIVATE METHODS
//////

//////
//	END PRIVATE METHODS
///////////////////////////////////////////////////////////////