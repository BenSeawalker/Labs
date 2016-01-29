/*****************************************************************************************
Author:			Garrett Fleischer
Filename:		FlaggedBubbleSort.h
Date Created:	1/23/16
Modifications:

*****************************************************************************************/

#ifndef FLAGGEDBUBBLESORT_H
#define FLAGGEDBUBBLESORT_H

#include "SwapSort.h"

template<typename RT, typename T>
class FlaggedBubbleSort : SwapSort<RT, T>
{
public:
	FlaggedBubbleSort(RT & ra, int length);

	virtual void Sort(RT & ra, int length);
};

template<typename RT, typename T>
FlaggedBubbleSort<RT, T>::FlaggedBubbleSort(RT & ra, int length)
{
	Sort(ra, length);
}

template<typename RT, typename T>
void FlaggedBubbleSort<RT, T>::Sort(RT & ra, int length)
{
	bool swapped = true;
	for (int i = 0; i < length && swapped; ++i)
	{
		swapped = false;
		for (int j = 0; j < (length - i - 1); ++j)
		{
			if (ra[j + 1] < ra[j])
			{
				swapped = true;
				Swap(ra[j + 1], ra[j]);
			}
		}
	}
}


#endif // FLAGGEDBUBBLESORT_H
