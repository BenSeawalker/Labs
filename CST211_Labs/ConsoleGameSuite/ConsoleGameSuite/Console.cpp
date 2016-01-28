/************************************************************************
* Author:		Garrett Fleischer
* Filename:		Console.cpp
* Date Created:	1/15/16
* Modifications: N/A
*************************************************************************/

#include "Console.h"

///////////////////////////////////////////////////////////////
//	INITIALIZE SINGLETON
//////

Console Console::m_instance = Console();

//////
//	END INITIALIZE SINGLETON
///////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////
//	CTOR AND DTOR
//////

Console::Console(UINT width, UINT height, BOOL visiblity, UINT encoding)
	: m_ohandle(GetStdHandle(STD_OUTPUT_HANDLE)), m_ihandle(GetStdHandle(STD_INPUT_HANDLE)), m_width(width), m_height(height), m_buffer(nullptr)
{
	// Ensure that the console is in the correct encoding
	SetConsoleEncoding(encoding);

	// Ensure that the console can receive mouse events...
	EnableMouseEvents();

	// Resize the window
	Resize(width, height);

	// Cursor visibility
	SetCursorVisibility(visiblity);
}

Console::~Console()
{
	delete[] m_buffer;
	m_buffer = nullptr;
}

//////
//	END CTOR AND DTOR
///////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////
//	SINGLETON
//////

/************************************************************************
* Purpose: To get the singleton instance of this class
*
* Precondition:
*
* Postcondition:
*		Modifies:	N/A
*		Throws:		N/A
*		Returns:	A reference to the singleton instance
*************************************************************************/
Console & Console::GetInstance()
{
	return m_instance;
}

//////
//	END SINGLETON
///////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////
//	PUBLIC STATIC METHODS
//////

/************************************************************************
* Purpose: To create a color of the specified foreground and background
*
* Precondition:
*
* Postcondition:
*		Modifies:	N/A
*		Throws:		N/A
*		Returns:	The specified color
*************************************************************************/
COLOR Console::CMakeColor(COLOR foreground, COLOR background)
{
	return (foreground + CMakeBackground(background));
}

/************************************************************************
* Purpose: To create a color of the specified background
*
* Precondition:
*
* Postcondition:
*		Modifies:	N/A
*		Throws:		N/A
*		Returns:	The specified background with a black foreground
*************************************************************************/
COLOR Console::CMakeBackground(COLOR background)
{
	return background * 16;
}

//////
//	END PUBLIC STATIC METHODS
///////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////
//	PUBLIC METHODS
//////

/************************************************************************
* Purpose: To write a single character to the console at a specified position
*
* Precondition:
*		draw - whether or not to defer rendering
*
* Postcondition:
*		Modifies:	The console screen buffer
*		Throws:		N/A
*		Returns:	N/A
*************************************************************************/
void Console::Write(int x, int y, const char & c, COLOR color, bool draw)
{
	if (InBounds(x, y))
	{
		SetCursor(x, y);

		int index = (m_cursor.X + (m_cursor.Y * m_width));
		(m_buffer[index]).Char.AsciiChar = c;
		(m_buffer[index]).Attributes = color;

		if (draw)
			Draw();
	}
}

/************************************************************************
* Purpose: To write a string of characters to the console at a specified position
*
* Precondition:
*
* Postcondition:
*		Modifies:	The console screen buffer
*		Throws:		N/A
*		Returns:	N/A
*************************************************************************/
void Console::Write(int x, int y, const char * txt, COLOR color)
{
	for (UINT i = 0; i < strlen(txt); ++i)
		Write(x + i, y, txt[i], color, false);

	Draw();
}

/************************************************************************
* Purpose: To completely clear the screen with the given color
*
* Precondition:
*
* Postcondition:
*		Modifies:	The console screen buffer
*		Throws:		N/A
*		Returns:	N/A
*************************************************************************/
void Console::Clear(COLOR color)
{
	ClearBuffer(m_buffer, (m_width * m_height), color);
	Draw();
}

