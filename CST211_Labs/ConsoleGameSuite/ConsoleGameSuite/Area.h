#ifndef AREA_H
#define AREA_H

#include "Card.h"

class Area
{
public:
	virtual ~Area() {};

	virtual bool IsValid(const Card & card, int dest) = 0;
	virtual void AddCard(Card card, int dest) = 0;
	virtual Card TakeCard(int src) = 0;
	virtual const Card & SeeCard(int src) const = 0;
	virtual int OpenCells(int dest = -1) = 0;
	virtual int ValidDepth(int dest) = 0;
};


#endif // AREA_H
