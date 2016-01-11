/************************************************************************
* Author:		Garrett Fleischer
* Filename:		Exception.cpp
* Date Created:	1/5/16
* Modifications:
*	N/A
*************************************************************************/
#include "Exception.h"

#include <cstring>


///////////////////////////////////////////////////////////////
//	C'TORS & D'TOR
//////

Exception::Exception()
	: m_message(nullptr)
{
	setMessage("*");
}

Exception::Exception(const char * msg)
	: m_message(nullptr)
{
	setMessage(msg);
}

Exception::Exception(const Exception & copy)
	: m_message(nullptr)
{
	*this = copy;
}

Exception::~Exception()
{
	delete[] m_message;
	m_message = nullptr;
}

//////
//	END C'TORS & D'TOR
///////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////
//	OPERATORS
//////

Exception & Exception::operator=(const Exception & rhs)
{
	if (this != &rhs)
		setMessage(rhs.m_message);

	return *this;
}

std::ostream & operator<<(std::ostream & stream, const Exception & excep)
{
	stream << excep.m_message;
	return stream;
}

//////
//	END OPERATORS
///////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////
//	GETTERS & SETTERS
//////

const char * Exception::getMessage() const
{
	return m_message;
}

void Exception::setMessage(const char * msg)
{
	delete[] m_message;
	m_message = new char[strlen(msg) + 1];
	strcpy(m_message, msg);
}

//////
//	END GETTERS & SETTERS
///////////////////////////////////////////////////////////////