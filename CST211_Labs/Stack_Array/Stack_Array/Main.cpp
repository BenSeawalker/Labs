/*****************************************************************************************
Author:			Garrett Fleischer
Filename:		Main.cpp
Date Created:	1/29/16
Modifications: 

Lab/Assignment: A5

Overview: Test of Array-based Stack ADT

Input: Input is hardcoded directly into Main.cpp and consists of debug testing statements

Output: The output for this program is to the console window and consists of debugging
text and data stored in the array. The output will have the following form:

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

#define TYPE int

void TestFillStack(Stack<TYPE> & stk);
void TestCanonical(const Stack<TYPE> & stk);
void TestEmptyStack(Stack<TYPE> & stk);

void PrintStack(const Stack<TYPE> & stk);

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	Stack<TYPE> stk(10);

	TestFillStack(stk);
	TestCanonical(stk);
	TestEmptyStack(stk);

	cout << endl;
	system("pause");

	return 0;
}


void TestFillStack(Stack<TYPE> & stk)
{
	cout << "\n\n\n--------------------------------------------------------------------------";
	cout << "\n\n\n///////////////////////// TEST FILL STACK /////////////////////////\n";

	cout << "\n*************** TEST PUSH() ***************\n";
	cout << "Input:\n\tloop stk.MaxSize() times:\n\tstk.Push(TYPE(i))";
	for (int i = 0; i < stk.MaxSize(); ++i)
		stk.Push(TYPE(i));
	PrintStack(stk);

	cout << "\n*************** TEST PUSH() ON FULL LIST ***************\n";
	cout << "Input:\n\tstk.Push(TYPE(23))";
	try
	{
		stk.Push(TYPE(23));
	}
	catch (const Exception & exc)
	{
		cout << "\nOutput:\n\t" << exc << '\n';
	}
}

void TestCanonical(const Stack<TYPE> & stk)
{
		cout << "\n\n\n--------------------------------------------------------------------------";
		cout << "\n\n\n///////////////////////// TEST CANONICAL METHODS /////////////////////////\n";

		cout << "\n*************** TEST DEFAULT CTOR ***************\n";
		cout << "Input:\n\tStack<TYPE> stk1\n\tPrintStack(stk1)";
		Stack<TYPE> stk1;
		PrintStack(stk1);
		
		cout << "\n*************** TEST COPY CTOR ***************\n";
		cout << "Input:\n\tStack<TYPE> stk2(stk)\n\tPrintStack(stk)\n\tPrintStack(stk2)";
		Stack<TYPE> stk2(stk);
		PrintStack(stk);
		PrintStack(stk2);

		cout << "\n*************** TEST OPERATOR = ***************\n";
		cout << "Input:\n\tstk1 = stk2\n\tPrintStack(stk2)\n\tPrintStack(stk1)";
		stk1 = stk2;
		PrintStack(stk2);
		PrintStack(stk1);
}

void TestEmptyStack(Stack<TYPE> & stk)
{
	cout << "\n\n\n--------------------------------------------------------------------------";
	cout << "\n\n\n///////////////////////// TEST FILL STACK /////////////////////////\n";

	cout << "\n*************** TEST POP() ***************\n";
	cout << "Input:\n\twhile(!stk.isEmpty()):\n\t\tstk.Pop()";
	cout << "\nOutput:\n";
	while(!stk.isEmpty())
		cout << '\t' << stk.Pop() << endl;

	cout << "\n*************** TEST POP() ON EMPTY LIST ***************\n";
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

void PrintStack(const Stack<TYPE> & stk)
{
	cout << "\nOutput:\n\tMaxSize: " << stk.MaxSize() << '\n'
		<< "\tSize: " << stk.Size() << '\n'
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