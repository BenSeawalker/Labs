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
	: m_cards(52)
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

	for (int i = 0; i < FREE_CELLS; ++i)
	{
		Card c = free->SeeCard(i);
		string disp = to_string(c.Rank()) + c.Suit();
		COLOR col = ((c.Suit() <= DIAMONDS) ? Color::dark_red : Color::black);

		CWrite(i * 4, 3, disp.c_str(), CMakeColor(col, Color::green));
	}
}

void Freecell::DrawHomeArea()
{
	HomeArea * home = dynamic_cast<HomeArea *>(((FCBoard *)GetModel())->GetArea(FCBoard::HOME));

	for (int i = 0; i < HOME_CELLS; ++i)
	{
		Card c = home->SeeCard(i);
		string disp = to_string(c.Rank()) + c.Suit();
		COLOR col = ((c.Suit() <= DIAMONDS) ? Color::dark_red : Color::black);

		CWrite(i * 4 + 4 + FREE_CELLS * 4, 3, disp.c_str(), CMakeColor(col, Color::green));
	}
}

void Freecell::DrawPlayArea()
{
	PlayArea * play = dynamic_cast<PlayArea *>(((FCBoard *)GetModel())->GetArea(FCBoard::PLAY));

	for (int i = 0; i < PLAY_CELLS; ++i)
	{
		LStack<Card> temp;
		while (play->SeeCard(i).Rank() != NONE)
			temp.Push(play->TakeCard(i));

		int cards = 0;
		while (!temp.isEmpty())
		{
			Card c = temp.Pop();
			string disp = to_string(c.Rank()) + c.Suit();
			COLOR col = ((c.Suit() <= DIAMONDS) ? Color::dark_red : Color::black);

			CWrite(i * 4, 5 + cards++, disp.c_str(), CMakeColor(col, Color::green));

			play->AddCard(c, i);
		}
	}
}

//void Freecell::SetModel(Model * model)
//{
//	View::SetModel(model);
//	Draw();
//}
