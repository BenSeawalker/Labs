#include "Keyboard.h"

Array<SHORT> Keyboard::m_previous_state = Array<SHORT>(NUM_KEYS);
Array<SHORT> Keyboard::m_current_state = Array<SHORT>(NUM_KEYS);

string Keyboard::m_string = "";


void Keyboard::UpdateKeyboardState(HANDLE & input_handle)
{
	m_previous_state = m_current_state;
	for (UINT i = 0; i < NUM_KEYS; ++i)
		m_current_state[i] = GetAsyncKeyState(i);

	/*if (KeyDown(VK_BACK))
		m_string.resize(m_string.size() - 1);
	else
		m_string += getch();*/

	UpdateString(input_handle);
}

bool Keyboard::KeyUp(int key)
{
	return !m_current_state[key];
}

bool Keyboard::KeyDown(int key)
{
	return (m_current_state[key] > 0);
}

bool Keyboard::KeyPressed(int key)
{
	return (!m_previous_state[key] && m_current_state[key]);
}

bool Keyboard::KeyReleased(int key)
{
	return (m_previous_state[key] && !m_current_state[key]);
}


string Keyboard::String()
{
	return m_string;
}

void Keyboard::UpdateString(HANDLE & input_handle)
{
	/*if (kbhit())
	{
	m_string += getch();
	}*/

	/*DWORD events;
	INPUT_RECORD buffer;
	PeekConsoleInput(input_handle, &buffer, 1, &events);

	if (events > 0)
	{
		ReadConsoleInput(input_handle, &buffer, 1, &events);
		m_string += buffer.Event.KeyEvent.uChar.AsciiChar;
	}*/

	//DWORD numEvents = 0;
	//DWORD numEventsRead = 0;

	//GetNumberOfConsoleInputEvents(input_handle, &numEvents);

	//if (numEvents != 0)
	//{
	//	// Create a buffer of that size to store the events
	//	INPUT_RECORD *eventBuffer = new INPUT_RECORD[numEvents];

	//	// Read the console events into that buffer, and save how
	//	// many events have been read into numEventsRead.
	//	ReadConsoleInput(input_handle, eventBuffer, numEvents, &numEventsRead);

	//	// Now, cycle through all the events that have happened:
	//	bool mouse_handled = false;
	//	for (DWORD i = 0; i < numEventsRead && !mouse_handled; ++i)
	//	{
	//		if (eventBuffer[i].EventType == KEY_EVENT)
	//		{
	//			/*if (eventBuffer[i].Event.KeyEvent.bKeyDown == VK_BACK)
	//				m_string.resize(m_string.size() - 1);
	//			else*/
	//				m_string += eventBuffer[i].Event.KeyEvent.uChar.AsciiChar;
	//		}
	//	}
	//}
}

