#include "Mouse.h"

Array<SHORT> Mouse::m_previous_state = Array<SHORT>(NUM_BTNS);
Array<SHORT> Mouse::m_current_state = Array<SHORT>(NUM_BTNS);

int Mouse::m_x = 0;
int Mouse::m_y = 0;
bool Mouse::m_moved = false;

void Mouse::UpdateMouseState(HANDLE & input_handle)
{
	// swap the current state into the previous
	m_previous_state = m_current_state;

	// update current mouse state
	m_current_state[LEFT] = GetAsyncKeyState(VK_LBUTTON);
	m_current_state[MIDDLE] = GetAsyncKeyState(VK_MBUTTON);
	m_current_state[RIGHT] = GetAsyncKeyState(VK_RBUTTON);

	UpdatePosition(input_handle);
}

bool Mouse::BtnUp(BUTTON btn)
{
	return !m_current_state[btn];
}

bool Mouse::BtnDown(BUTTON btn)
{
	return (m_current_state[btn] > 0);
}

bool Mouse::BtnPressed(BUTTON btn)
{
	return (!m_previous_state[btn] && m_current_state[btn]);
}

bool Mouse::BtnReleased(BUTTON btn)
{
	return (m_previous_state[btn] && !m_current_state[btn]);
}


bool Mouse::Moved()
{
	return m_moved;
}

int Mouse::X()
{
	return m_x;
}

int Mouse::Y()
{
	return m_y;
}



void Mouse::UpdatePosition(HANDLE & input_handle)
{
	DWORD numEvents = 0;
	DWORD numEventsRead = 0;

	GetNumberOfConsoleInputEvents(input_handle, &numEvents);

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

		delete[] eventBuffer;
	}
}