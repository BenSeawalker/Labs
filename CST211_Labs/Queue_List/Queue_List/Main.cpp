/*****************************************************************************************
Author:			Garrett Fleischer
Filename:		Main.cpp
Date Created:	1/29/16
Modifications: 

Lab/Assignment: A5

Overview: Test of LinkedList-based Queue ADT

Input: Input is hardcoded directly into Main.cpp and consists of debug testing statements

Output: The output for this program is to the console window and consists of debugging
text and data stored in the queue. The output will have the following form:

-----------------------------------------------------------------------

///////////////////////// SECTION HEADER /////////////////////////

*************** TEST HEADER ***************
Input:
	q.Enqueue(#)
Output:
	Size: #
	Front: ...

*****************************************************************************************/

#include "crtdbg_new.h"

#include <iostream>
using std::cout;
using std::endl;

#include "Queue.h"

void TestFillQueue(Queue<int> & q);
void TestCanonical(const Queue<int> & q);
void TestEmptyQueue(Queue<int> & q);

void PrintQueue(const Queue<int> & q);

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	Queue<int> q;

	TestFillQueue(q);
	TestCanonical(q);
	TestEmptyQueue(q);

	cout << endl;
	system("pause");

	return 0;
}


void TestFillQueue(Queue<int> & q)
{
	cout << "\n\n\n--------------------------------------------------------------------------";
	cout << "\n\n\n///////////////////////// TEST FILL QUEUE /////////////////////////\n";

	cout << "\n*************** TEST ENQUEUE() ***************\n";
	cout << "Input:\n\tloop 10 times:\tq.Enqueue(int(i))";
	for (int i = 0; i < 10; ++i)
		q.Enqueue(int(i));
	PrintQueue(q);

	cout << "\n*************** TEST ENQUEUE() WITH DUPLICATE ITEM ***************\n";
	cout << "Input:\n\tq.Enqueue(int(5))";
	q.Enqueue(int(5));
	PrintQueue(q);
}

void TestCanonical(const Queue<int> & q)
{
		cout << "\n\n\n--------------------------------------------------------------------------";
		cout << "\n\n\n///////////////////////// TEST CANONICAL METHODS /////////////////////////\n";

		cout << "\n*************** TEST DEFAULT CTOR ***************\n";
		cout << "Input:\n\tQueue<int> q1\n\tPrintQueue(q1)";
		Queue<int> q1;
		PrintQueue(q1);
		
		cout << "\n*************** TEST COPY CTOR ***************\n";
		cout << "Input:\n\tQueue<int> q2(q)\n\tPrintQueue(q)\n\tPrintQueue(q2)";
		Queue<int> q2(q);
		PrintQueue(q);
		PrintQueue(q2);

		cout << "\n*************** TEST OPERATOR = ***************\n";
		cout << "Input:\n\tq1 = q2\n\tPrintQueue(q2)\n\tPrintQueue(q1)";
		q1 = q2;
		PrintQueue(q2);
		PrintQueue(q1);
}

void TestEmptyQueue(Queue<int> & q)
{
	cout << "\n\n\n--------------------------------------------------------------------------";
	cout << "\n\n\n///////////////////////// TEST FILL QUEUE /////////////////////////\n";

	cout << "\n*************** TEST DEQUEUE() ***************\n";
	cout << "Input:\n\twhile(!q.isEmpty()):\n\t\tq.DeQueue()";
	cout << "\nOutput:\n";
	while(!q.isEmpty())
		cout << '\t' << q.Dequeue() << endl;

	cout << "\n*************** TEST DEQUEUE() ON EMPTY QUEUE ***************\n";
	cout << "Input:\n\tq.DeQueue()";
	try
	{
		q.Dequeue();
	}
	catch (const Exception & exc)
	{
		cout << "\nOutput:\n\t" << exc << '\n';
	}

	PrintQueue(q);
}

void PrintQueue(const Queue<int> & q)
{
	cout << "\nOutput:\n\tSize: " << q.Size() << '\n'
		<< "\tFront: ";

	try
	{
		cout << q.Front();
	}
	catch (const Exception & exc)
	{
		cout << exc << '\n';
	}

	cout << endl;
}