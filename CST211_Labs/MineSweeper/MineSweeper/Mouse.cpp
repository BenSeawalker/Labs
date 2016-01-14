#include "Mouse.h"

Mouse::Mouse(HANDLE & input_handle, void(*MousePressed)(BUTTON btn))
	: m_handle(input_handle)
{
	m_MousePressed = MousePressed;
}

void Mouse::UpdateMouseState()
{
	// How many events have happened?
	DWORD numEvents = 0;

	// How many events have we read from the console?
	DWORD numEventsRead = 0;

	GetNumberOfConsoleInputEvents(m_handle, &numEvents);

	// If it's not zero (something happened...)
	if (numEvents != 0)
	{
		// Create a buffer of that size to store the events
		INPUT_RECORD *eventBuffer = new INPUT_RECORD[numEvents];

		// Read the console events into that buffer, and save how
		// many events have been read into numEventsRead.
		ReadConsoleInput(m_handle, eventBuffer, numEvents, &numEventsRead);

		// Now, cycle through all the events that have happened:
		for (DWORD i = 0; i < numEventsRead; ++i)
		{
			if (eventBuffer[i].EventType == MOUSE_EVENT)
			{
				// POSITION
				m_x = eventBuffer[i].Event.MouseEvent.dwMousePosition.X;
				m_y = eventBuffer[i].Event.MouseEvent.dwMousePosition.Y;

				// LEFT CLICK
				if (eventBuffer[i].Event.MouseEvent.dwButtonState & FROM_LEFT_1ST_BUTTON_PRESSED)
				{
					m_MousePressed(LEFT);
				}
				// RIGHT CLICK
				else if (eventBuffer[i].Event.MouseEvent.dwButtonState & RIGHTMOST_BUTTON_PRESSED)
				{
					m_MousePressed(RIGHT);
				}
				// MIDDLE CLICK
				else if (eventBuffer[i].Event.MouseEvent.dwButtonState & FROM_LEFT_2ND_BUTTON_PRESSED)
				{
					m_MousePressed(MIDDLE);
				}
			}
		}
	}
}

UINT Mouse::x()
{
	return m_x;
}


UINT Mouse::y()
{
	return m_y;
}