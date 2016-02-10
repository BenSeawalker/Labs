#ifndef FREEAREA_H
#define FREEAREA_H

#include "Area.h"
#include "Array.h"

class FreeArea : public Area
{
public:
	FreeArea();
	FreeArea(const FreeArea & copy);

	virtual ~FreeArea();

	FreeArea & operator=(const FreeArea & rhs);

	virtual bool IsValid(const Card & card, int dest);
	virtual void AddCard(Card card, int dest);
	virtual Card TakeCard(int src);
	virtual const Card & SeeCard(int src) const;
	virtual int OpenCells(int dest = -1);
	virtual int ValidDepth(int dest);

private:
	Array<Card> m_cards;

};

#endif // FREEAREA_H
