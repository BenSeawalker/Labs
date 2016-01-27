#include <algorithm>
#include <ctime>
using std::time;

#include <chrono>
using std::chrono::high_resolution_clock;
using std::chrono::duration;
using std::chrono::duration_cast;

#include <iostream>
using std::cout;
using std::cin;
using std::endl;

#include "BubbleSort.h"
#include "FlaggedBubbleSort.h"
#include "SelectionSort.h"
#include "InsertionSort.h"
#include "ShellSort.h"
#include "HeapSort.h"

#include "MySelectionSort.h"

#define min(a,b)    (((a) < (b)) ? (a) : (b))

template<typename RT>
void Print(RT ra, int size);

template<typename TPTR, typename TRA, typename TVEC>
void Test(const Array<int> & original, int *& ptr, Array<int> & ra, vector<int> & vec, int n);

void Reset(const Array<int> & original, int *& ptr, Array<int> & ra, vector<int> & vec);

int main()
{
	int n = 10000;

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

	// HeapSort
	cout << "\n----------HEAP SORT----------\n\n";
	Test<HeapSort<int *, int>, HeapSort<Array<int>, int>, HeapSort<vector<int>, int>>
		(original, ptr, ra, vec, n);

	// MySelectionSort
	cout << "\n----------my selection sort----------\n\n";
	Test<MySelectionSort<int *, int>, MySelectionSort<Array<int>, int>, MySelectionSort<vector<int>, int>>
		(original, ptr, ra, vec, n);

	// InsertionSort
	cout << "\n----------INSERTION SORT----------\n\n";
	Test<InsertionSort<int *, int>, InsertionSort<Array<int>, int>, InsertionSort<vector<int>, int>>
		(original, ptr, ra, vec, n);

	// SelectionSort
	cout << "\n----------SELECTION SORT----------\n\n";
	Test<SelectionSort<int *, int>, SelectionSort<Array<int>, int>, SelectionSort<vector<int>, int>>
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
	duration<double> average;
	high_resolution_clock::time_point start;
	duration<double> diff;

	start = high_resolution_clock::now();
	TPTR(ptr, n);
	diff = duration_cast<duration<double>>(high_resolution_clock::now() - start);
	average += diff;
	cout << "C array\t\tTime: " << (diff.count() * 100) << " milliseconds" << endl;

	start = high_resolution_clock::now();
	TRA(ra, n);
	diff = duration_cast<duration<double>>(high_resolution_clock::now() - start);
	average += diff;
	cout << "Array<T>\tTime: " << (diff.count() * 100) << " milliseconds" << endl;

	start = high_resolution_clock::now();
	TVEC(vec, n);
	diff = duration_cast<duration<double>>(high_resolution_clock::now() - start);
	average += diff;
	cout << "vector<T>\tTime: " << (diff.count() * 100) << " milliseconds" << endl;

	cout << "\nAverage\t\tTime: " << (average.count() * 100) / 3.0f << " milliseconds" << endl;

	Print<int *>(ptr, n);
	Reset(original, ptr, ra, vec);
}