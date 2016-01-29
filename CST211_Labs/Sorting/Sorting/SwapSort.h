/*****************************************************************************************
Author:			Garrett Fleischer
Filename:		SwapSort.h
Date Created:	1/23/16
Modifications:

*****************************************************************************************/

#ifndef SWAPSORT_H
#define SWAPSORT_H

#include "ISort.h"

template<typename RT, typename T>
class SwapSort : ISort < RT >
{
public:
	virtual void Sort(RT & ra, int length) = 0;

protected:
	void Swap(T & a, T & b);
};


template<typename RT, typename T>
void SwapSort<RT, T>::Swap(T & a, T & b)
{
	T temp(a);
	a = b;
	b = temp;
}


#endif // SWAPSORT_H
