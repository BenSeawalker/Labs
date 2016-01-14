#include "Keyboard.h"

Array<bool> Keyboard::previous_keyboard_state = Array<bool>(NUM_KEYS);
Array<bool> Keyboard::current_keyboard_state = Array<bool>(NUM_KEYS);

void Keyboard::UpdateKeyboardState()
{
	previous_keyboard_state = current_keyboard_state;
	//current_keyboard_state.Swap(previous_keyboard_state);
	for (UINT i = 0; i < NUM_KEYS; ++i)
		current_keyboard_state[i] = bool(GetAsyncKeyState(i));
}

bool Keyboard::KeyUp(int key)
{
	return !current_keyboard_state[key];
}

bool Keyboard::KeyDown(int key)
{
	return current_keyboard_state[key];
}

bool Keyboard::KeyPressed(int key)
{
	return (!previous_keyboard_state[key] && current_keyboard_state[key]);
}

bool Keyboard::KeyReleased(int key)
{
	return (previous_keyboard_state[key] && !current_keyboard_state[key]);
}