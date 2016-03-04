#ifndef HASHTABLEVALUEITERATOR_H
#define HASHTABLEVALUEITERATOR_H

#include "AbstractIterator.h"
#include "HashTable.h"
#include "HashTablePairIterator.h"
#include "Exception.h"

template<typename K, typename V>
class HashTableValueIterator : AbstractIterator<V>
{
public:
	// CTORS & DTOR
	HashTableValueIterator(HashTable<K, V> & table);
	HashTableValueIterator(const HashTableValueIterator<K, V> & copy);

	~HashTableValueIterator();

	// OPERATORS
	HashTableValueIterator<K, V> & operator=(const HashTableValueIterator<K, V> & rhs);

	virtual void Reset();

	virtual void MoveNext();

	virtual V & GetCurrent();

	virtual bool IsDone() const;

private:
	HashTablePairIterator<K, V> m_pairIter;
};


template<typename K, typename V>
HashTableValueIterator<K, V>::HashTableValueIterator(HashTable<K, V> & table)
	: m_pairIter(table)
{}

template<typename K, typename V>
HashTableValueIterator<K, V>::HashTableValueIterator(const HashTableValueIterator<K, V> & copy)
	: m_pairIter(copy.m_pairIter)
{}

template<typename K, typename V>
HashTableValueIterator<K, V>::~HashTableValueIterator()
{}

template<typename K, typename V>
HashTableValueIterator<K, V>& HashTableValueIterator<K, V>::operator=(const HashTableValueIterator<K, V>& rhs)
{
	if (this != &rhs)
	{
		m_pairIter = rhs.m_pairIter;
	}

	return *this;
}

template<typename K, typename V>
void HashTableValueIterator<K, V>::Reset()
{
	m_pairIter.Reset();
}

template<typename K, typename V>
void HashTableValueIterator<K, V>::MoveNext()
{
	m_pairIter.MoveNext();
}

template<typename K, typename V>
V & HashTableValueIterator<K, V>::GetCurrent()
{
	return m_pairIter.GetCurrent().second;
}

template<typename K, typename V>
bool HashTableValueIterator<K, V>::IsDone() const
{
	return m_pairIter.IsDone();
}

#endif // HASHTABLEVALUEITERATOR_H