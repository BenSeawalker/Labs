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

	static int x();
	static int y();

private:
	static const int NUM_BTNS = 3;
	//void (*m_MousePressed)(BUTTON btn);

	static int m_x;
	static int m_y;
	static bool m_moved;

	static Array<bool> previous_mouse_state;
	static Array<bool> current_mouse_state;
};


#endif // Mouse_h__
