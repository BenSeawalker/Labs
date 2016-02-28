/*****************************************************************************************
Author:			Garrett Fleischer
Filename:		Main.cpp
Date Created:	2/15/16
Modifications:

Lab/Assignment: L4

Overview: Test of List and Tree Iterators

Input: Input is hardcoded directly into Main.cpp and consists of debug testing statements

Output: The output for this program is to the console window and consists of debugging
text and data stored in the tree. The output will have the following form:

----------------Test <function>----------------

Inserting: #, ...
Deleting: #, ...

Height: #

<test type>: <test result>

*****************************************************************************************/

#include "crtdbg_new.h"

#include <iostream>
using std::cout;
using std::endl;

#include "Graph.h"

void Display(char & data)
{
	cout << data << " ";
}

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	Graph<char, int> g;

	g.InsertVertex('A');
	g.InsertVertex('X');
	g.InsertVertex('G');
	g.InsertVertex('H');
	g.InsertVertex('P');
	g.InsertVertex('E');
	g.InsertVertex('M');
	g.InsertVertex('Y');
	g.InsertVertex('J');

	g.InsertArc('A', 'X', 0);
	g.InsertArc('X', 'G', 0);
	g.InsertArc('X', 'H', 0);
	g.InsertArc('G', 'P', 0);
	g.InsertArc('H', 'E', 0);
	g.InsertArc('P', 'H', 0);
	g.InsertArc('E', 'M', 0);
	g.InsertArc('E', 'Y', 0);
	g.InsertArc('M', 'J', 0);

	//g.DeleteVertex('H');
	//g.DeleteArc('X', 'H', 0);
	//g.DeleteArc('E', 'H', 0);

	g.BreadthFirst(&Display);
	cout << endl << endl;

	return 0;
}