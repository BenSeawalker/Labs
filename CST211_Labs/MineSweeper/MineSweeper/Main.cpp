#include "Board.h"

#include "Console.h"
#include "Keyboard.h"
#include "Mouse.h"

#include <iostream>
using std::cin;

#define KeyPressed Keyboard::KeyPressed
#define  Block 0xDB

void MousePressed(Mouse::BUTTON btn);

int main()
{
	Console & console = Console::GetInstance();
	console.Resize(80, 40);

	console.SetCursor(5, 12);
	while (!KeyPressed(VK_ESCAPE))
	{
		Mouse::UpdateMouseState(console.InputHandle());
		if (Mouse::BtnDown(Mouse::LEFT))
		{
			int mx = Mouse::x();
			int my = Mouse::y();

			console.SetCursor(mx, my);
			console.Write(console.GetCursor(), 0xDB, Color::fred);
		}

		Keyboard::UpdateKeyboardState();
		int dx = (KeyPressed(VK_RIGHT) - KeyPressed(VK_LEFT)) * 2;
		int dy = (KeyPressed(VK_DOWN) - KeyPressed(VK_UP)) * 2;

		// if a key was actually pressed...
		if (dx != 0 || dy != 0)
		{
			console.MoveCursor(dx, dy);

			int x1 = console.GetCursor().X,
				x2 = x1 + 1,
				y1 = console.GetCursor().Y,
				y2 = y1 + 1;

			console.Write({x1, y1}, Block, Color::fcyan);
			console.Write({ x2, y1 }, Block, Color::fcyan);
			console.Write({ x1, y2 }, Block, Color::fcyan);
			console.Write({ x2, y2 }, Block, Color::fcyan);

			console.SetCursor(x1, y1);
		}
	}

	cin.sync();
	cin.ignore();

	return 0;
}