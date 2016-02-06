/*****************************************************************************************
Author:			Garrett Fleischer
Filename:		Main.cpp
Date Created:	1/12/16
Modifications:
		1/27/16 - FIXED NARROWING CONVERSION ERRORS IN VS 2015+
		2/2/16 - Updated main to use improved console drawing.

Lab/Assignment: L1

Overview: Minesweeper game

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

#include "HomeArea.h"

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	HomeArea home;
	Card ace = Card(HEARTS, ACE);
	Card two = Card(HEARTS, 2);
	Card tri = Card(HEARTS, 3);
	Card tri2 = Card(CLUBS, 3);
	Card fi = Card(HEARTS, 5);

	cout << home.IsValid(ace, 0) << endl;
	home.AddCard(ace, 0);
	cout << home.IsValid(two, 0) << endl;
	home.AddCard(two, 0);
	cout << home.IsValid(tri2, 0) << endl;
	cout << home.IsValid(tri, 0) << endl;
	home.AddCard(tri, 0);
	cout << home.IsValid(fi, 0) << endl;


	/*Console & console = Console::GetInstance();

	MineSweeper minesweeper;

	bool running = true;
	while (running && !Keyboard::KeyPressed(VK_ESCAPE))
	{
		Mouse::UpdateMouseState();
		Keyboard::UpdateKeyboardState();

		running = minesweeper.Update();

		HistoryManager::Update();
		console.Update();
	}*/

	return 0;
}
