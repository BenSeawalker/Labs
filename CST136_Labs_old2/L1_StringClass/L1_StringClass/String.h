#ifndef STRING_H
#define STRING_H

#include <iostream>
using std::cout;
using std::endl;

#include <sstream>
using std::stringstream;

typedef unsigned int UINT;

class String
{
public:
	static const UINT BUFFER_LEN = 75;

	String();
	String(const char *);
	
	~String();


	UINT StrLen();
	void Display();
	void Display(stringstream &_s);
	bool IsEmpty();

	void SetBuffer(const char *);

private:
	char m_sBuffer[BUFFER_LEN];
	UINT m_nLength;

	UINT StrLen(const char *);
	void StrCopy(const char *);
};

#endif