#ifndef LISTITERATOR_H
#define LISTITERATOR_H

#include "AbstractIterator.h"
#include "DoubleLinkedList.h"
#include "ListNode.h"

template<typename ST, typename RT, typename T>
class ListIterator : public AbstractIterator<ST, RT, T>
{
public:
	// DTOR
	~ListIterator();

	// METHODS
	virtual void Reset();

	virtual void MoveNext();

	virtual RT & GetCurrent();

	virtual bool IsDone() const;

protected:
	// CTORS
	ListIterator(ST * list);
	ListIterator(const ListIterator & copy);

	// OPERATORS
	ListIterator & operator=(const ListIterator & rhs);

	// MEMBERS
	ST * m_list;
	ListNode<T> * m_current;
};


template<typename ST, typename RT, typename T>
ListIterator<ST, RT, T>::ListIterator(ST * list)
	: m_list(list), m_current(list->m_head)
{}

template<typename ST, typename RT, typename T>
ListIterator<ST, RT, T>::ListIterator(const ListIterator & copy)
	: m_list(copy.m_list), m_current(copy.m_current)
{}

template<typename ST, typename RT, typename T>
ListIterator<ST, RT, T>::~ListIterator()
{
	m_list = nullptr;
	m_current = nullptr;
}

template<typename ST, typename RT, typename T>
ListIterator<ST, RT, T> & ListIterator<ST, RT, T>::operator=(const ListIterator & rhs)
{
	if (this != &rhs)
	{
		m_list = rhs.m_list;
		m_current = rhs.m_current;
	}
	
	return *this;
}

template<typename ST, typename RT, typename T>
void ListIterator<ST, RT, T>::Reset()
{
	if (!m_list)
		throw Exception("Error accessing non-existent list!");

	m_current = m_list->m_head;
}

template<typename ST, typename RT, typename T>
void ListIterator<ST, RT, T>::MoveNext()
{
	if (IsDone())
		throw Exception("Cannot access next element! Iterator is done.");

	m_current = m_current->Next();
}

template<typename ST, typename RT, typename T>
RT & ListIterator<ST, RT, T>::GetCurrent()
{
	if (IsDone())
		throw Exception("Cannot access current element! Iterator is done.");

	return m_current->Data();
}

template<typename ST, typename RT, typename T>
bool ListIterator<ST, RT, T>::IsDone() const
{
	return m_current == nullptr;
}

#endif // LISTITERATOR_H

