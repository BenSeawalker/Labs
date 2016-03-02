/*****************************************************************************************
Author:			Garrett Fleischer
Filename:		Main.cpp
Date Created:	2/27/16
Modifications:

Lab/Assignment: A11

Overview: Test of Graph class

Input: Input is hardcoded directly into Main.cpp and consists of debug testing statements

Output: The output for this program is to the console window and consists of debugging
text and data stored in the Graph. The output will have the following form:

-------------------------- Test <function> --------------------------

Inserting: *, ...
Deleting: *, ...

<test type>: <test result>

*****************************************************************************************/

#include "crtdbg_new.h"

#include <iostream>
using std::cout;
using std::endl;

#include "Graph.h"

void TestCanonical();
void TestInsert();
void TestDelete();

void Display(char & data);


int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	TestCanonical();
	TestInsert();
	TestDelete();

	return 0;
}

void TestCanonical()
{
	cout << "\n-------------------------- Test Canonical --------------------------\n";

	cout << "\n============ DEFAULT CTOR ============\n" << endl;
	Graph<char, char, int> graph;

	cout << "\nInserting: A X G H P E M Y J" << endl;
	graph.InsertVertex('A', 'A');
	graph.InsertVertex('X', 'X');
	graph.InsertVertex('G', 'G');
	graph.InsertVertex('H', 'H');
	graph.InsertVertex('P', 'P');
	graph.InsertVertex('E', 'E');
	graph.InsertVertex('M', 'M');
	graph.InsertVertex('Y', 'Y');
	graph.InsertVertex('J', 'J');

	cout << "\nConnecting: A->X, X->G, X->H, G->P, H->E, P->H, E->M, E->Y, M->J\n" << endl;
	graph.InsertArc('A', 'X', 'a', 0);
	graph.InsertArc('X', 'G', 'x', 0);
	graph.InsertArc('X', 'H', 'x', 0);
	graph.InsertArc('G', 'P', 'g', 0);
	graph.InsertArc('H', 'E', 'h', 0);
	graph.InsertArc('P', 'H', 'p', 0);
	graph.InsertArc('E', 'M', 'e', 0);
	graph.InsertArc('E', 'Y', 'e', 0);
	graph.InsertArc('M', 'J', 'm', 0);

	graph.BreadthFirst(&Display);
	cout << endl << endl;

	// COPY CTOR
	cout << "\n============ COPY CTOR ============\n" << endl;
	Graph<char, char, int> copy(graph);

	cout << "\nOriginal: ";
	graph.BreadthFirst(&Display);
	cout << endl;
	cout << "\nCopy:     ";
	copy.BreadthFirst(&Display);
	cout << endl << endl;

	cout << "\nDeleting 'H' from copy:" << endl;
	copy.DeleteVertex('H');
	
	cout << "\nOriginal: ";
	graph.BreadthFirst(&Display);
	cout << endl;
	cout << "\nCopy:     ";
	copy.BreadthFirst(&Display);
	cout << endl << endl;
	
	
	// OPERATOR =
	cout << "\n============ OPERATOR EQ ============\n" << endl;
	copy = graph;

	cout << "\nOriginal: ";
	graph.BreadthFirst(&Display);
	cout << endl;
	cout << "\nCopy:     ";
	copy.BreadthFirst(&Display);
	cout << endl << endl;

	cout << "\nDeleting 'H' from copy:" << endl;
	copy.DeleteVertex('H');

	cout << "\nOriginal: ";
	graph.BreadthFirst(&Display);
	cout << endl;
	cout << "\nCopy:     ";
	copy.BreadthFirst(&Display);
	cout << endl << endl;

	cout << endl << endl << endl;
}

