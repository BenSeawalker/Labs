#ifndef ShellSort_h__
#define ShellSort_h__

#include "ISort.h"

template<typename RT, typename T>
class ShellSort : ISort<RT>
{
public:
	ShellSort(RT & ra, int length);

protected:
	virtual void Sort(RT & ra, int length);
};

template<typename RT, typename T>
ShellSort<RT, T>::ShellSort(RT & ra, int length)
{
	Sort(ra, length);
}

template<typename RT, typename T>
void ShellSort<RT, T>::Sort(RT & ra, int length)
{
	int gap = 0;
	while (gap * 3 + 1 < length)
		gap = gap * 3 + 1;

	while (gap > 0)
	{
		for (int i = gap; i < length; ++i)
		{
			T value = ra[i];
			int pos = i;

			while (pos >= gap && value < ra[pos - gap])
			{
				ra[pos] = ra[pos - gap];
				pos -= gap;
			}

			ra[pos] = value;
		}

		gap = (gap - 1) / 3;
	}
}


#endif // ShellSort_h__