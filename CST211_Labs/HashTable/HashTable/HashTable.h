/************************************************************************
* Author:		Garrett Fleischer
* Filename:		HashTable.h
* Date Created:	3/5/16
* Modifications:
*************************************************************************/
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


/************************************************************************
* Class: HashTable
*
* Purpose: This class is used for storing key value pairs
*
* Manager functions:
* 	HashTable (size : int, hash : hash_t)
*		hash is set to internal hash function by default
*	HashTable (const HashTable & copy)
*	operator = (const HashTable & rhs)
*	~HashTable()
*
* Methods:
*	operator [ ] (K key)
*		Returns the value with the given key
*
*	Insert(key : K, value : V) : void
*
*	SetHash(hash : hash_t) : void
*		hash is set to internal hash function if nullptr is passed
*
*	Resize(size : int) : void
*
*	Traverse(Visit : visit_t)
*
*************************************************************************/
template<typename K, typename V>
class HashTable
{
	friend class HashTablePairIterator<K, V>;

public:
	// TYPEDEFS
	typedef int(*hash_t)(const K & key);
	typedef void(*visit_t)(V & value);
	typedef void(*cvisit_t)(const V & value);
	typedef list<pair<K, V>> list_t;
	typedef vector<list_t> table_t;

	// CTORS & DTOR
	HashTable(int size = 0, hash_t hash = &InternalHash);
	HashTable(const HashTable & copy);

	~HashTable();

	// OPERATORS
	HashTable & operator=(const HashTable & rhs);
	V & operator[](const K & key);
	const V & operator[](const K & key) const;

	// METHODS
	void Insert(K key, V value);
	void Delete(K key);

	void SetHash(hash_t hash);

	void Resize(int size);

	void Traverse(visit_t Visit);
	void Traverse(cvisit_t Visit) const;

private:
	// METHODS
	void Rehash();

	const pair<K, V> * FindPair(const K & key) const;

	int Index(const K & key) const;

	static int InternalHash(const K & key);

	// MEMBERS
	table_t m_table;
	int m_size;
	hash_t Hash;
};

// Placed down here to avoid circular dependencies
#include "HashTablePairIterator.h"
#include "HashTableValueIterator.h"

///////////////////////////////////////////////////////////////
//	CTORS & DTOR
//////

template<typename K, typename V>
HashTable<K, V>::HashTable(int size, hash_t hash)
	: Hash(hash), m_table(size), m_size(size)
{}

template<typename K, typename V>
HashTable<K, V>::HashTable(const HashTable & copy)
	: m_table(copy.m_table), m_size(copy.m_size), Hash(copy.Hash)
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


/************************************************************************
* Purpose: Allow the consumer to access values based on their key
*
* Precondition:
*
* Postcondition:
*		Modifies:	N/A
*		Throws:		Exception("Error! Cannot access element in table of size zero!")
*					Exception("Error! Key not found!")
*		Returns:	Reference to the value associated with the given key
*************************************************************************/
template<typename K, typename V>
V & HashTable<K, V>::operator[](const K & key)
{
	if (m_size == 0)
		throw Exception("Error! Cannot access element in table of size zero!");

	pair<K, V> * found = const_cast<pair<K, V> *>(FindPair(key)); // keep things DRY...

	if (!found)
		throw Exception("Error! Key not found!");

	return found->second;
}

template<typename K, typename V>
const V & HashTable<K, V>::operator[](const K & key) const
{
	if (m_size == 0)
		throw Exception("Error! Cannot access element in table of size zero!");

	const pair<K, V> * found = FindPair(key);

	if (!found)
		throw Exception("Error! Key not found!");

	return found->second;
}

//////
//	END OPERATORS
///////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////
//	PUBLIC METHODS
//////

/************************************************************************
* Purpose: Allow the consumer to insert a key/value pair
*
* Precondition:
*
* Postcondition:
*		Modifies:	m_table
*		Throws:		Exception("Error! Cannot insert into table of size zero!")
*					Exception("Error! Key already exists!")
*		Returns:	N/A
*************************************************************************/
template<typename K, typename V>
void HashTable<K, V>::Insert(K key, V value)
{
	if (m_size == 0)
		throw Exception("Error! Cannot insert into table of size zero!");

	if (FindPair(key))
		throw Exception("Error! Key already exists!");

	int index = Index(key);
	m_table[index].push_back(pair<K, V>(key, value));
}

/************************************************************************
* Purpose: Allow the consumer to remove a key/value pair
*
* Precondition:
*	both K and V must overload == operator		
*
* Postcondition:
*		Modifies:	m_table[key]
*		Throws:		Exception("Error! Cannot delete element from a table of size zero!")
*					Exception("Error! Key not found!")
*		Returns:	N/A
*************************************************************************/
template<typename K, typename V>
void HashTable<K, V>::Delete(K key)
{
	if (m_size == 0)
		throw Exception("Error! Cannot delete element from a table of size zero!");

	const pair<K, V> * found = FindPair(key);
	if (!found)
		throw Exception("Error! Key not found!");

	m_table[Index(key)].remove(*found);
}