void TestInsert()
{
	cout << "\n-------------------------- Test Insert --------------------------\n";
	Graph<char, char, int> graph;

	cout << "\nInserting: A X G H P E M Y J" << endl;
	graph.InsertVertex('A', 'A');
	graph.InsertVertex('X', 'X');
	graph.InsertVertex('G', 'G');
	graph.InsertVertex('H', 'H');
	graph.InsertVertex('P', 'P');
	graph.InsertVertex('E', 'E');
	graph.InsertVertex('M', 'M');
	graph.InsertVertex('Y', 'Y');
	graph.InsertVertex('J', 'J');

	cout << "\nConnecting: A->X, X->G, X->H, G->P, H->E, P->H, E->M, E->Y, M->J\n" << endl;
	graph.InsertArc('A', 'X', 'a', 0);
	graph.InsertArc('X', 'G', 'x', 0);
	graph.InsertArc('X', 'H', 'x', 0);
	graph.InsertArc('G', 'P', 'g', 0);
	graph.InsertArc('H', 'E', 'h', 0);
	graph.InsertArc('P', 'H', 'p', 0);
	graph.InsertArc('E', 'M', 'e', 0);
	graph.InsertArc('E', 'Y', 'e', 0);
	graph.InsertArc('M', 'J', 'm', 0);

	cout << "\nBreadth First: " << endl;
	graph.BreadthFirst(&Display);
	cout << "\nDepth First:   " << endl;
	graph.DepthFirst(&Display);
	cout << endl << endl;

	cout << endl << endl << endl;
}

void TestDelete()
{
	cout << "\n-------------------------- Test Delete --------------------------\n";
	Graph<char, char, int> graph;
	

	cout << "\nInserting: A X G H P E M Y J" << endl;
	graph.InsertVertex('A', 'A');
	graph.InsertVertex('X', 'X');
	graph.InsertVertex('G', 'G');
	graph.InsertVertex('H', 'H');
	graph.InsertVertex('P', 'P');
	graph.InsertVertex('E', 'E');
	graph.InsertVertex('M', 'M');
	graph.InsertVertex('Y', 'Y');
	graph.InsertVertex('J', 'J');

	cout << "\nConnecting: A->X, X->G, X->H, G->P, H->E, P->H, E->M, E->Y, M->J\n" << endl;
	graph.InsertArc('A', 'X', 'a', 0);
	graph.InsertArc('X', 'G', 'x', 0);
	graph.InsertArc('X', 'H', 'x', 0);
	graph.InsertArc('G', 'P', 'g', 0);
	graph.InsertArc('H', 'E', 'h', 0);
	graph.InsertArc('P', 'H', 'p', 0);
	graph.InsertArc('E', 'M', 'e', 0);
	graph.InsertArc('E', 'Y', 'e', 0);
	graph.InsertArc('M', 'J', 'm', 0);


	cout << "\n============ DELETE ARC ============\n" << endl;
	cout << "\nDeleting H->X: ";
	cout << (graph.DeleteArc('H', 'X', 'x') ? "success!" : "failure!") << endl;
	cout << "\nDeleting X->H: ";
	cout << (graph.DeleteArc('X', 'H', 'x') ? "success!" : "failure!") << endl << endl;
	graph.BreadthFirst(&Display);
	cout << endl << endl;


	cout << "\n============ DELETE HEAD ============\n" << endl;
	cout << "\nDeleting 'A': " << endl;
	graph.DeleteVertex('A');
	graph.BreadthFirst(&Display);
	cout << endl << endl;

	cout << "\n============ DELETE TAIL ============\n" << endl;
	cout << "\nDeleting 'J': " << endl;
	graph.DeleteVertex('J');
	graph.BreadthFirst(&Display);
	cout << endl << endl;


	cout << "\n============ DELETE MIDDLE ============\n" << endl;
	cout << "\nDeleting 'P': " << endl;
	graph.DeleteVertex('P');
	graph.BreadthFirst(&Display);
	cout << endl << endl;


	cout << "\n============ PURGE() ============\n" << endl;
	cout << "\nEmpty before?: " << (graph.IsEmpty() ? "true" : "false") << endl;
	graph.Purge();
	cout << "\nEmpty after?:  " << (graph.IsEmpty() ? "true" : "false") << endl;
	cout << endl << endl;

	cout << endl << endl << endl;
}

void Display(char & data)
{
	cout << data << " ";
}