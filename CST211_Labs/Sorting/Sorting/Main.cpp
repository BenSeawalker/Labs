/*****************************************************************************************
Author:			Garrett Fleischer
Filename:		Main.cpp
Date Created:	1/23/16
Modifications:

Lab/Assignment: L2 Sorts

Overview: Test different sorting algorithms

Input: Input is read through command line arguments

Output: The output for this program is to the console window and a file: "SORT_TIMES.txt"
		It consists of debugging text and data stored in the array.

		The output will have the following form:

			----------SORT TO TEST----------

			Before: 90 64 43 45 46 97 42 12 4 3 88 98 14 36 92 ...

			C array		Time: 0.017961 milliseconds
			Array<T>	Time: 0.082537 milliseconds
			vector<T>	Time: 0.638485 milliseconds

			Average		Time: 0.246328 milliseconds

			After: 1 1 1 2 2 3 3 4 4 5 5 7 8 8 12 ...


*****************************************************************************************/

#include "crtdbg_new.h"

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

#include <fstream>
using std::ofstream;

#include <sstream>
using std::stringstream;

#include <cstring>
using std::stoi;

#include "BubbleSort.h"
#include "FlaggedBubbleSort.h"
#include "SelectionSort.h"
#include "InsertionSort.h"
#include "ShellSort.h"
#include "HeapSort.h"
#include "MergeSort.h"
#include "QuickSort.h"

// My faster, but higher memory usage version of the selection sort
#include "MySelectionSort.h"


#define min(a, b) (((a) < (b)) ? (a) : (b))

// FUNCTION DEFINITIONS
template<typename RT>
void Print(RT ra, int size, stringstream & stream);

template<typename TPTR, typename TRA, typename TVEC>
void Test(const vector<int> & original, int *& ptr, Array<int> & ra, vector<int> & vec, int n, stringstream & stream);

void Reset(const vector<int> & original, int *& ptr, Array<int> & ra, vector<int> & vec);

// PROGRAM ENTRY POINT
int main(int argc, char * argv[])
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	stringstream stream;

	int n = 0;
	if (argc > 1)
		n = stoi(argv[1]);
	else
		cout << "Please enter the number of elements to sort" << endl;

	srand((unsigned)time(nullptr));
	vector<int> original(n);
	for (int i = 0; i < n; ++i)
		original[i] = (rand() % (n * 2));

	if (n > 0)
	{
		int * ptr = new int[n];
		Array<int> ra(n);
		vector<int> vec(n);
		Reset(original, ptr, ra, vec);

		stream << "\n----------TEST SORTING ALGORITHMS----------\n\n";
		stream << "Elements: " << n << endl;
		stream << "\n-------------------------------------------\n\n";

		// QuickSort
		stream << "\n----------QUICK SORT----------\n\n";
		Test<QuickSort<int *, int>, QuickSort<Array<int>, int>, QuickSort<vector<int>, int>>
			(original, ptr, ra, vec, n, stream);

		// MergeSort
		stream << "\n----------MERGE SORT----------\n\n";
		Test<MergeSort<int *, int>, MergeSort<Array<int>, int>, MergeSort<vector<int>, int>>
			(original, ptr, ra, vec, n, stream);

		// HeapSort
		stream << "\n----------HEAP SORT----------\n\n";
		Test<HeapSort<int *, int>, HeapSort<Array<int>, int>, HeapSort<vector<int>, int>>
			(original, ptr, ra, vec, n, stream);

		// ShellSort
		stream << "\n----------SHELL SORT----------\n\n";
		Test<ShellSort<int *, int>, ShellSort<Array<int>, int>, ShellSort<vector<int>, int>>
			(original, ptr, ra, vec, n, stream);

		// InsertionSort
		stream << "\n----------INSERTION SORT----------\n\n";
		Test<InsertionSort<int *, int>, InsertionSort<Array<int>, int>, InsertionSort<vector<int>, int>>
			(original, ptr, ra, vec, n, stream);

		// MySelectionSort
		stream << "\n----------MY SELECTION SORT----------\n\n";
		Test<MySelectionSort<int *, int>, MySelectionSort<Array<int>, int>, MySelectionSort<vector<int>, int>>
			(original, ptr, ra, vec, n, stream);

		// SelectionSort
		stream << "\n----------SELECTION SORT----------\n\n";
		Test<SelectionSort<int *, int>, SelectionSort<Array<int>, int>, SelectionSort<vector<int>, int>>
			(original, ptr, ra, vec, n, stream);

		// BUBBLE
		stream << "\n----------BRUTE BUBBLE SORT----------\n\n";
		Test<BubbleSort<int *, int>, BubbleSort<Array<int>, int>, BubbleSort<vector<int>, int>>
			(original, ptr, ra, vec, n, stream);

		// FLAGGED BUBBLE
		stream << "\n----------FLAGGED BUBBLE SORT----------\n\n";
		Test<FlaggedBubbleSort<int *, int>, FlaggedBubbleSort<Array<int>, int>, FlaggedBubbleSort<vector<int>, int>>
			(original, ptr, ra, vec, n, stream);


		delete[] ptr;

		// Store output in file
		ofstream file("SORT_TIMES.txt");
		if (file.is_open())
		{
			file << stream.str();
			file.close();
		}

		// Display to screen
		cout << stream.str() << endl;
	}

	system("pause");

	return 0;
}


