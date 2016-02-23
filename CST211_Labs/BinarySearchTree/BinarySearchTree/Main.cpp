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

#include "AVLTree.h"

#include "ForwardIterator.h"
#include "BackwardIterator.h"

#include "PreOrderIterator.h"
#include "InOrderIterator.h"
#include "PostOrderIterator.h"
#include "BreadthFirstIterator.h"

void TestIterators();
void TestTraversals();
void TestDelete();

void Display(int & num);
void Display(const int & num);


int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	
	TestIterators();
	TestTraversals();
	//TestDelete();

	system("pause");

	return 0;
}

void TestIterators()
{
	cout << "\n----------------Test List Iterators----------------\n" << endl;

	cout << "Inserting: 1, 2, 3, 4, 5, 6, 7, 8, 9\n" << endl;
	DoubleLinkedList<int> list;
	list.Append(1);
	list.Append(2);
	list.Append(3);
	list.Append(4);
	list.Append(5);
	list.Append(6);
	list.Append(7);
	list.Append(8);
	list.Append(9);


	cout << "Forward:    ";
	ForwardIterator<int> fi(&list);
	for (fi.Reset(); !fi.IsDone(); fi.MoveNext())
		Display(fi.GetCurrent());

	cout << endl << endl;

	cout << "Backward:   ";
	BackwardIterator<int> bi(&list);
	for (bi.Reset(); !bi.IsDone(); bi.MoveNext())
		Display(bi.GetCurrent());

	cout << endl << endl;
}

void TestTraversals()
{
	cout << "\n----------------Test Tree Iterators----------------\n" << endl;
	AVLTree<int> tree;

	cout << "Inserting: 8, 9, 10, 2, 1, 5, 3, 6, 4, 7, 11\n" << endl;
	tree.Insert(8);
	tree.Insert(9);
	tree.Insert(10);
	tree.Insert(2);
	tree.Insert(1);
	tree.Insert(5);
	tree.Insert(3);
	tree.Insert(6);
	tree.Insert(4);
	tree.Insert(7);
	tree.Insert(11);

	PreOrderIterator<int> pre(&tree);
	InOrderIterator<int> in(&tree);
	PostOrderIterator<int> post(&tree);
	BreadthFirstIterator<int> breadth(&tree);

	cout << "Height: " << tree.Height() << endl << endl;

	cout << "Pre:       ";
	tree.PreOrderTraversal(&Display);
	cout << endl << "Iter:      ";
	for (pre.Reset(); !pre.IsDone(); pre.MoveNext())
		Display(pre.GetCurrent());
	cout << endl << endl;

	cout << "In:        ";
	tree.InOrderTraversal(&Display);
	cout << endl << "Iter:      ";
	for (in.Reset(); !in.IsDone(); in.MoveNext())
		Display(in.GetCurrent());
	cout << endl << endl;

	cout << "Post:      ";
	tree.PostOrderTraversal(&Display);
	cout << endl << "Iter:      ";
	for (post.Reset(); !post.IsDone(); post.MoveNext())
		Display(post.GetCurrent());
	cout << endl << endl;

	cout << "Breadth:   ";
	tree.BreadthFirstTraversal(&Display);
	cout << endl << "Iter:      ";
	for (breadth.Reset(); !breadth.IsDone(); breadth.MoveNext())
		Display(breadth.GetCurrent());
	cout << endl << endl;

	/*cout << "\nUsing constant BinarySearchTree\n" << endl;
	const AVLTree<int> cp(tree);

	cout << "Height: " << cp.Height() << endl << endl;

	cout << "Pre:       ";
	cp.PreOrderTraversal(&Display);
	cout << endl << endl;

	cout << "In:        ";
	cp.InOrderTraversal(&Display);
	cout << endl << endl;

	cout << "Post:      ";
	cp.PostOrderTraversal(&Display);
	cout << endl << endl;

	cout << "Breadth:   ";
	cp.BreadthFirstTraversal(&Display);
	cout << endl << endl;

	cout << endl << endl << endl;*/
}

