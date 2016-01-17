#include "Console.h"

// INITIALIZE STATIC VARS
Console Console::m_instance = Console();


///////////////////////////////////////////////////////////////
//	C'TORS & D'TOR
//////

Console::Console(UINT width, UINT height, BOOL visiblity, UINT encoding)
	: m_ohandle(GetStdHandle(STD_OUTPUT_HANDLE)), m_ihandle(GetStdHandle(STD_INPUT_HANDLE)), m_width(width), m_height(height), m_buffer(nullptr)
{
	// ensure that the console is in the correct encoding
	SetConsoleEncoding(encoding);

	// resize the window
	Resize(width, height);

	// cursor visibility
	SetCursorVisibility(visiblity);
}

Console::~Console()
{
	delete[] m_buffer;
	m_buffer = nullptr;
}

//////
//	END C'TORS & D'TOR
///////////////////////////////////////////////////////////////

Console & Console::GetInstance()
{
	return m_instance;
}

void Console::SetCursorVisibility(BOOL visible)
{
	GetConsoleCursorInfo(m_ohandle, &m_cinf);
	m_cinf.bVisible = visible;
	SetConsoleCursorInfo(m_ohandle, &m_cinf);
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
	// buffer size
	SetConsoleScreenBufferSize(m_ohandle, { width, height });

	// window size
	SetConsoleWindowInfo(m_ohandle, TRUE, &m_csbi.srWindow);

	// new buffer with new size
	CHAR_INFO * temp = new CHAR_INFO[width * height];
	ClearBuffer(temp, width * height, CMakeColor(Color::white, Color::black));

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
	if (InBounds(pos))
	{
		SetCursor(pos.X, pos.Y);

		int index = (m_cursor.X + (m_cursor.Y * m_width));
		(m_buffer[index]).Char.AsciiChar = c;
		(m_buffer[index]).Attributes = color;

		if (draw)
			Draw();
	}
}

void Console::Write(COORD pos, const char * txt, COLOR color)
{
	for (UINT i = 0; i < strlen(txt); ++i)
	{
		if (InBounds({ pos.X + i, pos.Y }))
		{
			SetCursor(pos.X + i, pos.Y);
			int index = (m_cursor.X + (m_cursor.Y * m_width));
			(m_buffer[index]).Char.AsciiChar = txt[i];
			(m_buffer[index]).Attributes = color;
		}
	}

	Draw();
}


void Console::Clear(COLOR color)
{
	ClearBuffer(m_buffer, (m_width * m_height), color);
	Draw();
}

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

void Console::ClearRect(int x1, int y1, int x2, int y2, COLOR color)
{
	for (int y = y1; y < y2 && y < m_height; ++y)
	{
		for (int x = x1; x < x2 && x < m_width; ++x)
		{
			if (InBounds({ x, y }))
			{
				int index = (x + (y * m_width));
				m_buffer[index].Char.AsciiChar = ' ';
				m_buffer[index].Attributes = color;
			}
		}
	}
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
		buffer[i].Char.AsciiChar = ' ';
		buffer[i].Attributes = color;
	}
}

void Console::Bound(SHORT & x, SHORT & y)
{
	if (x < 0)
		x = 0;
	else if (x >= SHORT(m_width))
		x = m_width - 1;

	if (y < 0)
		y = 0;
	else if (y >= SHORT(m_height))
		y = m_height - 1;
}

COORD Console::GetCursor()
{
	return m_cursor;
}

void Console::SetCursor(int x, int y)
{
	m_cursor.X = x;
	m_cursor.Y = y;
	Bound(m_cursor.X, m_cursor.Y);

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


bool Console::InBounds(COORD pos)
{
	return (((pos.X >= 0) && (pos.X < m_width)) && ((pos.Y >= 0) && (pos.Y < m_height)));
}

COLOR Console::CMakeColor(COLOR foreground, COLOR background)
{
	return (foreground + CMakeBackground(background));
}

COLOR Console::CMakeBackground(COLOR background)
{
	return background * 16;
}

void Console::Draw()
{
	SMALL_RECT consoleWriteArea = m_csbi.srWindow;
	WriteConsoleOutputA(m_ohandle, m_buffer, { m_width, m_height }, { 0, 0 }, &consoleWriteArea);
}


