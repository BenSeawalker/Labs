/************************************************************************
* Author:		Garrett Fleischer
* Filename:		HashTablePairIterator.h
* Date Created:	3/5/16
* Modifications:
*************************************************************************/
#ifndef HASHTABLEPAIRITERATOR_H
#define HASHTABLEPAIRITERATOR_H

#include "AbstractIterator.h"
#include "HashTable.h"
#include "Exception.h"

template<typename K, typename V>
class HashTablePairIterator : AbstractIterator<pair<K, V>>
{
public:
	// CTORS & DTOR
	HashTablePairIterator(HashTable<K, V> & table);
	HashTablePairIterator(const HashTablePairIterator<K, V> & copy);

	~HashTablePairIterator();

	// OPERATORS
	HashTablePairIterator<K, V> & operator=(const HashTablePairIterator<K, V> & rhs);

	// METHODS
	virtual void Reset();

	virtual void MoveNext();

	virtual pair<K, V> & GetCurrent();

	virtual bool IsDone() const;

private:
	HashTable<K, V> * m_hashTable;
	typename HashTable<K, V>::table_t::iterator m_vector;
	typename HashTable<K, V>::list_t::iterator m_list;
};


///////////////////////////////////////////////////////////////
//	CTORS & DTOR
//////

template<typename K, typename V>
HashTablePairIterator<K, V>::HashTablePairIterator(HashTable<K, V> & table)
	: m_hashTable(&table)
{}

template<typename K, typename V>
HashTablePairIterator<K, V>::HashTablePairIterator(const HashTablePairIterator<K, V> & copy)
	: m_hashTable(copy.m_hashTable), m_vector(copy.m_vector), m_list(copy.m_list)
{}

template<typename K, typename V>
HashTablePairIterator<K, V>::~HashTablePairIterator()
{
	m_vector = m_hashTable->m_table.end();
	m_hashTable = nullptr;
}

//////
//	END CTORS & DTOR
///////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////
//	OPERATORS
//////

template<typename K, typename V>
HashTablePairIterator<K, V> & HashTablePairIterator<K, V>::operator=(const HashTablePairIterator<K, V> & rhs)
{
	if (this != &rhs)
	{
		m_hashTable = rhs.m_hashTable;
		m_vector = rhs.m_vector;
		m_list = rhs.m_list;
	}

	return *this;
}

//////
//	END OPERATORS
///////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////
//	PUBLIC METHODS
//////

template<typename K, typename V>
void HashTablePairIterator<K, V>::Reset()
{
	m_vector = m_hashTable->m_table.begin();
	m_list = m_vector->begin();

	if (m_list == m_vector->end())
		MoveNext();
}

template<typename K, typename V>
void HashTablePairIterator<K, V>::MoveNext()
{
	if (IsDone())
		throw Exception("Cannot access next element! Iterator is done...");

	if (m_list == m_vector->end())
	{
		if (++m_vector != m_hashTable->m_table.end())
		{
			m_list = m_vector->begin();
			if (m_list == m_vector->end())
				MoveNext();
		}
	}
	else
	{
		++m_list;
		if (m_list == m_vector->end())
			MoveNext();
	}
}

template<typename K, typename V>
pair<K, V> & HashTablePairIterator<K, V>::GetCurrent()
{
	if (IsDone())
		throw Exception("Cannot access current element! Iterator is done...");

	return (*m_list);
}

template<typename K, typename V>
bool HashTablePairIterator<K, V>::IsDone() const
{
	return (m_vector == m_hashTable->m_table.end());
}

//////
//	END PUBLIC METHODS
///////////////////////////////////////////////////////////////

#endif // HASHTABLEPAIRITERATOR_H

