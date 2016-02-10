#include "Freecell.h"

#include "FreeArea.h"
#include "HomeArea.h"
#include "PlayArea.h"

#include "Console.h"
#include "Button.h"

#include "Keyboard.h"
#include "Mouse.h"

#include <string>
using std::string;
using std::to_string;


Freecell::Freecell()
	: m_cards(TOTAL_CARDS), m_selected(nullptr), m_running(true), m_paused(false)
{
	SetModel(&m_board);
}

Freecell::Freecell(FCBoard::SCENARIO scenario)
	: m_cards(TOTAL_CARDS), m_selected(nullptr), m_running(true), m_paused(false), m_board(scenario)
{
	SetModel(&m_board);
}

Freecell::Freecell(const Freecell & copy)
	: m_running(copy.m_running), m_board(copy.m_board), m_cards(copy.m_cards), m_moved(copy.m_moved), m_selected(nullptr)
{
	SetModel(&m_board);
}

Freecell::~Freecell()
{}

Freecell & Freecell::operator=(const Freecell & rhs)
{
	if (this != &rhs)
	{
		m_board = rhs.m_board;
		m_cards = rhs.m_cards;
		m_moved = rhs.m_moved;
		m_paused = rhs.m_paused;
		m_running = rhs.m_running;
		m_selected = nullptr;

		SetModel(&m_board);
	}

	return *this;
}

bool Freecell::Update()
{
	bool clicked = false;

	m_running = !Keyboard::KeyPressed(VK_ESCAPE);

	if (m_running && !m_paused)
	{
		for (int i = 0; i < m_cards.Length(); ++i)
		{
			CardBtn & cb = m_cards[i];
			cb.Update();

			if (cb.Clicked(Mouse::LEFT))
			{
				if (m_selected == nullptr)
				{
					clicked = true;
					m_moved = false;
					if (!cb.IsEmpty() && cb.Depth() > 0)
					{
						m_selected = &cb;
						cb.SetSelected(true);
						if (cb.Depth() > 1)
						{
							for (int i = 0; i < m_cards.Length(); ++i)
							{
								if (m_cards[i].Area() == cb.Area() && m_cards[i].Row() == cb.Row() && m_cards[i].Depth() < cb.Depth())
									m_cards[i].SetSelected(true);
							}
						}
					}
				}
				else if (!m_moved)
				{
					m_moved = true;
					m_board.MoveCards(m_selected->Area(), cb.Area(), m_selected->Row(), cb.Row(), m_selected->Depth());
					CheckVictory();
				}
			}
		}

		if (!clicked && Mouse::BtnPressed(Mouse::LEFT))
		{
			m_selected = nullptr;
			DeselectAll();
		}
	}

	return m_running;
}

void Freecell::ModelUpdated()
{
	Draw();
}

void Freecell::Draw()
{
	CClear( Color::green);

	// Free area
	DrawFreeArea();

	// Home area
	DrawHomeArea();

	// Play area
	DrawPlayArea();

	// Scoreboard
	CWrite(CWidth() / 2, CHeight() - 2, to_string(m_board.Moves()).c_str(), CMakeColor(Color::bright_white, Color::green));
}

void Freecell::DrawFreeArea()
{
	FreeArea * free = dynamic_cast<FreeArea *>(m_board.GetArea(FCBoard::FREE));
	if (free)
	{
		int width = CardBtn::SIZE + 1;

		for (int i = 0; i < FREE_CELLS; ++i)
		{
			Card c = free->SeeCard(i);
			string disp = to_string(c.Rank()) + c.Suit();
			COLOR col = ((c.Suit() <= DIAMONDS) ? Color::dark_red : Color::black);

			CardBtn & cb = m_cards[i];
			int x = OFF_X + i * width;
			int y = OFF_Y;

			cb.SetPos(x, y, Color::green);
			cb.Large();
			cb.SetCard(c);
			cb.SetRow(i);
			cb.SetArea(FCBoard::FREE);
		}
	}
}

void Freecell::DrawHomeArea()
{
	HomeArea * home = dynamic_cast<HomeArea *>(m_board.GetArea(FCBoard::HOME));

	if (home)
	{
		int width = CardBtn::SIZE + 1;

		for (int i = 0; i < HOME_CELLS; ++i)
		{
			Card c = home->SeeCard(i);
			string disp = to_string(c.Rank()) + c.Suit();
			

			CardBtn & cb = m_cards[i + FREE_CELLS];
			int x = OFF_X + i * width + FREE_CELLS * width + width / 2;
			int y = OFF_Y;

			cb.SetPos(x, y, Color::green);
			cb.Large();
			cb.SetCard(c);
			cb.SetRow(i);
			cb.SetArea(FCBoard::HOME);
			
			COLOR col = (((i + HEARTS) <= DIAMONDS) ? Color::dark_red : Color::blue);
			CClearRect(x + 2, y - 2, x + width - 3, y - 1, CMakeBackground(Color::white));
			CWrite(x + width / 2 - 1, y - 2, char(i + HEARTS), CMakeColor(col, Color::white));
		}
	}
}

void Freecell::DrawPlayArea()
{
	PlayArea * play = dynamic_cast<PlayArea *>(m_board.GetArea(FCBoard::PLAY));
	
	if (play)
	{
		int width = CardBtn::SIZE + 1;

		int total = 0;
		for (int i = 0; i < PLAY_CELLS; ++i)
		{
			LStack<Card> temp;
			while (play->SeeCard(i).Rank() != NONE)
				temp.Push(play->TakeCard(i));

			temp.Push(play->TakeCard(i));

			int depth = temp.Size();

			int cards = 0;
			while (!temp.isEmpty())
			{
				Card c = temp.Pop();
				string disp = to_string(c.Rank()) + c.Suit();
				COLOR col = ((c.Suit() <= DIAMONDS) ? Color::dark_red : Color::black);

				CardBtn & cb = m_cards[FREE_CELLS + HOME_CELLS + total++];
				int x = OFF_X + 2 + i * width;
				int y = OFF_Y + cards++ * 2 + width + 2 - (cards > 0) * 2;

				cb.SetPos(x, y, Color::green);
				cb.SetCard(c);
				cb.SetDepth(depth--);
				cb.SetRow(i);
				cb.SetArea(FCBoard::PLAY);

				if (temp.Size() > 0)
					cb.Small();
				else
					cb.Large();

				play->AddCard(c, i);
			}
		}

		// hide extra cards
		for (total += FREE_CELLS + HOME_CELLS; total < m_cards.Length(); ++total)
		{
			m_cards[total].SetPos(-width, -width, Color::green, false);
		}

		// ensure that all cards are displayed
		for (int i = 0; i < m_cards.Length(); i++)
		{
			m_cards[i].Draw();
		}
	}
}

void Freecell::DeselectAll()
{
	for (int i = 0; i < m_cards.Length(); ++i)
	{
		m_cards[i].SetSelected(false);
	}
}

void Freecell::CheckVictory()
{
	HomeArea * home = dynamic_cast<HomeArea *>(m_board.GetArea(FCBoard::HOME));
	
	if (home)
	{
		bool victory = true;
		
		for (int i = 0; i < HOME_CELLS && victory; ++i)
		{
			LStack<Card> temp;
			while (home->SeeCard(i).Rank() != NONE)
				temp.Push(home->TakeCard(i));

			if (temp.Size() < 13)
				victory = false;

			while (!temp.isEmpty())
				home->AddCard(temp.Pop(), i);
		}

		if (victory)
			WinGame();
	}
}

void Freecell::WinGame()
{
	//m_paused = true;
	m_running = false;
}
