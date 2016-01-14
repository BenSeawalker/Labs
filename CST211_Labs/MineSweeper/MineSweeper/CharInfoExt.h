#ifndef CHARINFOEXT_H
#define CHARINFOEXT_H


#include <Windows.h>

class CharInfoExt
{
public:
	CharInfoExt();
	CharInfoExt(const CharInfoExt & copy);

	~CharInfoExt();

	CharInfoExt & operator=(const CharInfoExt & rhs);

	char & Char();
	WORD & Attributes();

	CHAR_INFO Info();

	operator CHAR_INFO();

private:
	CHAR_INFO m_info;
};


#endif // CHARINFOEXT_H
