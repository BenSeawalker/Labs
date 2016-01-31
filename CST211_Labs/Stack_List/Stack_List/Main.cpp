/*****************************************************************************************
Author:			Garrett Fleischer
Filename:		Main.cpp
Date Created:	1/29/16
Modifications: 

Lab/Assignment: A5

Overview: Test of LinkedList-based Stack ADT

Input: Input is hardcoded directly into Main.cpp and consists of debug testing statements

Output: The output for this program is to the console window and consists of debugging
text and data stored in the stack. The output will have the following form:

-----------------------------------------------------------------------

///////////////////////// SECTION HEADER /////////////////////////

*************** TEST HEADER ***************
Input:
	stk.Push(#)
Output:
	MaxSize: #
	Size: #
	Peek: ...

*****************************************************************************************/

#include "crtdbg_new.h"

#include <iostream>
using std::cout;
using std::endl;

#include "Stack.h"

void TestFillStack(Stack<int> & stk);
void TestCanonical(const Stack<int> & stk);
void TestEmptyStack(Stack<int> & stk);

void PrintStack(const Stack<int> & stk);

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	Stack<int> stk;

	TestFillStack(stk);
	TestCanonical(stk);
	TestEmptyStack(stk);

	cout << endl;
	system("pause");

	return 0;
}


void TestFillStack(Stack<int> & stk)
{
	cout << "\n\n\n--------------------------------------------------------------------------";
	cout << "\n\n\n///////////////////////// TEST FILL STACK /////////////////////////\n";

	cout << "\n*************** TEST PUSH() ***************\n";
	cout << "Input:\n\tloop 10 times:\tstk.Push(int(i))";
	for (int i = 0; i < 10; ++i)
		stk.Push(int(i));
	PrintStack(stk);

	cout << "\n*************** TEST PUSH() WITH DUPLICATE ITEM ***************\n";
	cout << "Input:\n\tstk.Push(int(5))";
	stk.Push(int(5));
	PrintStack(stk);
}

void TestCanonical(const Stack<int> & stk)
{
		cout << "\n\n\n--------------------------------------------------------------------------";
		cout << "\n\n\n///////////////////////// TEST CANONICAL METHODS /////////////////////////\n";

		cout << "\n*************** TEST DEFAULT CTOR ***************\n";
		cout << "Input:\n\tStack<int> stk1\n\tPrintStack(stk1)";
		Stack<int> stk1;
		PrintStack(stk1);
		
		cout << "\n*************** TEST COPY CTOR ***************\n";
		cout << "Input:\n\tStack<int> stk2(stk)\n\tPrintStack(stk)\n\tPrintStack(stk2)";
		Stack<int> stk2(stk);
		PrintStack(stk);
		PrintStack(stk2);

		cout << "\n*************** TEST OPERATOR = ***************\n";
		cout << "Input:\n\tstk1 = stk2\n\tPrintStack(stk2)\n\tPrintStack(stk1)";
		stk1 = stk2;
		PrintStack(stk2);
		PrintStack(stk1);
}

void TestEmptyStack(Stack<int> & stk)
{
	cout << "\n\n\n--------------------------------------------------------------------------";
	cout << "\n\n\n///////////////////////// TEST FILL STACK /////////////////////////\n";

	cout << "\n*************** TEST POP() ***************\n";
	cout << "Input:\n\twhile(!stk.isEmpty()):\n\t\tstk.Pop()";
	cout << "\nOutput:\n";
	while(!stk.isEmpty())
		cout << '\t' << stk.Pop() << endl;

	cout << "\n*************** TEST POP() ON EMPTY STACK ***************\n";
	cout << "Input:\n\tstk.Pop()";
	try
	{
		stk.Pop();
	}
	catch (const Exception & exc)
	{
		cout << "\nOutput:\n\t" << exc << '\n';
	}

	PrintStack(stk);
}

void PrintStack(const Stack<int> & stk)
{
	cout << "\nOutput:\n\tSize: " << stk.Size() << '\n'
		<< "\tPeek: ";

	try
	{
		cout << stk.Peek();
	}
	catch (const Exception & exc)
	{
		cout << exc << '\n';
	}

	cout << endl;
}