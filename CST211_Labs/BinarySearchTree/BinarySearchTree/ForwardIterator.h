#ifndef FORWARDITERATOR_H
#define FORWARDITERATOR_H

#include "ListIterator.h"

template<typename ST, typename RT, typename T>
class ForwardIterator : public ListIterator<ST, RT, T>
{
public:
	// CTORS & DTOR
	ForwardIterator(ST * list);
	ForwardIterator(const ForwardIterator & copy);

	virtual ~ForwardIterator();

	// OPERATORS
	ForwardIterator<ST, RT, T> & operator=(const ForwardIterator & rhs);
};


template<typename ST, typename RT, typename T>
ForwardIterator<ST, RT, T>::ForwardIterator(ST * list)
	: ListIterator(list)
{}

template<typename ST, typename RT, typename T>
ForwardIterator<ST, RT, T>::ForwardIterator(const ForwardIterator<ST, RT, T> & copy)
	: ListIterator(copy)
{}

template<typename ST, typename RT, typename T>
ForwardIterator<ST, RT, T>::~ForwardIterator()
{}

template<typename ST, typename RT, typename T>
ForwardIterator<ST, RT, T> & ForwardIterator<ST, RT, T>::operator=(const ForwardIterator<ST, RT, T> & rhs)
{
	if (this != &rhs)
	{
		ListIterator::operator=(rhs);
	}

	return *this;
}

#endif // FORWARDITERATOR_H