/************************************************************************
* Purpose: Allow the consumer to change the hash function
*
* Precondition:
*	@hash : function for hashing keys, or nullptr to use default internal hash
*
* Postcondition:
*		Modifies:	Hash
*		Throws:		N/A
*		Returns:	N/A
*************************************************************************/
template<typename K, typename V>
void HashTable<K, V>::SetHash(hash_t hash)
{
	Hash = (hash ? hash : &InternalHash);

	Rehash();
}


/************************************************************************
* Purpose: Allow the consumer to resize the table
*
* Precondition:
*
* Postcondition:
*		Modifies:	m_size, m_table
*		Throws:		Exception("Error! Cannot set size to a negative value!")
*		Returns:	N/A
*************************************************************************/
template<typename K, typename V>
void HashTable<K, V>::Resize(int size)
{
	if (size < 0)
		throw Exception("Error! Cannot set size to a negative value!");

	m_size = size;
	Rehash();
}

/************************************************************************
* Purpose: Allow the consumer to traverse through the list
*
* Precondition:
*	NOTE: This is only here to satisfy the lab requirements,
			provided iterators negate any benefits this function provides
*
* Postcondition:
*		Modifies:	N/A
*		Throws:		N/A
*		Returns:	N/A
*************************************************************************/
template<typename K, typename V>
void HashTable<K, V>::Traverse(visit_t Visit)
{
	HashTableValueIterator<K, V> vi(*this);
	for (vi.Reset(); !vi.IsDone(); vi.MoveNext())
		Visit(vi.GetCurrent());
}

template<typename K, typename V>
void HashTable<K, V>::Traverse(cvisit_t Visit) const
{
	for (int i = 0; i < m_size; ++i)
	{
		list_t::const_iterator iter;
		for (iter = m_table[i].begin(); iter != m_table[i].end(); ++iter)
			Visit(iter->second);
	}
}

//////
//	END PUBLIC METHODS
///////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////
//	PRIVATE METHODS
//////

/************************************************************************
* Purpose: Rebuild the table after changing the hash function or resizing
*
* Precondition:
*
* Postcondition:
*		Modifies:	Hash
*		Throws:		N/A
*		Returns:	N/A
*************************************************************************/
template<typename K, typename V>
void HashTable<K, V>::Rehash()
{
	if (m_size == 0)
		m_table.clear();
	else
	{
		HashTable<K, V> copy(*this);
		m_table.clear();
		m_table.resize(m_size);

		HashTablePairIterator<K, V> iter(copy);
		for (iter.Reset(); !iter.IsDone(); iter.MoveNext())
			Insert(iter.GetCurrent().first, iter.GetCurrent().second);
	}
}

/************************************************************************
* Purpose: DRY implementation for [] operators
*
* Precondition:
*
* Postcondition:
*		Modifies:	N/A
*		Throws:		N/A
*		Returns:	Found pair or nullptr if not found
*************************************************************************/
template<typename K, typename V>
const pair<K, V> * HashTable<K, V>::FindPair(const K & key) const
{
	const pair<K, V> * found = nullptr;
	int i = Index(key);

	list_t::const_iterator iter;
	for (iter = m_table[i].begin(); !found && iter != m_table[i].end(); ++iter)
	{
		if (iter->first == key)
			found = &(*iter);
	}

	return found;
}

/************************************************************************
* Purpose: DRY method of calculating the index from the hash
*
* Precondition:
*
* Postcondition:
*		Modifies:	N/A
*		Throws:		N/A
*		Returns:	N/A
*************************************************************************/
template<typename K, typename V>
int HashTable<K, V>::Index(const K & key) const
{
	return (unsigned(Hash(key)) % m_size);
}


/************************************************************************
* Purpose: Internal hash function in case the user doesn't provide one
*			
* Precondition:
*	NOTE: internal hash function does not work with objects that contain pointers
*			AND implicit conversion constructors. (i.e. std::string)
*			HashTable["abc"] = bad
*			HashTable[str_abc] = will work if Insert(str_abc, ...) was called prior
*
* Postcondition:
*		Modifies:	N/A
*		Throws:		N/A
*		Returns:	N/A
*************************************************************************/
template<typename K, typename V>
int HashTable<K, V>::InternalHash(const K & key)
{
	const char * data = reinterpret_cast<const char *>(&key);
	unsigned hash = 12345;

	size_t i;
	for (i = 0; i < sizeof(K); ++i)
	{
		//hash = ((hash << 6) ^ (hash >> 26) ^ data[i]);
		hash += ((hash << 4) + data[i]);
		hash ^= (hash >> 3);
		hash -= ((hash << 1) * (i + 1));
	}

	return hash;
}

//////
//	END PRIVATE METHODS
///////////////////////////////////////////////////////////////

#endif // HASHTABLE_H

