#include "Deck.h"
#include <random>
#include <time.h>


Deck::Deck()
	: m_original(52), m_shuffle(52), m_deck(52)
{
	BuildDeck();
}

Deck::Deck(const Deck & copy)
	: m_deck
{

}


Deck::~Deck()
{
}

Deck & Deck::operator=(const Deck & rhs)
{
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

	for (int i = 0; i < 100; ++i)
	{
		int c1 = rand() % m_original.Length();
		int c2 = rand() % m_original.Length();

		m_shuffle[c1] = m_original[c2];
		m_shuffle[c2] = m_original[c1];
	}

	for (int i = 0; i < m_shuffle.Length(); ++i)
		m_deck.Push(m_shuffle[i]);
}

void Deck::Reset()
{
	while (!m_deck.isEmpty())
		m_deck.Pop();

	for (int i = 0; i < m_original.Length(); ++i)
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
			//                        row    column
			int i = ((((suit - HEARTS) * KING) + rank) - 1);
			m_original[i] = Card(suit, rank);
		}
	}

	for (int i = 0; i < m_original.Length(); ++i)
		m_deck.Push(m_original[i]);
}


//int Deck::RandomInt(int min, int max)
//{
//	int r = (int)rand() / (int)RAND_MAX;
//	return (min + (r * (max - min)));
//}