#include <crtdbg.h> 
#define _CRTDBG_MAP_ALLOC

#include "MineSweeper.h"

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	Console & console = Console::GetInstance();

	MineSweeper ms;

	bool running = true;
	while (running && !Keyboard::KeyPressed(VK_ESCAPE))
	{
		Mouse::UpdateMouseState(console.InputHandle());
		Keyboard::UpdateKeyboardState(console.InputHandle());

		running = ms.Update();
	}

	return 0;
}
