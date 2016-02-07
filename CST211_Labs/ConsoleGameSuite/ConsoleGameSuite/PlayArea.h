#ifndef PLAYAREA_H
#define PLAYAREA_H

#include "Area.h"
#include "Array.h"
#include "LStack.h"

class PlayArea : public Area
{
public:
	PlayArea();
	PlayArea(const PlayArea & copy);

	virtual ~PlayArea();

	PlayArea & operator=(const PlayArea & rhs);

	virtual bool IsValid(const Card & card, int dest);
	virtual void AddCard(Card card, int dest);
	virtual Card TakeCard(int src);
	virtual const Card & SeeCard(int src);
	virtual int OpenCells(int dest = -1);
	virtual int ValidDepth(int dest);

private:
	bool GetColor(const Card & card);

	Array<LStack<Card>> m_cards;

};

#endif // PLAYAREA_H
