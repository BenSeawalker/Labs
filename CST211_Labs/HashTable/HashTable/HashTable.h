#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <vector>
#include <list>
#include <utility>
#include "Exception.h"
using std::vector;
using std::list;
using std::pair;

template<typename K, typename V> class HashTablePairIterator;

template<typename K, typename V>
class HashTable
{
	friend class HashTablePairIterator<K, V>;

public:
	// TYPEDEFS
	typedef int(*hash_t)(K key);
	typedef list<pair<K, V>> list_t;
	typedef vector<list_t> table_t;

	// CTORS & DTOR
	HashTable(hash_t hash = nullptr, int size = 0);
	HashTable(const HashTable & copy);

	~HashTable();

	// OPERATORS
	HashTable & operator=(const HashTable & rhs);
	V & operator[](const K & key);
	const V & operator[](const K & key) const;

	// METHODS
	void Insert(K key, V value);

	void SetHash(hash_t hash);

	void Resize(int size);

private:
	// METHODS
	void Rehash(table_t & copy);

	// MEMBERS
	table_t m_table;
	hash_t Hash;
};


///////////////////////////////////////////////////////////////
//	CTORS & DTOR
//////

template<typename K, typename V>
HashTable<K, V>::HashTable(hash_t hash, int size)
	: Hash(hash), m_table(size)
{}

template<typename K, typename V>
HashTable<K, V>::HashTable(const HashTable & copy)
	: m_table(copy.m_table), Hash(copy.Hash)
{}

template<typename K, typename V>
HashTable<K, V>::~HashTable()
{}

//////
//	END CTORS & DTOR
///////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////
//	OPERATORS
//////

template<typename K, typename V>
HashTable<K, V> & HashTable<K, V>::operator=(const HashTable<K, V> & rhs)
{
	if (this != &rhs)
	{
		m_table = rhs.m_table;
		Hash = rhs.Hash;
	}

	return *this;
}

template<typename K, typename V>
V & HashTable<K, V>::operator[](const K & key)
{
	if (m_table.size() == 0)
		throw Exception("Error! Cannot access element in table of size zero!");

	V * found = nullptr;
	int i = (Hash(key) % m_table.size());

	list_t::iterator iter;
	for (iter = m_table[i].begin(); !found && iter != m_table[i].end(); ++iter)
	{
		if (iter->first == key)
			found = &(iter->second);
	}

	if (!found)
		throw Exception("Error! Key not found!");

	return *found;
}

template<typename K, typename V>
const V & HashTable<K, V>::operator[](const K & key) const
{
	if (m_table.size() == 0)
		throw Exception("Error! Cannot access element in table of size zero!");

	V * found = nullptr;
	int i = (Hash(key) % m_table.size());

	list_t::iterator iter;
	for (iter = m_table[i].begin(); !found && iter != m_table[i].end(); ++iter)
	{
		if (iter->first == key)
			found = &(iter->second);
	}

	if (!found)
		throw Exception("Error! Key not found!");

	return *found;
}

//////
//	END OPERATORS
///////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////
//	PUBLIC METHODS
//////

template<typename K, typename V>
void HashTable<K, V>::Insert(K key, V value)
{
	if (Hash == nullptr)
		throw Exception("Error! Hash function cannot be NULL!");

	if (m_table.size() == 0)
		throw Exception("Error! Cannot insert into table of size zero!");

	int index = (Hash(key) % m_table.size());
	m_table[index].push_back(pair<K, V>(key, value));
}

template<typename K, typename V>
void HashTable<K, V>::SetHash(hash_t hash)
{
	Hash = hash;

	table_t copy = m_table;
	m_table.clear();
	m_table.resize(copy.size());

	Rehash(copy);
}

template<typename K, typename V>
void HashTable<K, V>::Resize(int size)
{
	if (size < 0)
		throw Exception("Error! Size cannot be negative!");

	table_t copy = m_table;
	m_table.clear();
	m_table.resize(size);

	Rehash(copy);
}

//////
//	END PUBLIC METHODS
///////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////
//	PRIVATE METHODS
//////

template<typename K, typename V>
void HashTable<K, V>::Rehash(table_t & copy)
{
	table_t::iterator ilist;
	for (ilist = copy.begin(); ilist != copy.end(); ++ilist)
	{
		list_t::iterator ipair;
		for (ipair = ilist->begin(); ipair != ilist->end(); ++ipair)
		{
			Insert(ipair->first, ipair->second);
		}
	}
}

//////
//	END PRIVATE METHODS
///////////////////////////////////////////////////////////////

#endif // HASHTABLE_H

