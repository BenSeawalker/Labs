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
	typedef int(*khash_t)(const K & key);
//	typedef int(*vhash_t)(const V & value);
	typedef void(*visit_t)(V & value);
	typedef list<pair<K, V>> list_t;
	typedef vector<list_t> table_t;

	// CTORS & DTOR
	HashTable(khash_t hash = nullptr, int size = 0);
	HashTable(const HashTable & copy);

	~HashTable();

	// OPERATORS
	HashTable & operator=(const HashTable & rhs);
	V & operator[](const K & key);
	const V & operator[](const K & key) const;

	// METHODS
	void Insert(K key, V value);

	void SetHash(khash_t hash);

	void Resize(int size);

	// unnecessary traverse...
	void Traverse(visit_t Visit);

private:
	// METHODS
	void Rehash();

	// MEMBERS
	table_t m_table;
	int m_size;
	khash_t Hash;
};

// Placed down here to avoid circular dependencies
#include "HashTablePairIterator.h"
#include "HashTableValueIterator.h"

///////////////////////////////////////////////////////////////
//	CTORS & DTOR
//////

template<typename K, typename V>
HashTable<K, V>::HashTable(khash_t hash, int size)
	: Hash(hash), m_table(size), m_size(size)
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
		m_size = rhs.m_size;
		Hash = rhs.Hash;
	}

	return *this;
}

template<typename K, typename V>
V & HashTable<K, V>::operator[](const K & key)
{
	if (m_size == 0)
		throw Exception("Error! Cannot access element in table of size zero!");

	V * found = nullptr;
	int i = abs(Hash(key) % m_size);

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
	if (m_size == 0)
		throw Exception("Error! Cannot access element in table of size zero!");

	V * found = nullptr;
	int i = abs(Hash(key) % m_size);

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

	if (m_size == 0)
		throw Exception("Error! Cannot insert into table of size zero!");

	int index = abs(Hash(key) % m_size);
	m_table[index].push_back(pair<K, V>(key, value));
}

template<typename K, typename V>
void HashTable<K, V>::SetHash(khash_t hash)
{
	Hash = hash;
	Rehash();
}

template<typename K, typename V>
void HashTable<K, V>::Resize(int size)
{
	if (size < 0)
		throw Exception("Error! Size cannot be negative!");

	m_size = size;
	Rehash();
}

template<typename K, typename V>
void HashTable<K, V>::Traverse(visit_t Visit)
{
	HashTableValueIterator<K, V> vi(*this);
	for (vi.Reset(); !vi.IsDone(); vi.MoveNext())
		Visit(vi.GetCurrent());
}

//////
//	END PUBLIC METHODS
///////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////
//	PRIVATE METHODS
//////

template<typename K, typename V>
void HashTable<K, V>::Rehash()
{
	HashTable<K, V> copy(*this);
	m_table.clear();
	m_table.resize(m_size);

	HashTablePairIterator<K, V> pi(copy);
	for (pi.Reset(); !pi.IsDone(); pi.MoveNext())
		Insert(pi.GetCurrent().first, pi.GetCurrent().second);
}

//////
//	END PRIVATE METHODS
///////////////////////////////////////////////////////////////

#endif // HASHTABLE_H

