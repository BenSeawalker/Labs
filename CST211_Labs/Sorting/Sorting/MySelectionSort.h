/*****************************************************************************************
Author:			Garrett Fleischer
Filename:		MySelectionSort.h
Date Created:	1/23/16
Modifications:

*****************************************************************************************/

#ifndef MYSELECTIONSORT_H
#define MYSELECTIONSORT_H

#include "ISort.h"

template<typename RT, typename T>
class MySelectionSort : ISort<RT>
{
public:
	MySelectionSort(RT & ra, int length);

	virtual void Sort(RT & ra, int length);

private:
	void Shift(RT & ra, T * copy, int & least, int & ra_len, int & cp_len);
};

template<typename RT, typename T>
MySelectionSort<RT, T>::MySelectionSort(RT & ra, int length)
{
	Sort(ra, length);
}


/*
*	Less memory efficient than a "real" selection sort,
*	but significantly faster and more consistent for all types of array
*/
template<typename RT, typename T>
void MySelectionSort<RT, T>::Sort(RT & ra, int length)
{
	// Make a copy of the original ra
	T * copy = new T[length];
	int copy_len = length,	// copy_len is same length as original ra
		ra_len = 0,			// ra_len is pretending to be zero
		least;

	for (int i = 0; i < length; ++i)
		copy[i] = ra[i];

	// While there is still data in the copy array
	while (copy_len > 0)
	{
		// find the least value in the copy array
		least = 0;
		for (int i = 1; i < copy_len; ++i)
		{
			if (copy[i] < copy[least])
				least = i;
		}

		// shift that value into the "end" of the original ra
		Shift(ra, copy, least, ra_len, copy_len);
	}

	delete[] copy;
}

template<typename RT, typename T>
void MySelectionSort<RT, T>::Shift(RT & ra, T * copy, int & least, int & ra_len, int & cp_len)
{
	// Shift value and increment ra_len
	ra[ra_len++] = copy[least];

	// Shift all values in copy array after least to the left by one, and decrement cp_len
	--cp_len;
	for (int i = least; i < cp_len; ++i)
		copy[i] = copy[i + 1];
}

#endif // MYSELECTIONSORT_H