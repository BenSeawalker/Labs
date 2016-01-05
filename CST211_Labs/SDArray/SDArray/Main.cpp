/************************************************************************
* Author:		Garrett Fleischer
* Filename:		Main.cpp
* Date Created:	1/4/16
* Modifications:
*	N/A
*************************************************************************/
#include <crtdbg.h> 
#define _CRTDBG_MAP_ALLOC

#include <iostream>
using std::cout;
using std::endl;

#include "Array.h"
#include "Exception.h"

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	try
	{
		Array<int> ira = Array<int>(10, 5);

		for (int i = ira.getStartIndex(); i < (ira.getStartIndex() + ira.getLength()); ++i)
			ira[i] = i;

		Array<int> ira2;
		ira2 = ira;

		ira.setLength(5);
		ira.setStartIndex(8);
	
		for (int i = ira.getStartIndex(); i < (ira.getStartIndex() + ira.getLength()); ++i)
			cout << ((ira[i]))++ << endl;

		cout << endl;

		for (int i = ira2.getStartIndex(); i < (ira2.getStartIndex() + ira2.getLength()); ++i)
			cout << (ira2[i]) << endl;
	}
	catch (const Exception & e)
	{
		cout << '\n' << e.getMessage() << '\n' << endl;
	}

	

	return 0;
}