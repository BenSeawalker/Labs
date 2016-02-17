/*****************************************************************************************
Author:			Garrett Fleischer
Filename:		Main.cpp
Date Created:	2/12/16
Modifications:

Lab/Assignment: A10

Overview: Test of Binary Search Tree ADT

Input: Input is hardcoded directly into Main.cpp and consists of debug testing statements

Output: The output for this program is to the console window and consists of debugging
text and data stored in the tree. The output will have the following form:

Inserting: #, ...

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

	AVLTree<int> tree;

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
	//tree.Insert(12);

	/*tree.Insert(70);
	tree.Insert(60);
	tree.Insert(80);
	tree.Insert(75);
	tree.Insert(90);
	tree.Insert(85);
	tree.Insert(95);
	tree.Insert(100);
	tree.Insert(99);
	tree.Insert(98);*/

	tree.PreOrderTraversal(&Display);
	/*TestTraversals();
	TestDelete();*/

	system("pause");

	return 0;
}

void TestTraversals()
{
	BinarySearchTree<int> bst;

	cout << "Inserting: 20, 12, 25, 11, 18, 22, 26\n" << endl;

	bst.Insert(20);
	bst.Insert(12);
	bst.Insert(25);
	bst.Insert(11);
	bst.Insert(18);
	bst.Insert(22);
	bst.Insert(26);

	cout << "Height: " << bst.Height() << endl << endl;

	cout << "Pre:       ";
	bst.PreOrderTraversal(&Display);
	cout << endl << endl;

	cout << "In:        ";
	bst.InOrderTraversal(&Display);
	cout << endl << endl;

	cout << "Post:      ";
	bst.PostOrderTraversal(&Display);
	cout << endl << endl;

	cout << "Breadth:   ";
	bst.BreadthFirstTraversal(&Display);
	cout << endl << endl;

	cout << "\nUsing constant BinarySearchTree\n" << endl;
	const BinarySearchTree<int> cp(bst);

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
	BinarySearchTree<int> bst;

	cout << "Inserting: 20, 15, 25, 12, 18, 30, 11, 13\n";

	bst.Insert(20);
	bst.Insert(15);
	bst.Insert(25);
	bst.Insert(12);
	bst.Insert(18);
	bst.Insert(30);
	bst.Insert(11);
	bst.Insert(13);

	const BinarySearchTree<int> cp(bst);

	cout << "\nHeight: " << bst.Height() << endl << endl;

	cout << "\nData displayed breadth-first\n" << endl;

	cout << "\nCase 1 (11): ";
	bst.Delete(11);
	bst.BreadthFirstTraversal(&Display);
	bst = cp;

	cout << "\nCase 2 (25): ";
	bst.Delete(25);
	bst.BreadthFirstTraversal(&Display);
	bst = cp;

	cout << "\nCase 3 (12): ";
	bst.Delete(12);
	bst.BreadthFirstTraversal(&Display);
	bst = cp;

	cout << "\nCase 4 (15): ";
	bst.Delete(15);
	bst.BreadthFirstTraversal(&Display);

	cout << "\n\n\nHeight: " << bst.Height() << endl << endl;

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