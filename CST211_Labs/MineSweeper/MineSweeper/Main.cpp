#include "Board.h"

#include "Console.h"
#include "Keyboard.h"
#include "Mouse.h"

#include <iostream>
using std::cin;

#define KeyPressed Keyboard::KeyPressed

void MousePressed(Mouse::BUTTON btn);

Console & console = Console::GetInstance();
Mouse mouse(console.InputHandle(), &MousePressed);

int main()
{

	console.Write({ 5, 10 }, "лллллллллллллллллллллллллллллллллллл", Color::fgrey);
	console.Write({ 5, 11 }, "лллллллллллллллллллллллллллллллллллл", Color::fwhite);

	console.SetCursor(5, 12);
	while (!KeyPressed(VK_ESCAPE))
	{
		mouse.UpdateMouseState();

		Keyboard::UpdateKeyboardState();
		int dx = KeyPressed(VK_RIGHT) - KeyPressed(VK_LEFT);
		int dy = KeyPressed(VK_DOWN) - KeyPressed(VK_UP);

		// if a key was actually pressed...
		if (dx || dy)
		{
			console.MoveCursor(dx, dy);
			console.Write(console.GetCursor(), 0xDB, Color::fcyan);
		}
	}

	cin.sync();
	cin.ignore();

	return 0;
}


void MousePressed(Mouse::BUTTON btn)
{
	int mx = mouse.x();
	int my = mouse.y();

	console.SetCursor(mx, my);
	console.Write(console.GetCursor(), 0xDB, Color::fred);
}