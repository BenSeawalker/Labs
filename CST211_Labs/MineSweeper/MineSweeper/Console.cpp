#include "Console.h"

// INITIALIZE STATIC VARS
Console * Console::m_instance = nullptr;


///////////////////////////////////////////////////////////////
//	C'TORS & D'TOR
//////

Console::Console(UINT width, UINT height, bool visible, UINT encoding)
	: m_ohandle(GetStdHandle(STD_OUTPUT_HANDLE)), m_ihandle(GetStdHandle(STD_INPUT_HANDLE)), m_width(0), m_height(0), m_buffer(nullptr)
{
	// ensure that the console is in the correct encoding
	SetConsoleEncoding(encoding);

	// resize the window
	Resize(width, height);

	// cursor visibility
	SetCursorVisibility(visible);
}

Console::~Console()
{
	m_instance = nullptr;
}

//////
//	END C'TORS & D'TOR
///////////////////////////////////////////////////////////////

Console & Console::GetInstance()
{
	if (!m_instance)
		m_instance = new Console();

	return *m_instance;
}

void Console::SetCursorVisibility(bool visible)
{
	if (visible != m_cinf.bVisible)
	{
		GetConsoleCursorInfo(m_ohandle, &m_cinf);
		m_cinf.bVisible = visible;
		SetConsoleCursorInfo(m_ohandle, &m_cinf);
	}
}

void Console::SetConsoleEncoding(UINT encoding)
{
	SetConsoleCP(encoding);
	SetConsoleOutputCP(encoding);
}

void Console::Resize(UINT width, UINT height)
{
	// inner size
	m_csbi.srWindow.Left = 0;
	m_csbi.srWindow.Top = 0;
	m_csbi.srWindow.Right = width - 1;
	m_csbi.srWindow.Bottom = height - 1;
	SetConsoleWindowInfo(m_ohandle, TRUE, &m_csbi.srWindow);

	// window size
	SetConsoleScreenBufferSize(m_ohandle, { width, height });


	// new buffer with new size
	CHAR_INFO * temp = new CHAR_INFO[width * height];
	ClearBuffer(temp, width * height, Color::fwhite);

	// copy old data to new buffer
	//CopyBuffer(temp, m_buffer, width, height, m_width, m_height);

	// update old buffer
	delete[] m_buffer;
	m_buffer = temp;

	Draw();
	
	// set the new width and height
	m_width = width;
	m_height = height;
}

void Console::Write(COORD pos, const char & c, COLOR color, bool draw)
{
	SetCursor(pos.X, pos.Y);

	(m_buffer[m_cursor.X + (m_cursor.Y * m_width)]).Char.AsciiChar = c;
	(m_buffer[m_cursor.X + (m_cursor.Y * m_width)]).Attributes = color;

	if (draw)
		Draw();
}

void Console::Write(COORD pos, const char * txt, COLOR color)
{
	for (UINT i = 0; i < strlen(txt); ++i)
		Write({ pos.X + i, pos.Y }, txt[i], color, false);

	Draw();
}


void Console::CopyBuffer(CHAR_INFO * dest, CHAR_INFO * source, UINT destWidth, UINT destHeight, UINT sourceWidth, UINT sourceHeight)
{
	for (UINT i = 0; i < min(destWidth * destHeight, sourceWidth * sourceHeight); ++i)
		dest[i] = source[i];
}

void Console::ClearBuffer(CHAR_INFO * buffer, UINT size, COLOR color)
{
	for (UINT i = 0; i < size; ++i)
	{
		buffer[i].Char.AsciiChar = '\0';
		buffer[i].Attributes = color;
	}
}

void Console::Bound(int & x, int & y)
{
	if (x < 0)
		x = 0;
	else if (x >= m_width)
		x = m_width - 1;

	if (y < 0)
		y = 0;
	else if (y >= m_height)
		y = m_height - 1;
}

COORD Console::GetCursor()
{
	return m_cursor;
}

void Console::SetCursor(int x, int y)
{
	Bound(x, y);
	m_cursor.X = x;
	m_cursor.Y = y;
	SetConsoleCursorPosition(m_ohandle, m_cursor);
}

void Console::MoveCursor(int dx, int dy)
{
	m_cursor.X += dx;
	m_cursor.Y += dy;
	SetConsoleCursorPosition(m_ohandle, m_cursor);
}

UINT Console::Width()
{
	return m_width;
}

UINT Console::Height()
{
	return m_height;
}

HANDLE & Console::OutputHandle()
{
	return m_ohandle;
}

HANDLE & Console::InputHandle()
{
	return m_ihandle;
}


void Console::Draw()
{
	SMALL_RECT consoleWriteArea = m_csbi.srWindow;
	WriteConsoleOutputA(m_ohandle, m_buffer, { m_width, m_height }, { 0, 0 }, &consoleWriteArea);
}


