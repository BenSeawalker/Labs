#include "String.h"



/////////////////////////////////////////////////
// C'TOR / D'TOR
/////////
String::String()
	: m_nLength(0)
{
	cout << "No arg c'tor" << endl;
}

String::String(const char * _str)
	: m_nLength(0)
{
	cout << "1 arg c'tor" << endl;
	SetBuffer(_str);
}


String::~String()
{
	cout << "d'tor" << endl;
}



/////////////////////////////////////////////////
// PUBLIC
/////////
	
	// Return the lenth of this String
	UINT String::StrLen()
	{
		return m_nLength + 5; // 5 chars for " (##)"
	}

	// Return whether or not this string is empty
	bool String::IsEmpty()
	{
		return (m_nLength == 0);
	}


	// Display data to the screen
	void String::Display()
	{
		for (UINT i = 0; i < m_nLength; ++i)
			cout << m_sBuffer[i];

		cout << (IsEmpty() ? "" : " ") << "(" << m_nLength << ")";
	}

	// "Display" data inside custom stream
	void String::Display(stringstream & _s)
	{
		for (UINT i = 0; i < m_nLength; ++i)
			_s << m_sBuffer[i];

		_s << (IsEmpty() ? "" : " ") << "(" << m_nLength << ")";
	}



/////////////////////////////////////////////////
// PRIVATE
/////////
	
	// Update the character array with new data
	void String::SetBuffer(const char * _str)
	{
		UINT len = StrLen(_str);

		if (len <= BUFFER_LEN)
		{
			StrCopy(_str);
			m_nLength = len;
		}
		else
			throw "Too many characters";
	}


	// Calculate the length of a String
	UINT String::StrLen(const char * _str)
	{
		UINT len = 0;

		while (_str[len] != '\0')
			len++;

		return len;
	}


	// Copy the string
	void String::StrCopy(const char * _str)
	{
		UINT i = 0;
		while (_str[i] != '\0')
		{
			m_sBuffer[i] = _str[i];
			++i;
		}
	}


