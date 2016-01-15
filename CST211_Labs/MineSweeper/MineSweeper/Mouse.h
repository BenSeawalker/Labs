#ifndef MOUSE_H
#define MOUSE_H

#include <Windows.h>
#include "Array.h"

class Mouse
{
public:
	enum BUTTON { LEFT, MIDDLE, RIGHT };

	//Mouse(HANDLE & input_handle, void(*MousePressed)(BUTTON btn));

	static void UpdateMouseState(HANDLE & input_handle);

	static bool BtnUp(BUTTON btn);

	static bool BtnDown(BUTTON btn);

	static bool BtnPressed(BUTTON btn);

	static bool BtnReleased(BUTTON btn);

	static bool Moved();

	static int X();
	static int Y();

private:
	// METHODS
	static void UpdatePosition(HANDLE & input_handle);

	// MEMBERS
	static const int NUM_BTNS = 3;
	static Array<SHORT> m_previous_state;
	static Array<SHORT> m_current_state;

	static int m_x;
	static int m_y;
	static bool m_moved;

	
};


#endif // Mouse_h__
