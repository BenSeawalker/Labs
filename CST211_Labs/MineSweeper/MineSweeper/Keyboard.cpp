#include "Keyboard.h"

Array<short> Keyboard::previous_keyboard_state = Array<short>(NUM_KEYS);
Array<short> Keyboard::current_keyboard_state = Array<short>(NUM_KEYS);

void Keyboard::UpdateKeyboardState()
{
	current_keyboard_state.Swap(previous_keyboard_state);
	for (UINT i = 0; i < NUM_KEYS; i++)
		current_keyboard_state[i] = GetAsyncKeyState(i);
}

bool Keyboard::KeyUp(int _key)
{
	return !current_keyboard_state[_key];
}

bool Keyboard::KeyDown(int _key)
{
	return current_keyboard_state[_key];
}

bool Keyboard::KeyPressed(int _key)
{
	return (!previous_keyboard_state[_key] && current_keyboard_state[_key]);
}

bool Keyboard::KeyReleased(int _key)
{
	return (previous_keyboard_state[_key] && !current_keyboard_state[_key]);
}