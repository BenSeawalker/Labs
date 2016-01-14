#include "CharInfoExt.h"


CharInfoExt::CharInfoExt()
{
	m_info.Char.AsciiChar = '\0';
	m_info.Attributes = 7;
}


CharInfoExt::CharInfoExt(const CharInfoExt & copy)
{
	*this = copy;
}

CharInfoExt::~CharInfoExt()
{
}

CharInfoExt & CharInfoExt::operator=(const CharInfoExt & rhs)
{
	m_info = rhs.m_info;

	return *this;
}


char & CharInfoExt::Char()
{
	return m_info.Char.AsciiChar;
}

WORD & CharInfoExt::Attributes()
{
	return m_info.Attributes;
}

CHAR_INFO CharInfoExt::Info()
{
	return m_info;
}


CharInfoExt::operator CHAR_INFO()
{
	return CHAR_INFO(m_info);
}
