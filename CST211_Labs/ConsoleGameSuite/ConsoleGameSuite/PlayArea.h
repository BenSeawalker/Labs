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

	~PlayArea();

	PlayArea & operator=(const PlayArea & rhs);

	virtual bool IsValid(const Card & card, int dest);
	virtual void AddCard(Card card, int dest);
	virtual Card TakeCard(int src);

private:
	bool GetColor(const Card & card);

	Array<LStack<Card>> m_cards;

};

#endif // PLAYAREA_H
