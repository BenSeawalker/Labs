#ifndef DECK_H
#define DECK_H

#include "Array.h"
#include "AStack.h"
#include "Card.h"

class Deck
{
public:
	Deck();
	Deck(const Deck & copy);
	~Deck();

	Deck & operator=(const Deck & rhs);

	void Shuffle(unsigned int seed = 0);
	void Reset();

	Card DrawCard();
	bool isEmpty();

private:
	void BuildDeck();
	
	Array<Card> m_original;
	Array<Card> m_shuffle;
	AStack<Card> m_deck;
};

#endif // DECK_H
