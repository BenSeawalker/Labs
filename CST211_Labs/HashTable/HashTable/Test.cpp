#include "Test.h"

Test::Test()
	: m_table(HashFunc, 10)
{
}

Test::~Test()
{
}

int Test::HashFunc(const string & key)
{
	int hash = 5381;
	for (size_t i = 0; i < key.length(); ++i)
		hash += ((hash << 5) + key[i]);

	return hash;
}