void TestDelete()
{
	cout << "----------------Test Delete----------------\n" << endl;
	AVLTree<int> tree;

	cout << "Inserting: 8, 9, 10, 2, 1, 5, 3, 6, 4, 7, 11\n" << endl;

	 	tree.Insert(8);
	 	tree.Insert(9);
	 	tree.Insert(10);
	 	tree.Insert(2);
	 	tree.Insert(1);
	 	tree.Insert(5);
	 	tree.Insert(3);
	 	tree.Insert(6);
	 	tree.Insert(4);
	 	tree.Insert(7);
	 	tree.Insert(11);

	const AVLTree<int> cp(tree);

	cp.BreadthFirstTraversal(&Display);

	cout << "\n\nHeight: " << tree.Height() << endl;

	cout << "\n\nData displayed breadth-first\n" << endl;


	cout << "\n\nDeleting: 10, 9, 11, 6, 7, 8\n" << endl;
	// EH
	// LR - EH
	// LL - LH
	tree.Delete(10);
	tree.Delete(9);
	tree.Delete(11);
	tree.Delete(6);
	tree.Delete(7);
	tree.Delete(8);
	
	tree.BreadthFirstTraversal(&Display);
	cout << "\n\nHeight: " << tree.Height() << endl;
	tree = cp;


	cout << "\n\nDeleting: 1, 10, 9, 11, 6, 7, 8\n" << endl;
	// EH
	// RH
	// LL - EH
	tree.Delete(1);
	tree.Delete(10);
	tree.Delete(9);
	tree.Delete(11);
	tree.Delete(6);
	tree.Delete(7);
	tree.Delete(8);

	tree.BreadthFirstTraversal(&Display);
	cout << "\n\nHeight: " << tree.Height() << endl;
	tree = cp;


	cout << "\n\nDeleting: 1, 4\n";
	cout << "Inserting: 5, 4\n";
	cout << "Deleting: 7, 9, 11, 6, 10, 8, 5\n" << endl;
	// EH
	// RH
	// LR - LH
	tree.Delete(1);
	tree.Delete(4);
	tree.Insert(5);
	tree.Insert(4);
	tree.Delete(7);
	tree.Delete(9);
	tree.Delete(11);
	tree.Delete(6);
	tree.Delete(10);
	tree.Delete(8);
	tree.Delete(5);

	tree.BreadthFirstTraversal(&Display);
	cout << "\n\nHeight: " << tree.Height() << endl;
	tree = cp;

	cout << "\n\nDeleting: 1, 9, 11, 10\n" << endl;
	// RH
	// EH
	// LR - EH
	tree.Delete(1);
	tree.Delete(9);
	tree.Delete(11);
	tree.Delete(10);

	tree.BreadthFirstTraversal(&Display);
	cout << "\n\nHeight: " << tree.Height() << endl;
	tree = cp;


	cout << "\n\nInserting: 5\n";
	cout << "Deleting: 1, 7, 9, 11, 6, 10, 8, 5\n" << endl;
	// RH
	// EH
	// LR - RH
	tree.Insert(5);
	tree.Delete(1);
	tree.Delete(7);
	tree.Delete(9);
	tree.Delete(11);
	tree.Delete(6);
	tree.Delete(10);
	tree.Delete(8);
	tree.Delete(5);

	tree.BreadthFirstTraversal(&Display);
	cout << "\n\nHeight: " << tree.Height() << endl;
	tree = cp;


	cout << "\n\nDeleting: 156\n" << endl;
	try
	{
		tree.Delete(156);
	}
	catch (const Exception & exc)
	{
		cout << exc << endl;
	}

	cout << endl << endl << endl;
}

void Display(int & num)
{
	cout << num << " ";
}

void Display(const int & num)
{
	cout << num << " ";
}