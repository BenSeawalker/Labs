/*****************************************************************************************
Author:			Garrett Fleischer
Filename:		InsertionSort.h
Date Created:	1/23/16
Modifications:

*****************************************************************************************/

#ifndef INSERTIONSORT_H
#define INSERTIONSORT_H

#include "ISort.h"

template<typename RT, typename T>
class InsertionSort : ISort < RT >
{
public:
	InsertionSort(RT & ra, int length);

	virtual void Sort(RT & ra, int length);
};

template<typename RT, typename T>
InsertionSort<RT, T>::InsertionSort(RT & ra, int length)
{
	Sort(ra, length);
}

template<typename RT, typename T>
void InsertionSort<RT, T>::Sort(RT & ra, int length)
{
	for (int i = 1; i < length; ++i)
	{
		T value = ra[i];
		int pos = i;

		while (pos > 0 && value < ra[pos - 1])
		{
			ra[pos] = ra[pos - 1];
			pos--;
		}

		ra[pos] = value;
	}
}

#endif // INSERTIONSORT_H