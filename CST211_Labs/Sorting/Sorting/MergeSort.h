/*****************************************************************************************
Author:			Garrett Fleischer
Filename:		MergeSort.h
Date Created:	1/23/16
Modifications:

*****************************************************************************************/

#ifndef MERGESORT_H
#define MERGESORT_H

#include "ISort.h"

template<typename RT, typename T>
class MergeSort : ISort<RT>
{
public:
	MergeSort(RT & ra, int length);

	virtual void Sort(RT & ra, int length);

private:
	void Split(RT & ra, T * temp, int left, int right);
	void Merge(RT & ra, T * temp, int left, int mid, int right);
};



template<typename RT, typename T>
MergeSort<RT, T>::MergeSort(RT & ra, int length)
{
	Sort(ra, length);
}

template<typename RT, typename T>
void MergeSort<RT, T>::Sort(RT & ra, int length)
{
	T * temp = new T[length];

	Split(ra, temp, 0, length - 1);

	delete[] temp;
}

template<typename RT, typename T>
void MergeSort<RT, T>::Split(RT & ra, T * temp, int left, int right)
{
	if (left < right)
	{
		// Done this way to avoid overflow error
		int mid = (left + (right - left) / 2) + 1;

		Split(ra, temp, left, mid - 1);
		Split(ra, temp, mid, right);
		Merge(ra, temp, left, mid, right);
	}
}



template<typename RT, typename T>
void MergeSort<RT, T>::Merge(RT & ra, T * temp, int left, int right, int right_end)
{
	int left_start = left;
	int left_end = right - 1;
	int pos = left;

	// Compare right first, as it will usually be the smaller array
	while (right <= right_end && left <= left_end)
	{
		if (ra[left] < ra[right])
			temp[pos++] = ra[left++];
		else
			temp[pos++] = ra[right++];
	}
	// Copy rest of left array
	while (left <= left_end)
		temp[pos++] = ra[left++];

	// Copy rest of right array
	while (right <= right_end)
		temp[pos++] = ra[right++];

	// Copy temp to ra
	for (int i = left_start; i <= right_end; ++i)
		ra[i] = temp[i];
}


#endif // MERGESORT_H
