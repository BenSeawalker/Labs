#include <algorithm>
#include <ctime>
using std::clock;
using std::time;

#include <iostream>
using std::cout;
using std::cin;
using std::endl;

#include "BubbleSort.h"
#include "FlaggedBubbleSort.h"
#include "SelectionSort.h"
#include "InsertionSort.h"
#include "ShellSort.h"

#include "MySort.h"

#define min(a,b)    (((a) < (b)) ? (a) : (b))

template<typename RT>
void Print(RT ra, int size);

template<typename TPTR, typename TRA, typename TVEC>
void Test(const Array<int> & original, int *& ptr, Array<int> & ra, vector<int> & vec, int n);

void Reset(const Array<int> & original, int *& ptr, Array<int> & ra, vector<int> & vec);

int main()
{
	int n = 10;

	srand((unsigned)time(nullptr));
	Array<int> original(n);
	for (int i = 0; i < n; ++i)
		original[i] = (rand() % (n * 2));

	int * ptr = new int[n];
	Array<int> ra(n);
	vector<int> vec(n);
	Reset(original, ptr, ra, vec);

	

	// ShellSort
	cout << "\n----------SHELL SORT----------\n\n";
	Test<ShellSort<int *, int>, ShellSort<Array<int>, int>, ShellSort<vector<int>, int>>
		(original, ptr, ra, vec, n);

	// SelectionSort
	cout << "\n----------SELECTION SORT----------\n\n";
	Test<SelectionSort<int *, int>, SelectionSort<Array<int>, int>, SelectionSort<vector<int>, int>>
		(original, ptr, ra, vec, n);

	// InsertionSort
	cout << "\n----------INSERTION SORT----------\n\n";
	Test<InsertionSort<int *, int>, InsertionSort<Array<int>, int>, InsertionSort<vector<int>, int>>
		(original, ptr, ra, vec, n);

	// MySort
	cout << "\n----------My BUBBLE SORT----------\n\n";
	Test<MySort<int *, int>, MySort<Array<int>, int>, MySort<vector<int>, int>>
		(original, ptr, ra, vec, n);

	// FLAGGED BUBBLE
	cout << "\n----------FLAGGED BUBBLE SORT----------\n\n";
	Test<FlaggedBubbleSort<int *, int>, FlaggedBubbleSort<Array<int>, int>, FlaggedBubbleSort<vector<int>, int>>
		(original, ptr, ra, vec, n);

	// BUBBLE
	cout << "\n----------BRUTE BUBBLE SORT----------\n\n";
	Test<BubbleSort<int *, int>, BubbleSort<Array<int>, int>, BubbleSort<vector<int>, int>>
		(original, ptr, ra, vec, n);
	

	delete[] ptr;

	cout << endl;
	system("pause");

	return 0;
}

void Reset(const Array<int> & original, int *& ptr, Array<int> & ra, vector<int> & vec)
{
	for (int i = 0; i < original.Length(); i++)
	{
		ptr[i] = original[i];
		ra[i] = original[i];
		vec[i] = original[i];
	}
}

template<typename RT>
void Print(RT ra, int size)
{
	cout << '\n';
	for (int i = 0; i < min(size, 10); ++i)
		cout << ra[i] << ' ';

	cout << '\n' << endl;
}

template<typename TPTR, typename TRA, typename TVEC>
void Test(const Array<int> & original, int *& ptr, Array<int> & ra, vector<int> & vec, int n)
{
	clock_t start = clock();
	TPTR(ptr, n);
	cout << "Time: " << clock() - start << " milliseconds" << endl;

	start = clock();
	TRA(ra, n);
	cout << "Time: " << clock() - start << " milliseconds" << endl;

	start = clock();
	TVEC(vec, n);
	cout << "Time: " << clock() - start << " milliseconds" << endl;

	Print<int *>(ptr, n);
	Reset(original, ptr, ra, vec);
}