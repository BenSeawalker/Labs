#ifndef KEYBOARD_H
#define KEYBOARD_H


#include <Windows.h>

#include "Array.h"

class Keyboard
{
public:
	static void UpdateKeyboardState();

	static bool KeyUp(int _key);

	static bool KeyDown(int _key);

	static bool KeyPressed(int _key);

	static bool KeyReleased(int _key);

private:
	static const int NUM_KEYS = 256;
	static Array<short> previous_keyboard_state;
	static Array<short> current_keyboard_state;
};


#endif // KEYBOARD_H