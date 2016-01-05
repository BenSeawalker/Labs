#ifndef STRINGCONTROLLER_H
#define STRINGCONTROLLER_H

#include <sstream>
using std::stringstream;

#include <fstream>
using std::ofstream;

#include <iostream>
using std::cout;
using std::cin;
using std::endl;


#include "String.h"


class StringController
{
public:
	static const UINT NUM_NAMES = 15;

	StringController();
	~StringController();

	void GetNames();
	void Display();

	UINT NamesPerLine();
	void NamesPerLine(int);

private:
	String m_names[NUM_NAMES];
	UINT m_numNames,
		 m_namesPerLine;
	

	void CheckWidth(bool _tooWide = false);
	void CleanInput();
};

#endif