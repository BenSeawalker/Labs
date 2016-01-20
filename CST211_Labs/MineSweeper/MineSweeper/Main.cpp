#include "crtdbg_new.h"

#include "MineSweeper.h"

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	Console & console = Console::GetInstance();

	MineSweeper minesweeper;

	bool running = true;
	while (running && !Keyboard::KeyPressed(VK_ESCAPE))
	{
		Mouse::UpdateMouseState(console.InputHandle());
		Keyboard::UpdateKeyboardState();

		running = minesweeper.Update();
	}

	return 0;
}
