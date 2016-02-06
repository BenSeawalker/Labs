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

	~HomeArea();

	HomeArea & operator=(const HomeArea & rhs);

	virtual bool IsValid(const Card & card, int dest);
	virtual void AddCard(Card card, int dest);
	virtual Card TakeCard(int src);

private:
	Array<AStack<Card>> m_cards;

};

#endif // HOMEAREA_H
