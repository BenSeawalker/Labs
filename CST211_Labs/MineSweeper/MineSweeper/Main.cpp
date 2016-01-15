#include "Board.h"

#include "Console.h"
#include "Keyboard.h"
#include "Mouse.h"
#include "Button.h"

#include <iostream>
using std::cin;

#define KeyPressed Keyboard::KeyPressed

void ButtonPressed(Button & btn);

Console & console = Console::GetInstance();

int main()
{
	
	console.Resize(100, 50);

	Button b = Button(10, 10, 0, "Hello", &ButtonPressed);
	Button b2 = Button(10, 15, 1, "World", &ButtonPressed, Color::blue, Color::red, Color::red, Color::blue);
	b2.Resize(3, 7);

	/*console.Clear(MakeBackground(Color::white));
	console.ClearLine(2, MakeBackground(Color::purple));
	console.ClearLine(4, MakeBackground(Color::purple));
	console.ClearLine(8, MakeBackground(Color::purple));
	console.ClearLine(16, MakeBackground(Color::purple));

	console.ClearRect(10, 20, 15, 25, MakeBackground(Color::green));*/

	console.SetCursor(5, 12);
	while (!KeyPressed(VK_ESCAPE))
	{
		Mouse::UpdateMouseState(console.InputHandle());
		b.Update();
		b2.Update();

		/*if (Mouse::Moved())
		{
			int mx = Mouse::X();
			int my = Mouse::Y();
		}

		if (Mouse::BtnDown(Mouse::LEFT))
		{
			int mx = Mouse::X();
			int my = Mouse::Y();

			console.SetCursor(mx, my);
			console.Write(console.GetCursor(), ' ', MakeBackground(Color::red));
		}
		if (Mouse::BtnDown(Mouse::RIGHT))
		{
			int mx = Mouse::X();
			int my = Mouse::Y();

			console.SetCursor(mx, my);
			console.Write(console.GetCursor(), ' ', MakeBackground(Color::white));
		}*/

		Keyboard::UpdateKeyboardState(console.InputHandle());
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

			console.Write({ x1, y1 }, ' ', MakeBackground(Color::grey));
			console.Write({ x2, y1 }, ' ', MakeBackground(Color::white));
			console.Write({ x1, y2 }, ' ', MakeBackground(Color::bright_white));
			console.Write({ x2, y2 }, ' ', MakeBackground(Color::blue));

			console.SetCursor(x1, y1);
		}

		console.Write({ 3, 3 }, Keyboard::String().c_str(), MakeBackground(Color::blue));
	}

	cin.sync();
	cin.ignore();

	return 0;
}


void ButtonPressed(Button & btn)
{
	string str = "You clicked: \"";
	str += btn.Text();
	str += "\" with ID: ";
	str += std::to_string(btn.ID());
	
	if (btn.ID() == 1)
		btn.Resize(11, 3);

	console.ClearLine(20);
	console.Write({ 10, 20 }, str.c_str(), MakeColor(Color::cyan));
}