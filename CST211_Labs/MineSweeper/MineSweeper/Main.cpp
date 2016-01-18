#include "crtdbg_new.h"

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
		Keyboard::UpdateKeyboardState();

		running = ms.Update();

		/*if (Keyboard::KeyPressed(VK_BACK))
			console.ClearLine(10);
		console.Write({ 5, 10 }, Keyboard::String().c_str());*/
	}

	return 0;
}
