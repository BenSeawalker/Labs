#include "Mouse.h"


Array<bool> Mouse::previous_mouse_state = Array<bool>(NUM_BTNS);
Array<bool> Mouse::current_mouse_state = Array<bool>(NUM_BTNS);

int Mouse::m_x = 0;
int Mouse::m_y = 0;
bool Mouse::m_moved = false;

//Mouse::Mouse(HANDLE & input_handle, void(*MousePressed)(BUTTON btn))
//	: m_handle(input_handle)
//{
//	m_MousePressed = MousePressed;
//}

void Mouse::UpdateMouseState(HANDLE & input_handle)
{
	//current_mouse_state.Swap(previous_mouse_state);
	
	// swap the current state into the previous
	previous_mouse_state = current_mouse_state;

	// update current mouse state
	current_mouse_state[LEFT] = bool(GetAsyncKeyState(VK_LBUTTON));
	current_mouse_state[MIDDLE] = bool(GetAsyncKeyState(VK_MBUTTON));
	current_mouse_state[RIGHT] = bool(GetAsyncKeyState(VK_RBUTTON));

	// UPDATE MOUSE POSITION
	{
		// How many events have happened?
		DWORD numEvents = 0;

		// How many events have we read from the console?
		DWORD numEventsRead = 0;

		GetNumberOfConsoleInputEvents(input_handle, &numEvents);

		// If it's not zero (something happened...)
		if (numEvents != 0)
		{
			// Create a buffer of that size to store the events
			INPUT_RECORD *eventBuffer = new INPUT_RECORD[numEvents];

			// Read the console events into that buffer, and save how
			// many events have been read into numEventsRead.
			ReadConsoleInput(input_handle, eventBuffer, numEvents, &numEventsRead);
			
			// Now, cycle through all the events that have happened:
			bool mouse_handled = false;
			for (DWORD i = 0; i < numEventsRead && !mouse_handled; ++i)
			{
				if (eventBuffer[i].EventType == MOUSE_EVENT)
				{
					// POSITION
					int old_x = m_x;
					int old_y = m_y;
					
					m_x = eventBuffer[i].Event.MouseEvent.dwMousePosition.X;
					m_y = eventBuffer[i].Event.MouseEvent.dwMousePosition.Y;

					m_moved = (m_x != old_x || m_y != old_y);

					mouse_handled = true;
				}
			}
		}
	}
}

bool Mouse::BtnUp(BUTTON btn)
{
	return !current_mouse_state[btn];
}

bool Mouse::BtnDown(BUTTON btn)
{
	return current_mouse_state[btn];
}

bool Mouse::BtnPressed(BUTTON btn)
{
	return (!previous_mouse_state[btn] && current_mouse_state[btn]);
}

bool Mouse::BtnReleased(BUTTON btn)
{
	return (previous_mouse_state[btn] && !current_mouse_state[btn]);
}


bool Mouse::Moved()
{
	return m_moved;
}

int Mouse::x()
{
	return m_x;
}

int Mouse::y()
{
	return m_y;
}