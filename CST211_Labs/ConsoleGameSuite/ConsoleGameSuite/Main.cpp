/*****************************************************************************************
Author:			Garrett Fleischer
Filename:		Main.cpp
Date Created:	1/12/16
Modifications:
		1/27/16 - FIXED NARROWING CONVERSION ERRORS IN VS 2015+
		2/2/16 - Updated main to use improved console drawing.

Lab/Assignment: L1

Overview: Suite of games for the console:
			Minesweeper
			Freecell

Input: Input is received in a non-blocking manner from the mouse and keyboard

Output: The output for this program is to the console window and consists of clickable
		buttons and tiles.

*****************************************************************************************/

#include <iostream>
using std::cout;
using std::endl;

#include "crtdbg_new.h"

#include "MineSweeper.h"
#include "Console.h"
#include "HistoryManager.h"

#include "Freecell.h"
#include "FCBoard.h"

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	FCBoard board;
	Freecell game;
	game.SetModel(&board);
	for (int i = 0; i < 7; ++i)
		board.MoveCards(FCBoard::PLAY, FCBoard::PLAY, i, 7, 1);
	
	CardBtn c(Card(HEARTS, KING));
	c.SetPos(10, 18, Color::green);
	CardBtn c1(Card(CLUBS, QUEEN));
	c1.SetPos(10, 20, Color::green);
	CardBtn c2(Card(DIAMONDS, JACK));
	c2.SetPos(10, 22, Color::green);
	c2.Large();

	while (true)
	{
		Mouse::UpdateMouseState();

		c.Update();
		c1.Update();
		c2.Update();
		
		CUpdate();
	}
	
	
	cout << endl << endl << endl << endl;
	cout << endl << endl << endl << endl;
	cout << endl << endl << endl << endl;
	cout << endl << endl << endl << endl;
	cout << endl << endl << endl << endl;
	cout << endl << endl << endl << endl;
	cout << endl << endl << endl << endl;
	cout << endl << endl << endl << endl;
	cout << endl << endl << endl << endl;
	cout << endl << endl << endl << endl;
	//system("pause");
	/*MineSweeper minesweeper;

	bool running = true;
	while (running && !Keyboard::KeyPressed(VK_ESCAPE))
	{
		Mouse::UpdateMouseState();
		Keyboard::UpdateKeyboardState();

		running = minesweeper.Update();

		HistoryManager::Update();
		CUpdate();
	}*/

	return 0;
}
