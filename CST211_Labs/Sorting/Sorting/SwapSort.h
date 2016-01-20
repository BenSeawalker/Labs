#ifndef SWAPSORT_H
#define SWAPSORT_H

#include "ISort.h"

template<typename RT, typename T>
class SwapSort : ISort < RT >
{
protected:
	virtual void Sort(RT & ra, int length) = 0;
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
