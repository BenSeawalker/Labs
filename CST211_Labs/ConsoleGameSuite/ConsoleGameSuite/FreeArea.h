#ifndef FREEAREA_H
#define FREEAREA_H

#include "Area.h"
#include "Array.h"

class FreeArea : public Area
{
public:
	FreeArea();
	FreeArea(const FreeArea & copy);

	~FreeArea();

	FreeArea & operator=(const FreeArea & rhs);

	virtual bool IsValid(const Card & card, int dest);
	virtual void AddCard(Card card, int dest);
	virtual Card TakeCard(int src);

private:
	Array<Card> m_cards;

};

#endif // FREEAREA_H
