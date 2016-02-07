#ifndef FCBOARD_H
#define FCBOARD_H

#include "Model.h"
#include "Array.h"
#include "Area.h"


class FCBoard : public Model
{
public:
	enum AREA { FREE, HOME, PLAY };

	FCBoard();
	FCBoard(const FCBoard & copy);
	virtual ~FCBoard();

	FCBoard & operator=(const FCBoard & rhs);

	bool MoveCards(AREA from, AREA to, int src, int dest, int depth);

	Area * GetArea(AREA area);

private:
	void DeepCopy(const FCBoard & copy);

	Array<Area *> m_areas;
};

#endif // FCBOARD_H
