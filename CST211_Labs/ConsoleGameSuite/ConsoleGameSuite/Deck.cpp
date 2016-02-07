#include "Deck.h"
#include <random>
#include <time.h>


Deck::Deck()
	: m_original(52), m_shuffle(52), m_deck(52)
{
	BuildDeck();
}

Deck::Deck(const Deck & copy)
	: m_original(copy.m_original), m_shuffle(copy.m_shuffle), m_deck(copy.m_deck)
{}


Deck::~Deck()
{}

Deck & Deck::operator=(const Deck & rhs)
{
	if (this != &rhs)
	{
		m_shuffle = rhs.m_shuffle;
		m_deck = rhs.m_deck;
	}

	return *this;
}


void Deck::Shuffle(unsigned int seed)
{
	if (seed == 0)
		seed = (unsigned)time(NULL);

	srand(seed);

	m_shuffle = m_original;
	while (!m_deck.isEmpty())
		m_deck.Pop();

	for (int i = 0; i < 156; ++i)
	{
		int c1 = rand() % m_original.Length();
		int c2 = rand() % m_original.Length();

		Card temp = m_shuffle[c1];
		m_shuffle[c1] = m_shuffle[c2];
		m_shuffle[c2] = temp;
	}

	for (int i = 0; i < m_shuffle.Length(); ++i)
		m_deck.Push(m_shuffle[i]);
}

void Deck::Reset()
{
	while (!m_deck.isEmpty())
		m_deck.Pop();

	for (int i = m_original.Length() - 1; i >= 0; --i)
		m_deck.Push(m_original[i]);
}

Card Deck::DrawCard()
{
	return m_deck.Pop();
}

bool Deck::isEmpty()
{
	return m_deck.isEmpty();
}

void Deck::BuildDeck()
{
	for (char suit = HEARTS; suit <= SPADES; ++suit)
	{
		for (int rank = ACE; rank <= KING; ++rank)
		{
			int i = ((((suit - HEARTS) * KING) + rank) - 1);
			m_original[i] = Card(suit, rank);
		}
	}

	Reset();
}