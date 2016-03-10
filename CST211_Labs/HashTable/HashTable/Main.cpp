/*****************************************************************************************
Author:			Garrett Fleischer
Filename:		Main.cpp
Date Created:	3/5/16
Modifications:

Lab/Assignment: Lab 6

Overview: Test of HashTable class

Input: Input is hardcoded directly into Main.cpp and consists of debug testing statements

Output: The output for this program is to the console window and consists of debugging
text and data stored in the table. The output will have the following form:

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

struct Book
{
	string m_title;
	string m_author;
	int m_pages;

	bool operator==(const Book & rhs) const
	{
		return (m_title == rhs.m_title &&
				m_author == rhs.m_author &&
				m_pages == rhs.m_pages);
	}
};


void TestCanonical(const HashTable<string, Book> & table);
void TestHash(HashTable<string, Book> & table);
void TestIterators(HashTable<string, Book> & table);

int AsciiHash(const string & key);
int BetterAsciiHash(const string & key);

void Display(Book & book);
void CDisplay(const Book & book);



int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	cout << "\n-------------------------- TEST INSERT --------------------------\n";
	cout << "\n========================== HashTable(10, &AsciiHash) ==========================\n";
	HashTable<string, Book> table(10, &AsciiHash);

	Book temp = { "C++: An Active Learning Approach", "Randal Albert", 635 };
	table.Insert("0763757233", temp);

	Book temp1 = { "Rodeo for Dummies", "Calvin Caldwell", 1 };
	table.Insert("7063757233", temp1);

	Book temp3 = { "And That n There", "Ralph Carestia", 1 };
	table.Insert("7063757234", temp3);

	TestCanonical(table);
	TestHash(table);
	TestIterators(table);

	cout << endl << endl << endl;

	system("pause");

	return 0;
}




void TestCanonical(const HashTable<string, Book> & table)
{
	cout << "\n-------------------------- TEST CANONICAL --------------------------\n";
	cout << "\n\n========================== Copy ctor ==========================\n";
	HashTable<string, Book> cp(table);
	cout << "Original: ";
	table.Traverse(&CDisplay);
	cout << "\nCopy:     ";
	cp.Traverse(&Display);

	cout << "\n\n========================== operator=() ==========================\n";
	HashTable<string, Book> opeq;
	opeq = table;
	cout << "Original: ";
	table.Traverse(&CDisplay);
	cout << "\nCopy:     ";
	opeq.Traverse(&Display);

	cout << "\n\n========================== Modify copies ==========================\n";
	cout << "cp.Insert(9788460767923, Moby Dick)\n";
	cp.Insert("9788460767923", { "Moby Dick", "Herman Melville", 927 });
	cout << "opeq.Delete(7063757234)\n";
	opeq.Delete("7063757234");
	cout << "\nOriginal: ";
	table.Traverse(&CDisplay);
	cout << "\nCopies:   ";
	cp.Traverse(&Display);
	cout << "\n          ";
	opeq.Traverse(&Display);

	cout << "\n\n========================== operator[] ==========================\n";
	cout << "\nconst table[7063757233]: " << table["7063757233"].m_title;
	cout << "\n\ncp[9788460767923]: " << cp["9788460767923"].m_title;
}

void TestHash(HashTable<string, Book>& table)
{
	cout << "\n\n\n-------------------------- TEST HASH MODIFIERS --------------------------\n";

	cout << "\n\n========================== Resize(100) ==========================\n";
	table.Resize(100);
	table.Traverse(&Display);
	cout << "\n\n========================== Resize(2) ==========================\n";
	table.Resize(2);
	table.Traverse(&Display);

	cout << "\n\n========================== Resize(10) ==========================\n";
	table.Resize(10);
	table.Traverse(&Display);

	cout << "\n\n========================== SetHash(&BetterAsciiHash) ==========================\n";
	table.SetHash(&BetterAsciiHash);
	table.Traverse(&Display);

	cout << "\n\n\n========================== Test InternalHash() ==========================\n";
	cout << "HashTable<int, string>(9)\n";
	HashTable<int, string> itable(9);
	cout << "Insert(12345, Hello)\nInsert(54321, World)\nInsert(67890, Goodbye)\nInsert(1054673, Earth)\n\n";
	itable.Insert(12345, "Hello");
	itable.Insert(54321, "World");
	itable.Insert(67890, "Goodbye");
	itable.Insert(1054673, "Earth");
	HashTableValueIterator<int, string> value(itable);
	for (value.Reset(); !value.IsDone(); value.MoveNext())
		cout << value.GetCurrent() << ", ";
}

void TestIterators(HashTable<string, Book>& table)
{
	cout << "\n\n\n-------------------------- TEST ITERATORS --------------------------\n";

	cout << "\n\n========================== PAIR ==========================\n";
	HashTablePairIterator<string, Book> pair_iter(table);
	for (pair_iter.Reset(); !pair_iter.IsDone(); pair_iter.MoveNext())
		cout << pair_iter.GetCurrent().first << " : " << pair_iter.GetCurrent().second.m_author << ", ";

	cout << "\n\n========================== KEY ==========================\n";
	HashTableKeyIterator<string, Book> key(table);
	for (key.Reset(); !key.IsDone(); key.MoveNext())
		cout << key.GetCurrent() << ", ";

	cout << "\n\n========================== VALUE ==========================\n";
	HashTableValueIterator<string, Book> value(table);
	for (value.Reset(); !value.IsDone(); value.MoveNext())
		cout << value.GetCurrent().m_title << ", ";
}

int AsciiHash(const string & key)
{
	int hash = 0;
	for (size_t i = 0; i < key.length(); ++i)
		hash += (key[i] * (i + 1));

	return hash;
}

int BetterAsciiHash(const string & key)
{
	int hash = 5381;
	for (size_t i = 0; i < key.length(); ++i)
		hash += ((hash << 5) ^ key[i] ^ (i + 1));

	return hash;
}

void Display(Book & book)
{
	cout << book.m_author << ", ";
}

void CDisplay(const Book & book)
{
	cout << book.m_author << ", ";
}