/************************************************************************
* Purpose: To clear a line on the screen with the given color
*
* Precondition:
*
* Postcondition:
*		Modifies:	The console screen buffer
*		Throws:		N/A
*		Returns:	N/A
*************************************************************************/
void Console::ClearLine(int line, COLOR color /*= Color::black*/)
{
	if (line < m_height)
	{
		int y = (line * m_width);
		for (int i = y; i < y + m_width && i < (m_width * m_height); ++i)
		{
			m_buffer[i].Char.AsciiChar = ' ';
			m_buffer[i].Attributes = color;
		}

		Draw();
	}
}

/************************************************************************
* Purpose: To clear a region on the screen with the given color
*
* Precondition:
*
* Postcondition:
*		Modifies:	The console screen buffer
*		Throws:		N/A
*		Returns:	N/A
*************************************************************************/
void Console::ClearRect(int x1, int y1, int x2, int y2, COLOR color)
{
	for (int y = y1; y < y2 && y < m_height; ++y)
	{
		for (int x = x1; x < x2 && x < m_width; ++x)
		{
			if (InBounds(x, y))
			{
				int index = (x + (y * m_width));
				m_buffer[index].Char.AsciiChar = ' ';
				m_buffer[index].Attributes = color;
			}
		}
	}
}

/************************************************************************
* Purpose: To check if a given coordinate is within the bounds of the console
*
* Precondition:
*
* Postcondition:
*		Modifies:	N/A
*		Throws:		N/A
*		Returns:	TRUE if the given coordinate is inside the bounds of the console
*************************************************************************/
bool Console::InBounds(int x, int y) const
{
	return (((x >= 0) && (x < m_width)) && ((y >= 0) && (y < m_height)));
}

//////
//	END PUBLIC METHODS
///////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////
//	GETTERS AND SETTERS
//////

/************************************************************************
* Purpose: To change whether or not the blinking cursor is visible
*
* Precondition:
*
* Postcondition:
*		Modifies:	The console cursor info
*		Throws:		N/A
*		Returns:	N/A
*************************************************************************/
void Console::SetCursorVisibility(BOOL visible)
{
	GetConsoleCursorInfo(m_ohandle, &m_cinf);
	m_cinf.bVisible = visible;
	SetConsoleCursorInfo(m_ohandle, &m_cinf);
}

/************************************************************************
* Purpose: To change the encoding of all characters on the screen
*
* Precondition:
*
* Postcondition:
*		Modifies:	The console screen buffer
*		Throws:		N/A
*		Returns:	N/A
*************************************************************************/
void Console::SetConsoleEncoding(UINT encoding)
{
	SetConsoleCP(encoding);
	SetConsoleOutputCP(encoding);
}

/************************************************************************
* Purpose: To resize BOTH the console window and the screen buffer
*
* Precondition:
*
* Postcondition:
*		Modifies:	The console screen buffer
*					The screen will be completely cleared with a white foreground and black background
*		Throws:		N/A
*		Returns:	N/A
*************************************************************************/
void Console::Resize(UINT width, UINT height)
{
	// inner size
	m_csbi.srWindow.Left = 0;
	m_csbi.srWindow.Top = 0;
	m_csbi.srWindow.Right = width - 1;
	m_csbi.srWindow.Bottom = height - 1;
	// buffer size
	SetConsoleScreenBufferSize(m_ohandle, { static_cast<SHORT>(width), static_cast<SHORT>(height) });

	// window size
	SetConsoleWindowInfo(m_ohandle, TRUE, &m_csbi.srWindow);

	// new buffer with new size
	CHAR_INFO * temp = new CHAR_INFO[width * height];
	ClearBuffer(temp, width * height, CMakeColor(Color::white, Color::black));

	// update old buffer
	delete[] m_buffer;
	m_buffer = temp;

	// set the new width and height
	m_width = width;
	m_height = height;

	// redraw the screen
	Draw();
}

/************************************************************************
* Purpose: To get the position of the text cursor in the window
*
* Precondition:
*
* Postcondition:
*		Modifies:	N/A
*		Throws:		N/A
*		Returns:	The position of the text cursor
*************************************************************************/
Coord Console::GetCursor() const
{
	return m_cursor;
}

/************************************************************************
* Purpose: To set the position of the text cursor in the window
*
* Precondition:
*
* Postcondition:
*		Modifies:	The position of the text cursor
*		Throws:		N/A
*		Returns:	N/A
*************************************************************************/
void Console::SetCursor(int x, int y)
{
	m_cursor.X = x;
	m_cursor.Y = y;
	Bound(m_cursor.X, m_cursor.Y);

	SetConsoleCursorPosition(m_ohandle, m_cursor);
}