/************************************************************************
* Purpose: To reset all given arrays back to the values in the original array
*
* Precondition:
*		All arrays must have length >= original
*
* Postcondition:
*		Modifies:	The contents of the given arrays
*		Throws:		N/A
*		Returns:	N/A
*************************************************************************/
void Reset(const vector<int> & original, int *& ptr, Array<int> & ra, vector<int> & vec)
{
	for (unsigned int i = 0; i < original.size(); i++)
	{
		ptr[i] = original[i];
		ra[i] = original[i];
		vec[i] = original[i];
	}
}

/************************************************************************
* Purpose: To display up to the first 20 elements in the given array
*
* Precondition:
*
* Postcondition:
*		Modifies:	stream contains the printed data
*		Throws:		N/A
*		Returns:	N/A
*************************************************************************/
template<typename RT>
void Print(RT ra, int size, stringstream & stream)
{
	for (int i = 0; i < min(size, 20); ++i)
		stream << ra[i] << ' ';

	stream << ((size > 20) ? "..." : "") << '\n' << endl;
}


/************************************************************************
* Purpose: To test the given type of sort on the given arrays
*
* Precondition:
*
* Postcondition:
*		Modifies:	The contents of the given arrays
					stream contains the printed data
*		Throws:		N/A
*		Returns:	N/A
*************************************************************************/
template<typename TPTR, typename TRA, typename TVEC>
void Test(const vector<int> & original, int *& ptr, Array<int> & ra, vector<int> & vec, int n, stringstream & stream)
{
	high_resolution_clock::time_point start;
	duration<float, std::milli> diff;
	duration<float, std::milli> average(0.0);

	// Print the array as it is before sorting
	stream << "Before: ";
	Print<int *>(ptr, n, stream);

	// Test c array
	start = high_resolution_clock::now();
	TPTR(ptr, n);
	diff = (high_resolution_clock::now() - start);
	average += diff;
	stream << "C array\t\tTime: " << diff.count() << " milliseconds" << endl;

	// Test my array class
	start = high_resolution_clock::now();
	TRA(ra, n);
	diff = (high_resolution_clock::now() - start);
	average += diff;
	stream << "Array<T>\tTime: " << diff.count() << " milliseconds" << endl;

	// Test vector class
	start = high_resolution_clock::now();
	TVEC(vec, n);
	diff = (high_resolution_clock::now() - start);
	average += diff;
	stream << "vector<T>\tTime: " << diff.count() << " milliseconds" << endl;

	// print the average time for all 3 arrays
	stream << "\nAverage\t\tTime: " << (average.count() / 3) << " milliseconds" << endl;

	// Print the array as it is after sorting
	stream << "\nAfter: ";
	Print<int *>(ptr, n, stream);

	// Reset the arrays back to their unsorted versions
	Reset(original, ptr, ra, vec);
}