#ifndef KEYBOARD_H
#define KEYBOARD_H


#include <Windows.h>
#include <conio.h>
#include <string>
using std::string;

#include "Array.h"

class Keyboard
{
public:
	static void UpdateKeyboardState(HANDLE & input_handle);

	static bool KeyUp(int key);

	static bool KeyDown(int key);

	static bool KeyPressed(int key);

	static bool KeyReleased(int key);

	static string String();

private:
	// METHODS
	static void UpdateString(HANDLE & input_handle);

	// MEMBERS
	static const int NUM_KEYS = 256;
	static Array<SHORT> m_previous_state;
	static Array<SHORT> m_current_state;

	static string m_string;
};


#endif // KEYBOARD_H