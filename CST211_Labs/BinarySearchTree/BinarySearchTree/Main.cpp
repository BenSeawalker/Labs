/*****************************************************************************************
Author:			Garrett Fleischer
Filename:		Main.cpp
Date Created:	2/15/16
Modifications:

Lab/Assignment: L4

Overview: Test of (AVL) Balanced Binary Search Tree ADT

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

void TestTraversals();
void TestDelete();

void Display(int & num);
void Display(const int & num);


int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	TestTraversals();
	TestDelete();

	system("pause");

	return 0;
}

void TestTraversals()
{
	cout << "\n----------------Test Traversals----------------\n" << endl;
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

	cout << "Height: " << tree.Height() << endl << endl;

	cout << "Pre:       ";
	tree.PreOrderTraversal(&Display);
	cout << endl << endl;

	cout << "In:        ";
	tree.InOrderTraversal(&Display);
	cout << endl << endl;

	cout << "Post:      ";
	tree.PostOrderTraversal(&Display);
	cout << endl << endl;

	cout << "Breadth:   ";
	tree.BreadthFirstTraversal(&Display);
	cout << endl << endl;

	cout << "\nUsing constant BinarySearchTree\n" << endl;
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

	cout << endl << endl << endl;
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