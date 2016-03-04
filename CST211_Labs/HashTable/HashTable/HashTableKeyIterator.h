#ifndef HASHTABLEKEYITERATOR_H;
#define HASHTABLEKEYITERATOR_H

#include "AbstractIterator.h"
#include "HashTable.h"
#include "HashTablePairIterator.h"
#include "Exception.h"

template<typename K, typename V>
class HashTableKeyIterator : AbstractIterator<K>
{
public:
	// CTORS & DTOR
	HashTableKeyIterator(HashTable<K, V> & table);
	HashTableKeyIterator(const HashTableKeyIterator<K, V> & copy);

	~HashTableKeyIterator();

	// OPERATORS
	HashTableKeyIterator<K, V> & operator=(const HashTableKeyIterator<K, V> & rhs);

	virtual void Reset();

	virtual void MoveNext();

	virtual K & GetCurrent();

	virtual bool IsDone() const;

private:
	HashTablePairIterator<K, V> m_pairIter;
};


template<typename K, typename V>
HashTableKeyIterator<K, V>::HashTableKeyIterator(HashTable<K, V> & table)
	: m_pairIter(table)
{}

template<typename K, typename V>
HashTableKeyIterator<K, V>::HashTableKeyIterator(const HashTableKeyIterator<K, V> & copy)
	: m_pairIter(copy.m_pairIter)
{}

template<typename K, typename V>
HashTableKeyIterator<K, V>::~HashTableKeyIterator()
{}

template<typename K, typename V>
HashTableKeyIterator<K, V>& HashTableKeyIterator<K, V>::operator=(const HashTableKeyIterator<K, V>& rhs)
{
	if (this != &rhs)
	{
		m_pairIter = rhs.m_pairIter;
	}

	return *this;
}

template<typename K, typename V>
void HashTableKeyIterator<K, V>::Reset()
{
	m_pairIter.Reset();
}

template<typename K, typename V>
void HashTableKeyIterator<K, V>::MoveNext()
{
	m_pairIter.MoveNext();
}

template<typename K, typename V>
K & HashTableKeyIterator<K, V>::GetCurrent()
{
	return m_pairIter.GetCurrent().first;
}

template<typename K, typename V>
bool HashTableKeyIterator<K, V>::IsDone() const
{
	return m_pairIter.IsDone();
}

#endif // HASHTABLEKEYITERATOR_H