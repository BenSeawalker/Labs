#include <iostream>
using std::cout;
using std::endl;

#include <crtdbg.h> 
#define _CRTDBG_MAP_ALLOC

#include "doublelinkedlist.h"

void TestAppend(DoubleLinkedList<int> & alist);

//Note the const ref parameter.
void TestFirstAndLast(const DoubleLinkedList<int> & alist);
void TestPrepend(DoubleLinkedList<int> & alist);
void TestPurge(DoubleLinkedList<int> alist);
void TestInsertBefore();
void TestInsertAfter();
void TestExtract();

int main()
{
	// Please put in every lab and assignment this term for ease of testing for memory leaks
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	cout << "\n********** Testing: DoubleLinkedList default ctor  **********\n";
	DoubleLinkedList<int> alist;			//ctor
	cout << "\n********** Testing: DoubleLinkedList copy ctor with empty list **********\n";
	DoubleLinkedList<int> blist(alist);		//copy ctor
	DoubleLinkedList<int> clist;

	cout << "\n********** Testing: DoubleLinkedList op = **********\n";
	clist = blist;							//= operator

	// Note that these functions are only available for testing. 
	// Will be removed from the list before going into production.
	cout << "\n********** Testing: DoubleLinkedList getters  **********\n";
	std::cout << alist.getHead() << std::endl;
	std::cout << alist.getTail() << std::endl;

	//// Tests Methods
	TestAppend(alist);
	TestFirstAndLast(alist);
	TestPrepend(alist);

	std::cout << "\n********** Testing: DoubleLinkedList Copy ctor with Full List **********" << std::endl;
	TestPurge(alist);
	TestInsertBefore();
	TestInsertAfter();
	TestExtract();

	std::cout << "\n********** Testing: List Integrity **********" << std::endl;

	// Note these are also only for testing
	/*alist.PrintForwards();
	alist.PrintBackwards();*/

	// OK NOW MAKE SURE IT WORKS THE SAME FOR COMPLEX DATA TYPES
	// USE THE string CLASS

	// Please put in every lab and assignment this term for ease of testing for memory leaks
	system("pause");

	return 0;
}
void TestAppend(DoubleLinkedList<int> & alist)
{
	std::cout << "\n********** Testing: DoubleLinkedList Append **********" << std::endl;

	alist.Append(5);
	alist.Append(15);
	alist.Append(25);
	alist.Append(35);

	std::cout << alist.First() << std::endl;
	std::cout << alist.Last() << std::endl;
}
void TestFirstAndLast(const DoubleLinkedList<int> & alist)
{
	DoubleLinkedList<int> blist;

	std::cout << "\n********** Testing: DoubleLinkedList First and Last **********" << std::endl;

	std::cout << "\n********** Testing: First and Last with Full List **********" << std::endl;
	std::cout << alist.First() << std::endl;
	std::cout << alist.Last() << std::endl;

	std::cout << "\n********** Testing: First with Empty List **********" << std::endl;
	try
	{
		std::cout << blist.First() << std::endl;
	}
	catch (char * msg)
	{
		std::cout << msg << std::endl;
	}
	std::cout << "\n********** Testing: First with Empty List **********" << std::endl;
	try
	{
		std::cout << blist.Last() << std::endl;
	}
	catch (char * msg)
	{
		std::cout << msg << std::endl;
	}
}
void TestPrepend(DoubleLinkedList<int> & alist)
{
	DoubleLinkedList<int> blist;

	std::cout << "\n********** Testing: DoubleLinkedList Prepend **********" << std::endl;

	std::cout << "\n********** Testing: Prepend with Full List **********" << std::endl;
	alist.Prepend(4);
	alist.Prepend(3);
	alist.Prepend(2);
	alist.Prepend(1);
	alist.Prepend(0);

	std::cout << alist.First() << std::endl;
	std::cout << alist.Last() << std::endl;

	std::cout << "\n********** Testing: Prepend with Empty List **********" << std::endl;
	blist.Prepend(100);
	blist.Prepend(200);
	blist.Prepend(300);
	blist.Prepend(400);
	blist.Prepend(500);

	std::cout << blist.First() << std::endl;
	std::cout << blist.Last() << std::endl;
}
void TestPurge(DoubleLinkedList<int> alist)
{
	DoubleLinkedList<int> blist;

	std::cout << "\n********** Testing: DoubleLinkedList Purge with Full List **********" << std::endl;

	std::cout << "\n********** Testing: Before Purge Full List **********" << std::endl;
	std::cout << alist.getHead() << std::endl;
	std::cout << alist.getTail() << std::endl;

	alist.Purge();

	std::cout << "\n********** Testing: After Purge Full List **********" << std::endl;
	std::cout << alist.getHead() << std::endl;
	std::cout << alist.getTail() << std::endl;

	std::cout << "\n********** Testing: DoubleLinkedList Purge with Empty List **********" << std::endl;
	std::cout << "\n********** Testing: Before Purge Empty List **********" << std::endl;
	std::cout << alist.getHead() << std::endl;
	std::cout << alist.getTail() << std::endl;

	alist.Purge();

	std::cout << "\n********** Testing: After Purge Empty List **********" << std::endl;
	std::cout << alist.getHead() << std::endl;
	std::cout << alist.getTail() << std::endl;
}
void TestInsertBefore()
{
	DoubleLinkedList<int> clist;

	std::cout << "\n********** Testing: DoubleLinkedList InsertBefore **********" << std::endl;

	std::cout << "\n********** Testing: InsertBefore with Empty List **********" << std::endl;
	try
	{
		//Note: Here is the function signature so you can determine the order of parameters
		//void DoubleLinkedList<T>::InsertBefore(const T & new_data, const T & existing_data)
		clist.InsertBefore(-1, 0);
	}
	catch (char * msg)
	{
		std::cout << msg << std::endl;
	}
	std::cout << "\n********** Testing: InsertBefore head with only one node **********" << std::endl;
	clist.Append(0);
	clist.InsertBefore(-1, 0);

	std::cout << clist.First() << std::endl;
	std::cout << clist.Last() << std::endl;

	std::cout << "\n********** Testing: InsertBefore head with multiple nodes **********" << std::endl;
	clist.InsertBefore(-3, -1);

	std::cout << clist.First() << std::endl;
	std::cout << clist.Last() << std::endl;

	std::cout << "\n********** Testing: InsertBefore a node in the middle of the list **********" << std::endl;
	clist.InsertBefore(-2, -1);

	std::cout << clist.First() << std::endl;
	std::cout << clist.Last() << std::endl;

	std::cout << "\n********** Testing: InsertBefore but existing_data doesn't exist **********" << std::endl;
	try
	{
		clist.InsertBefore(-2, 99);
	}
	catch (char * msg)
	{
		std::cout << msg << std::endl;
	}
}
void TestInsertAfter()
{
	DoubleLinkedList<int> clist;

	std::cout << "\n********** Testing: DoubleLinkedList InsertAfter **********" << std::endl;

	std::cout << "\n********** Testing: InsertAfter with Empty List **********" << std::endl;
	try
	{
		//Note: Here is the function signature so you can determine the order of parameters
		//void DoubleLinkedList<T>::InsertAfter(const T & new_data, const T & existing_data)
		clist.InsertAfter(-1, 0);
	}
	catch (char * msg)
	{
		std::cout << msg << std::endl;
	}
	std::cout << "\n********** Testing: InsertAfter tail with only one node **********" << std::endl;
	clist.Append(0);
	clist.InsertAfter(1, 0);

	std::cout << clist.First() << std::endl;
	std::cout << clist.Last() << std::endl;

	std::cout << "\n********** Testing: InsertAfter tail with multiple nodes **********" << std::endl;
	clist.InsertAfter(3, 1);

	std::cout << clist.First() << std::endl;
	std::cout << clist.Last() << std::endl;

	std::cout << "\n********** Testing: InsertAfter a node in the middle of the list **********" << std::endl;
	clist.InsertAfter(2, 1);

	std::cout << clist.First() << std::endl;
	std::cout << clist.Last() << std::endl;

	std::cout << "\n********** Testing: InsertAfter but existing_data doesn't exist **********" << std::endl;
	try
	{
		clist.InsertAfter(-2, 99);
	}
	catch (char * msg)
	{
		std::cout << msg << std::endl;
	}
}
void TestExtract()
{
	DoubleLinkedList<int> alist;

	std::cout << "\n********** Testing: DoubleLinkedList Extract **********" << std::endl;

	std::cout << "\n********** Testing: Extract with empty list**********" << std::endl;
	try
	{
		//Note: The parameter is the DATA to be removed
		alist.Extract(0);
	}
	catch (char * msg)
	{
		std::cout << msg << std::endl;
	}
	std::cout << "\n********** Testing: Extract removing only node **********" << std::endl;
	alist.Append(0);
	alist.Extract(0);

	try
	{
		std::cout << alist.First() << std::endl;
	}
	catch (char * msg)
	{
		std::cout << msg << std::endl;
	}
	try
	{
		std::cout << alist.Last() << std::endl;
	}
	catch (char * msg)
	{
		std::cout << msg << std::endl;
	}

	std::cout << "\n********** Testing: Extract removing head **********" << std::endl;
	alist.Append(0);
	alist.Append(1);
	alist.Extract(0);

	std::cout << alist.First() << std::endl;
	std::cout << alist.Last() << std::endl;

	std::cout << "\n********** Testing: Extract removing tail **********" << std::endl;
	alist.Prepend(0);
	alist.Extract(1);

	std::cout << alist.First() << std::endl;
	std::cout << alist.Last() << std::endl;

	std::cout << "\n********** Testing: Extract removing non-existing node **********" << std::endl;
	alist.Append(0);
	alist.Append(1);

	try
	{
		alist.Extract(99);
	}
	catch (char * msg)
	{
		std::cout << msg << std::endl;
	}
}