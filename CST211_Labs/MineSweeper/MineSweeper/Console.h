#ifndef CONSOLE_H
#define CONSOLE_H

#include <Windows.h>
#include <cstring>

typedef WORD COLOR;

struct Color
{
	static const COLOR
		fdarkblue = 1,
		fgreen = 2,
		fcyan = 3,
		fdarkred = 4,
		fpurple = 5,
		fdarkyellow = 6,
		fwhite = 7,
		fgrey = 8,
		fblue = 9,
		flime = 10,
		fturquoise = 11,
		fred = 12,
		fpink = 13,
		fyellow = 14,
		fbrightwhite = 15,

		bdarkblue = 16,
		bgreen = 17,
		bcyan = 18,
		bdarkred = 19,
		bpurple = 20,
		bdarkyellow = 21,
		bwhite = 22,
		bgrey = 23,
		bblue = 24,
		blime = 25,
		bturquoise = 26,
		bred = 27,
		bpink = 28,
		byellow = 29,
		bbrightwhite = 30;
};


class Console
{
public:
	// SINGLETON
	static Console & GetInstance();

	// METHODS
	void SetCursorVisibility(bool visible);
	void SetConsoleEncoding(UINT encoding);

	void Resize(UINT width, UINT height);

	void Write(COORD pos, const char & txt, COLOR color = Color::fwhite, bool draw = true);
	void Write(COORD pos, const char * txt, COLOR color = Color::fwhite);

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

	void Bound(int & x, int & y);

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
