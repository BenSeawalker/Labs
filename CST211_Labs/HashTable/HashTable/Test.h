#pragma once

#include <string>
using std::string;
#include "HashTable.h"

class Test
{
public:
	Test();
	~Test();

	static int HashFunc(const string & key);

private:
	HashTable<string, int> m_table;
};