/************************************************************************
* Purpose: To move the text cursor relative to its current position
*
* Precondition:
*
* Postcondition:
*		Modifies:	The position of the text cursor
*		Throws:		N/A
*		Returns:	N/A
*************************************************************************/
void Console::MoveCursor(int dx, int dy)
{
	m_cursor.X += dx;
	m_cursor.Y += dy;
	Bound(m_cursor.X, m_cursor.Y);

	SetConsoleCursorPosition(m_ohandle, m_cursor);
}

/************************************************************************
* Purpose: To get the current width of the console
*
* Precondition:
*
* Postcondition:
*		Modifies:	N/A
*		Throws:		N/A
*		Returns:	The current width of the console
*************************************************************************/
UINT Console::Width() const
{
	return m_width;
}

/************************************************************************
* Purpose: To get the current height of the console
*
* Precondition:
*
* Postcondition:
*		Modifies:	N/A
*		Throws:		N/A
*		Returns:	The current height of the console
*************************************************************************/
UINT Console::Height() const
{
	return m_height;
}

/************************************************************************
* Purpose: To get the output handle of the console
*
* Precondition:
*
* Postcondition:
*		Modifies:	N/A
*		Throws:		N/A
*		Returns:	The output handle of the console
*************************************************************************/
HANDLE & Console::OutputHandle()
{
	return m_ohandle;
}

/************************************************************************
* Purpose: To get the input handle of the console
*
* Precondition:
*
* Postcondition:
*		Modifies:	N/A
*		Throws:		N/A
*		Returns:	The input handle of the console
*************************************************************************/
HANDLE & Console::InputHandle()
{
	return m_ihandle;
}

//////
//	END GETTERS AND SETTERS
///////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////
//	PRIVATE METHODS
//////

/************************************************************************
* Purpose: To set the console mode to accept mouse events
*
* Precondition:
*
* Postcondition:
*		Modifies:	The console mode
*		Throws:		N/A
*		Returns:	N/A
*************************************************************************/
void Console::EnableMouseEvents()
{
	DWORD dwPreviousMode;
	GetConsoleMode(m_ohandle, &dwPreviousMode);

	DWORD dwNewMode = dwPreviousMode | ENABLE_MOUSE_INPUT | ENABLE_EXTENDED_FLAGS & ~ENABLE_QUICK_EDIT_MODE;
	SetConsoleMode(m_ohandle, dwNewMode);
}

/************************************************************************
* Purpose: To clear out the given buffer with null characters of the specified color
*
* Precondition:
*
* Postcondition:
*		Modifies:	The given buffer
*		Throws:		N/A
*		Returns:	N/A
*************************************************************************/
void Console::ClearBuffer(CHAR_INFO * buffer, UINT size, COLOR color)
{
	for (UINT i = 0; i < size; ++i)
	{
		buffer[i].Char.AsciiChar = '\0';
		buffer[i].Attributes = color;
	}
}

/************************************************************************
* Purpose: To bound a given set of coordinates to the width and height of the console
*
* Precondition:
*
* Postcondition:
*		Modifies:	The given coordinates
*		Throws:		N/A
*		Returns:	N/A
*************************************************************************/
void Console::Bound(int & x, int & y)
{
	if (x < 0)
		x = 0;
	else if (x >= int(m_width))
		x = m_width - 1;

	if (y < 0)
		y = 0;
	else if (y >= int(m_height))
		y = m_height - 1;
}

/************************************************************************
* Purpose: To write the local buffer to the screen buffer
*
* Precondition:
*
* Postcondition:
*		Modifies:	The screen buffer
*		Throws:		N/A
*		Returns:	N/A
*************************************************************************/
void Console::Draw()
{
	SMALL_RECT consoleWriteArea = m_csbi.srWindow;
	WriteConsoleOutputA(m_ohandle, m_buffer, { static_cast<SHORT>(m_width), static_cast<SHORT>(m_height) }, { 0, 0 }, &consoleWriteArea);
}

//////
//	END PRIVATE METHODS
///////////////////////////////////////////////////////////////