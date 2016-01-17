#include "crtdbg_new.h"

#include "MineSweeper.h"

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	Console & console = Console::GetInstance();

	MineSweeper ms;

	bool running = true;
	while (running)
	{
		Mouse::UpdateMouseState(console.InputHandle());
		Keyboard::UpdateKeyboardState(console.InputHandle());

		running = (!Keyboard::KeyPressed(VK_ESCAPE) && ms.Update());
	}

	return 0;
}
