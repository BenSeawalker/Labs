#include "Freecell.h"

#include "FreeArea.h"
#include "HomeArea.h"
#include "PlayArea.h"

#include "Console.h"
#include "Button.h"


#include <string>
using std::string;
using std::to_string;


Freecell::Freecell()
	: m_cards(68), m_selected(nullptr)
{}

Freecell::Freecell(FCBoard * model)
	: View(model)
{
	ModelUpdated();
}


Freecell::~Freecell()
{}

bool Freecell::Update()
{
	bool clicked = false;

	for (int i = 0; i < m_cards.Length(); ++i)
	{
		CardBtn & cb = m_cards[i];
		cb.Update();
		
		if (cb.Clicked(Mouse::LEFT))
		{
			if (m_selected == nullptr)
			{
				clicked = true;
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
			else
			{
				FCBoard * board = (FCBoard *)GetModel();
				board->MoveCards(m_selected->Area(), cb.Area(), m_selected->Row(), cb.Row(), m_selected->Depth());
			}
		}
	}

	if (!clicked && Mouse::BtnPressed(Mouse::LEFT))
	{
		m_selected = nullptr;
		DeselectAll();
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

	if (GetModel())
	{
		// Free area
		DrawFreeArea();

		// Home area
		DrawHomeArea();

		// Play area
		DrawPlayArea();
	}
}

void Freecell::DrawFreeArea()
{
	FreeArea * free = dynamic_cast<FreeArea *>(((FCBoard *)GetModel())->GetArea(FCBoard::FREE));
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
	HomeArea * home = dynamic_cast<HomeArea *>(((FCBoard *)GetModel())->GetArea(FCBoard::HOME));

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
	PlayArea * play = dynamic_cast<PlayArea *>(((FCBoard *)GetModel())->GetArea(FCBoard::PLAY));
	
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
