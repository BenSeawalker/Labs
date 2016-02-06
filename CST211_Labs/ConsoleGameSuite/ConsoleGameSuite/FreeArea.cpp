#include "FreeArea.h"

FreeArea::FreeArea()
	: m_cards(4)
{}

FreeArea::FreeArea(const FreeArea & copy)
	: m_cards(copy.m_cards)
{}

FreeArea::~FreeArea()
{}


FreeArea & FreeArea::operator=(const FreeArea & rhs)
{
	if(this != &rhs)
		m_cards = rhs.m_cards;

	return *this;
}


bool FreeArea::IsValid(const Card & card, int dest)
{
	return (m_cards[dest].Rank() == NONE);
}

void FreeArea::AddCard(Card card, int dest)
{
	m_cards[dest] = card;
}

Card FreeArea::TakeCard(int src)
{
	Card card = m_cards[src];
	m_cards[src] = Card();

	return card;
}
