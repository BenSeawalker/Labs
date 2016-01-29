/*****************************************************************************************
Author:			Garrett Fleischer
Filename:		QuickSort.h
Date Created:	1/23/16
Modifications:

*****************************************************************************************/

#ifndef QUICKSORT_H
#define QUICKSORT_H

#include "SwapSort.h"

template<typename RT, typename T>
class QuickSort : SwapSort<RT, T>
{
public:
	QuickSort(RT & ra, int length);

	virtual void Sort(RT & ra, int length);

private:
	void Sort(RT & ra, int first, int last);
};

template<typename RT, typename T>
QuickSort<RT, T>::QuickSort(RT & ra, int length)
{
	Sort(ra, length);
}

template<typename RT, typename T>
void QuickSort<RT, T>::Sort(RT & ra, int length)
{
	if (length > 1)
	{
		int max = 0;
		for (int i = 1; i < length; ++i)
			if (ra[max] < ra[i])
				max = i;

		Swap(ra[length - 1], ra[max]);
		Sort(ra, 0, length - 2);
	}
}

template<typename RT, typename T>
void QuickSort<RT, T>::Sort(RT & ra, int first, int last)
{
	int small = first + 1,
		large = last;
	T pivot = ra[first];

	while (small <= large)
	{
		while (ra[small] < pivot)
			++small;
		while (ra[large] > pivot)
			--large;

		if (small < large)
			Swap(ra[small++], ra[large--]);
		else
			++small;
	}

	Swap(ra[large], ra[first]);
	if (first < large - 1)
		Sort(ra, first, large - 1);
	if (last > large + 1)
		Sort(ra, large + 1, last);
}




#endif // QUICKSORT_H
