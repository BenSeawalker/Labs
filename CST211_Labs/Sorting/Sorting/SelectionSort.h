#ifndef SELECTIONSORT_H
#define SELECTIONSORT_H

#include "ISort.h"

template<typename RT, typename T>
class SelectionSort : ISort<RT>
{ 
public:
	SelectionSort(RT & ra, int length);

protected:
	virtual void Sort(RT & ra, int length);
	void Shift(RT & ra, T * cp, int cp_i, int & ra_len, int & cp_len);
};

template<typename RT, typename T>
SelectionSort<RT, T>::SelectionSort(RT & ra, int length)
{
	Sort(ra, length);
}

template<typename RT, typename T>
void SelectionSort<RT, T>::Sort(RT & ra, int length)
{
	T * copy = new T[length];
	int copy_len = length;
	int ra_len = 0;

	for (int i = 0; i < length; ++i)
		copy[i] = ra[i];

	while (copy_len > 0)
	{
		int lowest_index = 0;
		for (int i = 1; i < copy_len; ++i)
		{
			if (copy[i] < copy[lowest_index])
				lowest_index = i;
		}
		Shift(ra, copy, lowest_index, ra_len, copy_len);
	}

	delete[] copy;
}

template<typename RT, typename T>
void SelectionSort<RT, T>::Shift(RT & ra, T * cp, int cp_i, int & ra_len, int & cp_len)
{
	ra[ra_len] = cp[cp_i];
	ra_len++;

	for (int i = cp_i; i < cp_len; ++i)
		cp[i] = cp[i + 1];

	cp_len--;
}

#endif // SELECTIONSORT_H