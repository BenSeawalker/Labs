#ifndef HOMEAREA_H
#define HOMEAREA_H

#include "Area.h"
#include "Array.h"
#include "AStack.h"

class HomeArea : public Area
{
public:
	HomeArea();
	HomeArea(const HomeArea & copy);

	virtual ~HomeArea();

	HomeArea & operator=(const HomeArea & rhs);

	virtual bool IsValid(const Card & card, int dest);
	virtual void AddCard(Card card, int dest);
	virtual Card TakeCard(int src);
	virtual const Card & SeeCard(int src) const;
	virtual int OpenCells(int dest = -1);
	virtual int ValidDepth(int dest);

private:
	Array<AStack<Card>> m_cards;

};

#endif // HOMEAREA_H
