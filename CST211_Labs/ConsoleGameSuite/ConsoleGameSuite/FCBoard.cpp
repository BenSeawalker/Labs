#include "FCBoard.h"

#include "FreeArea.h"
#include "HomeArea.h"
#include "PlayArea.h"

#include "Deck.h"


FCBoard::FCBoard()
	: m_areas(3)
{
	m_areas[FREE] = new FreeArea;
	m_areas[HOME] = new HomeArea;
	m_areas[PLAY] = new PlayArea;
	
	Deck d;
	d.Shuffle();
	for (int i = 0; i < 52; ++i)
		m_areas[PLAY]->AddCard(d.DrawCard(), i % 8);
}


FCBoard::FCBoard(const FCBoard & copy)
	: m_areas(3)
{
	DeepCopy(copy);
}

FCBoard::~FCBoard()
{
	delete m_areas[FREE];
	delete m_areas[HOME];
	delete m_areas[PLAY];
}

FCBoard & FCBoard::operator=(const FCBoard & rhs)
{
	if (this != &rhs)
	{
		delete m_areas[FREE];
		delete m_areas[HOME];
		delete m_areas[PLAY];

		DeepCopy(rhs);
		Notify();
	}

	return *this;
}


bool FCBoard::MoveCards(AREA from, AREA to, int src, int dest, int depth)
{
	int f_dest = (to == FREE ? dest : -1);
	int p_dest = (to == PLAY ? dest : -1);
	int open_cells = m_areas[FREE]->OpenCells(f_dest) + m_areas[PLAY]->OpenCells(p_dest) + 1;

	bool valid = (open_cells >= depth && depth <= m_areas[from]->ValidDepth(src));
	if (from != to)
		valid = valid && (depth <= m_areas[to]->ValidDepth(dest));

	if (valid)
	{
		AStack<Card> temp(depth);
		for (int i = 0; i < depth; ++i)
			temp.Push(m_areas[from]->TakeCard(src));

		valid = m_areas[to]->IsValid(temp.Peek(), dest);

		while (!temp.isEmpty())
			if (valid)
				m_areas[to]->AddCard(temp.Pop(), dest);
			else
				m_areas[from]->AddCard(temp.Pop(), src);

		Notify();
	}

	return valid;
}

Area * FCBoard::GetArea(AREA area)
{
	return m_areas[area];
}

void FCBoard::DeepCopy(const FCBoard & copy)
{
	m_areas[FREE] = new FreeArea(*((FreeArea *)copy.m_areas[FREE]));
	m_areas[HOME] = new HomeArea(*((HomeArea *)copy.m_areas[HOME]));
	m_areas[PLAY] = new PlayArea(*((PlayArea *)copy.m_areas[PLAY]));
}

