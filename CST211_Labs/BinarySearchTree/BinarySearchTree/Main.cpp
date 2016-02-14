#include "crtdbg_new.h"

#include <iostream>
using std::cout;
using std::endl;

#include "BSTree.h"

void TestTraversals();
void TestDelete();

void Display(int & num);


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
	BSTree<int> bst;

	cout << "Inserting: 20, 12, 25, 11, 18, 22, 26\n";

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

	cout << endl << endl << endl;
}

void TestDelete()
{
	BSTree<int> bst;
	BSTree<int> cp;

	cout << "Inserting: 20, 15, 25, 12, 18, 30, 11, 13\n";

	bst.Insert(20);
	bst.Insert(15);
	bst.Insert(25);
	bst.Insert(12);
	bst.Insert(18);
	bst.Insert(30);
	bst.Insert(11);
	bst.Insert(13);
	cp = bst;

	cout << "\nHeight: " << bst.Height() << endl << endl;

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

	cout << endl << endl << endl;
}

void Display(int & num)
{
	cout << num << " ";
}
