#include "HomeArea.h"

HomeArea::HomeArea()
	: m_cards(4)
{
	for (int i = 0; i < 4; ++i)
	{
		m_cards[i].Resize(52);
		m_cards[i].Push(Card());
	}
}

HomeArea::HomeArea(const HomeArea & copy)
	: m_cards(copy.m_cards)
{}

HomeArea::~HomeArea()
{}


HomeArea & HomeArea::operator=(const HomeArea & rhs)
{
	if (this != &rhs)
		m_cards = rhs.m_cards;

	return *this;
}


bool HomeArea::IsValid(const Card & card, int dest)
{
	bool valid = false;

	switch (dest)
	{
	case 0:
		valid = ((card.Suit() == HEARTS) && (card.Rank() == (m_cards[dest].Peek().Rank() + 1)));
		break;

	case 1:
		valid = ((card.Suit() == DIAMONDS) && (card.Rank() == (m_cards[dest].Peek().Rank() + 1)));
		break;

	case 2:
		valid = ((card.Suit() == CLUBS) && (card.Rank() == (m_cards[dest].Peek().Rank() + 1)));
		break;

	case 3:
		valid = ((card.Suit() == SPADES) && (card.Rank() == (m_cards[dest].Peek().Rank() + 1)));
		break;
	}

	return valid;
}

void HomeArea::AddCard(Card card, int dest)
{
	m_cards[dest].Push(card);
}

Card HomeArea::TakeCard(int src)
{
	Card card;
	if(m_cards[src].Peek().Rank() != NONE)
		card = m_cards[src].Pop();

	return card;
}

