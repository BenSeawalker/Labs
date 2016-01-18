/************************************************************************
* Author:		Garrett Fleischer
* Filename:		Console.h
* Date Created:	1/15/16
* Modifications: N/A
*************************************************************************/

#ifndef CONSOLE_H
#define CONSOLE_H

#include <Windows.h>
#include <cstring>
#include "Exception.h"

// CONTAINS ALL AVAILABLE COLORS IN THE CONSOLE
typedef WORD COLOR;

struct Color
{
	static const COLOR
		black = 0,
		dark_blue = 1,
		green = 2,
		cyan = 3,
		dark_red = 4,
		purple = 5,
		dark_yellow = 6,
		white = 7,
		grey = 8,
		blue = 9,
		lime = 10,
		turquoise = 11,
		red = 12,
		pink = 13,
		yellow = 14,
		bright_white = 15;
};

// MACROS TO SAVE TYPING
#define MakeColor Console::CMakeColor
#define MakeBackground Console::CMakeBackground


/************************************************************************
* Class: Console
*
* Purpose: This class provides methods for manipulating the Windows console
*
* Manager functions:
*		GetInstance()
*
*	Private Console(UINT width = 80, UINT height = 40, BOOL visiblity = false, UINT encoding = 437)
*
*	~Console()
*
* Methods:
*	Public:
*		SetCursorVisibility(BOOL visiblity)
*			Set whether or not the cursor visibly blinks at its current location
*
*		SetConsoleEncoding(UINT encoding)
*			Change the encoding of characters displayed in the console
*
*		Resize(UINT width, UINT height)
*			Change the size of the window and screen buffer
*
*		CMakeColor(COLOR foreground = Color::white, COLOR background = Color::black)
*			Creates the Attribute value of foreground and background of a cell in the console
*
*		COLOR CMakeBackground(COLOR background)
*			Creates a color of the specified background with a black foreground
*
*		Write(COORD pos, const char & txt, COLOR color = Color::white, bool draw = true)
*			Writes a single character at the specified position. draw = whether or not to redraw the buffer
*
*		void Write(COORD pos, const char * txt, COLOR color = Color::white)
*			Writes a string to the console starting at the specified position. (does not wrap)
*
*	Private:
*		UpdatePosition(HANDLE & input_handle)
*
*************************************************************************/
class Console
{
public:
	// SINGLETON
	static Console & GetInstance();

	// DTOR
	~Console();

	// STATIC METHODS
	static COLOR CMakeColor(COLOR foreground = Color::white, COLOR background = Color::black);
	static COLOR CMakeBackground(COLOR background);

	// METHODS
	void Write(COORD pos, const char & txt, COLOR color = Color::white, bool draw = true);
	void Write(COORD pos, const char * txt, COLOR color = Color::white);

	void Clear(COLOR color = Color::black);
	void ClearLine(int line, COLOR color = Color::black);
	void ClearRect(int x1, int y1, int x2, int y2, COLOR color = Color::black);

	bool InBounds(COORD pos);

	// GETTERS AND SETTERS
	void SetCursorVisibility(BOOL visiblity);
	void SetConsoleEncoding(UINT encoding);

	void Resize(UINT width, UINT height);

	COORD GetCursor();
	void SetCursor(int x, int y);
	void MoveCursor(int dx, int dy);

	UINT Width();
	UINT Height();

	HANDLE & OutputHandle();
	HANDLE & InputHandle();

private:
	// CTOR
	Console(UINT width = 80, UINT height = 40, BOOL visiblity = false, UINT encoding = 437);

	// METHODS
	void ClearBuffer(CHAR_INFO * buffer, UINT size, COLOR color);

	void Bound(SHORT & x, SHORT & y);

	void Draw();

	// SINGLETON
	static Console m_instance;

	// MEMBERS
	HANDLE						m_ohandle;
	HANDLE						m_ihandle;
	CONSOLE_SCREEN_BUFFER_INFO	m_csbi;
	CHAR_INFO *					m_buffer;
	CONSOLE_CURSOR_INFO			m_cinf;
	COORD						m_cursor;
	int							m_width;
	int							m_height;
	
};


#endif // CONSOLE_H
