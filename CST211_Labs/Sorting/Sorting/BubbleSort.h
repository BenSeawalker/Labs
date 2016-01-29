/*****************************************************************************************
Author:			Garrett Fleischer
Filename:		BubbleSort.h
Date Created:	1/23/16
Modifications:

*****************************************************************************************/

#ifndef BUBBLESORT_H
#define BUBBLESORT_H

#include "SwapSort.h"

template<typename RT, typename T>
class BubbleSort : SwapSort<RT, T>
{
public:
	BubbleSort(RT & ra, int length);

	virtual void Sort(RT & ra, int length);
};

template<typename RT, typename T>
BubbleSort<RT, T>::BubbleSort(RT & ra, int length)
{
	Sort(ra, length);
}

template<typename RT, typename T>
void BubbleSort<RT, T>::Sort(RT & ra, int length)
{
	for (int i = 0; i < length; ++i)
	{
		for (int j = 0; j < (length - i - 1); ++j)
		{
			if (ra[j + 1] < ra[j])
				Swap(ra[j + 1], ra[j]);
		}
	}
}


#endif // BUBBLESORT_H
