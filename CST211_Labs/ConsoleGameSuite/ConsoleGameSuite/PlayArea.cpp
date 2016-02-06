#include "PlayArea.h"

PlayArea::PlayArea()
	: m_cards(8)
{
	for (int i = 0; i < m_cards.Length(); ++i)
		m_cards[i].Push(Card());
}

PlayArea::PlayArea(const PlayArea & copy)
	: m_cards(copy.m_cards)
{}

PlayArea::~PlayArea()
{}


PlayArea & PlayArea::operator=(const PlayArea & rhs)
{
	if (this != &rhs)
		m_cards = rhs.m_cards;

	return *this;
}


bool PlayArea::IsValid(const Card & card, int dest)
{
	bool valid = ((m_cards[dest].Peek().Rank() == NONE) ||
				((GetColor(card) != GetColor(m_cards[dest].Peek())) &&
				(card.Rank() == (m_cards[dest].Peek().Rank() - 1))));

	return valid;
}

void PlayArea::AddCard(Card card, int dest)
{
	m_cards[dest].Push(card);
}

Card PlayArea::TakeCard(int src)
{
	Card card;
	if (m_cards[src].Peek().Rank() != NONE)
		card = m_cards[src].Pop();

	return card;
}

bool PlayArea::GetColor(const Card & card)
{
	return (card.Suit() <= DIAMONDS);
}

