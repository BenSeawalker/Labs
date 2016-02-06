#ifndef AREA_H
#define AREA_H

#include "Card.h"

class Area
{
public:
	virtual bool IsValid(const Card & card, int dest) = 0;
	virtual void AddCard(Card card, int dest) = 0;
	virtual Card TakeCard(int src) = 0;
};


#endif // AREA_H
