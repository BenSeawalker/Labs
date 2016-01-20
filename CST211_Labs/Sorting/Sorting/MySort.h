#ifndef MYSORT_H
#define MYSORT_H

#include "SwapSort.h"

template<typename RT, typename T>
class MySort : SwapSort<RT, T>
{
public:
	MySort(RT & ra, int length);

private:
	virtual void Sort(RT & ra, int length);
};

template<typename RT, typename T>
MySort<RT, T>::MySort(RT & ra, int length)
{
	Sort(ra, length);
}

template<typename RT, typename T>
void MySort<RT, T>::Sort(RT & ra, int length)
{
	for (int i = 0; i < length; ++i)
	{
		for (int j = (i + 1); j < (length); ++j)
		{
			if (ra[j] < ra[i])
				Swap(ra[j], ra[i]);
		}
	}
}


#endif // MYSORT_H
