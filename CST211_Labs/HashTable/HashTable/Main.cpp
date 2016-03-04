/*****************************************************************************************
Author:			Garrett Fleischer
Filename:		Main.cpp
Date Created:	3/3/16
Modifications:

Lab/Assignment: Lab 7

Overview: Test of HashTable class

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
#include <string>
using std::string;

#include "HashTable.h"
#include "HashTableValueIterator.h"
#include "HashTableKeyIterator.h"

int AsciiHash(string key);

struct Book
{
	string m_title;
	string m_author;
	int m_pages;
};

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	HashTable<string, Book> table(&AsciiHash, 10);

	Book temp = { "C++: An Active Learning Approach", "Randal Albert", 635 };
	table.Insert("0763757233", temp);

	Book temp1 = { "Rodeo for Dummies", "Calvin Caldwell", 1 };
	table.Insert("7063757233", temp1);

	Book temp3 = { "And That n There", "Ralph Carestia", 1 };
	table.Insert("7063757234", temp3);

	table.Resize(100);

	cout << table["0763757233"].m_title << endl;
	cout << table["7063757233"].m_title << endl;
	cout << table["7063757234"].m_title << endl << endl;

	HashTableValueIterator<string, Book> valueIter(table);
	for (valueIter.Reset(); !valueIter.IsDone(); valueIter.MoveNext())
		cout << valueIter.GetCurrent().m_author << endl;

	cout << endl;

	HashTableKeyIterator<string, Book> keyIter(table);
	for (keyIter.Reset(); !keyIter.IsDone(); keyIter.MoveNext())
		cout << keyIter.GetCurrent() << endl;

	cout << endl;

	return 0;
}

int AsciiHash(string key)
{
	int hash = 0;
	for (int i = 0; i < key.length(); ++i)
		hash += key[i];

	return hash;
}