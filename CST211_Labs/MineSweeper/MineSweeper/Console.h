#ifndef CONSOLE_H
#define CONSOLE_H

#include <Windows.h>
#include <cstring>

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


#define MakeColor Console::CMakeColor
#define MakeBackground Console::CMakeBackground


class Console
{
public:
	// SINGLETON
	static Console & GetInstance();

	// METHODS
	void SetCursorVisibility(BOOL visible);
	void SetConsoleEncoding(UINT encoding);

	void Resize(UINT width, UINT height);

	static COLOR CMakeColor(COLOR foreground = Color::white, COLOR background = Color::black);
	static COLOR CMakeBackground(COLOR background);

	void Write(COORD pos, const char & txt, COLOR color = Color::white, bool draw = true);
	void Write(COORD pos, const char * txt, COLOR color = Color::white);

	void Clear(COLOR color = Color::black);
	void ClearLine(UINT line, COLOR color = Color::black);
	void ClearRect(int x1, int y1, int x2, int y2, COLOR color = Color::black);

	COORD GetCursor();
	void SetCursor(int x, int y);
	void MoveCursor(int dx, int dy);

	UINT Width();
	UINT Height();

	HANDLE & OutputHandle();
	HANDLE & InputHandle();

	

private:
	// CTOR AND DTOR
	Console(UINT width = 80, UINT height = 40, bool visible = false, UINT encoding = 437);
	~Console();

	// METHODS
	void CopyBuffer(CHAR_INFO * dest, CHAR_INFO * source, UINT destWidth, UINT destHeight, UINT sourceWidth, UINT sourceHeight);
	void ClearBuffer(CHAR_INFO * buffer, UINT size, COLOR color);

	void Bound(SHORT & x, SHORT & y);

	void Draw();

	// SINGLETON
	static Console * m_instance;

	// MEMBERS
	HANDLE						m_ohandle;
	HANDLE						m_ihandle;
	CONSOLE_SCREEN_BUFFER_INFO	m_csbi;
	CONSOLE_CURSOR_INFO			m_cinf;
	COORD						m_cursor;
	UINT						m_width;
	UINT						m_height;
	CHAR_INFO *					m_buffer;
	
};


#endif // CONSOLE_H
