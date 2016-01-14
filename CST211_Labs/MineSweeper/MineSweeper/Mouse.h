#ifndef MOUSE_H
#define MOUSE_H

#include <Windows.h>

class Mouse
{
public:
	enum BUTTON { LEFT, MIDDLE, RIGHT };

	Mouse(HANDLE & input_handle, void(*MousePressed)(BUTTON btn));

	void UpdateMouseState();

	UINT x();
	UINT y();

private:
	void (*m_MousePressed)(BUTTON btn);

	HANDLE & m_handle;
	UINT m_x;
	UINT m_y;
};


#endif // Mouse_h__
