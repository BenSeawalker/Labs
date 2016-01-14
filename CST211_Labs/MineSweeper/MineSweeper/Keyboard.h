#ifndef KEYBOARD_H
#define KEYBOARD_H


#include <Windows.h>

#include "Array.h"

class Keyboard
{
public:
	static void UpdateKeyboardState();

	static bool KeyUp(int key);

	static bool KeyDown(int key);

	static bool KeyPressed(int key);

	static bool KeyReleased(int key);

private:
	static const int NUM_KEYS = 256;
	static Array<bool> previous_keyboard_state;
	static Array<bool> current_keyboard_state;
};


#endif // KEYBOARD_H