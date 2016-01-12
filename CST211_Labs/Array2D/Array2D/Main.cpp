/************************************************************************
* Author:		Garrett Fleischer
* Filename:		Main.cpp
* Date Created:	1/4/16
* Modifications:
*	N/A
*************************************************************************/
#include <crtdbg.h> 
#define _CRTDBG_MAP_ALLOC

#include <iostream>
using std::cout;
using std::endl;

#include <string>
using std::string;
using std::to_string;


#include "Array2D.h"
#include "Row.h"
#include "Exception.h"
#include "ComplexData.h"

void TestSetRows(const Array2D<ComplexData> & ra);
void TestSetColumns(const Array2D<ComplexData> & ra);
void TestDataAccess(const Array2D<ComplexData> & ra);

void PrintArray2D(const Array2D<ComplexData> & ra);


int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);


	Array2D<ComplexData> ra(5, 5);

	for (int i = 0; i < ra.Rows(); ++i)
		for (int j = 0; j < ra.Columns(); ++j)
		{
			char c[2];
			c[0] = 'A' + i;
			c[1] = '\0';
			ra[i][j] = ComplexData(c);
		}

	cout << "\n**********INITIAL DATA**********\n";
	PrintArray2D(ra);

	cout << "\n**********TEST SET ROWS**********\n";
	TestSetRows(ra);

	cout << "\n**********TEST SET COLUMNS**********\n";
	TestSetColumns(ra);

	cout << "\n**********TEST DATA ACCESS**********\n";
	TestDataAccess(ra);

	cout << "\n**********TESTING ARRAY INTEGRITY**********\n";
	PrintArray2D(ra);

	cout << "\n**********TESTING PURGE()**********\n";
	ra.Purge();
	PrintArray2D(ra);

	cout << endl;
	system("pause");

	return 0;
}


void TestSetRows(const Array2D<ComplexData> & ra)
{
	cout << "\nTESTING COPY C'TOR\n";
	Array2D<ComplexData> ra2(ra);
	PrintArray2D(ra2);

	Array2D<ComplexData> ra3(3, 3);

	cout << "\nTESTING ROWS WITH EMPTY 3x3 ARRAY\n";
	cout << "\nsetRows(10)\n";
	ra3.SetRows(10);
	PrintArray2D(ra3);
	cout << "\nsetRows(2)\n";
	ra3.SetRows(2);
	PrintArray2D(ra3);
	try
	{
		cout << "\nsetRows(-23)\n";
		ra3.SetRows(-23);
		PrintArray2D(ra3);
	}
	catch (const Exception & e)
	{
		cout << '\n' << e << '\n' << endl;
	}


	cout << "\nTESTING ROWS WITH FULL ARRAY\n";
	cout << "\nsetRows(10)\n";
	ra2.SetRows(10);
	PrintArray2D(ra2);
	cout << "\nsetRows(2)\n";
	ra2.SetRows(2);
	PrintArray2D(ra2);
	cout << "\nsetRows(5)\n";
	ra2.SetRows(5);
	PrintArray2D(ra2);
}

void TestSetColumns(const Array2D<ComplexData> & ra)
{
	cout << "\nTESTING OP=\n";
	Array2D<ComplexData> ra2;
	ra2 = ra;
	PrintArray2D(ra2);

	Array2D<ComplexData> ra3(3, 3);

	cout << "\nTESTING COLUMNS WITH EMPTY 3x3 ARRAY\n";
	cout << "\nsetColumns(10)\n";
	ra3.SetColumns(10);
	PrintArray2D(ra3);
	cout << "\nsetColumns(2)\n";
	ra3.SetColumns(2);
	PrintArray2D(ra3);
	try
	{
		cout << "\nsetColumns(-23)\n";
		ra3.SetColumns(-23);
		PrintArray2D(ra3);
	}
	catch (const Exception & e)
	{
		cout << '\n' << e << '\n' << endl;
	}


	cout << "\nTESTING COLUMNS WITH FULL ARRAY\n";
	cout << "\nsetColumns(10)\n";
	ra2.SetColumns(10);
	PrintArray2D(ra2);
	cout << "\nsetColumns(2)\n";
	ra2.SetColumns(2);
	PrintArray2D(ra2);
	cout << "\nsetColumns(5)\n";
	ra2.SetColumns(5);
	PrintArray2D(ra2);
}

void TestDataAccess(const Array2D<ComplexData> & ra)
{
	cout << "\nTESTING CONTAINS ON EXISTING INDEX\n";
	cout << "\nra.Contains ( 2, 3 )\n";
	cout << (ra.Contains(2, 3) ? "True!" : "False!") << endl;

	cout << "\nTESTING CONTAINS ON NONEXISTING INDEX\n";
	cout << "\nra.Contains ( -5, 32 )\n";
	cout << (ra.Contains(-5, 32) ? "True!" : "False!") << endl;


	cout << "\nTESTING OP[][] ON EXISTING INDEX\n";
	cout << "\nra [ 3 ] [ 1 ]\n";
	cout << ra[3][1] << endl;

	try
	{
		cout << "\nTESTING OP[][] ON NONEXISTING ROW\n";
		cout << "\nra[ 200 ] [ 3 ]\n";
		cout << ra[200][3] << endl;
	}
	catch (const Exception & e)
	{
		cout << '\n' << e << '\n' << endl;
	}

	try
	{
		cout << "\nTESTING OP[][] ON NONEXISTING COLUMN\n";
		cout << "\nra [ 2 ] [ 5 ]\n";
		cout << ra[2][5] << endl;
	}
	catch (const Exception & e)
	{
		cout << '\n' << e << '\n' << endl;
	}


	cout << "\nTESTING SELECT() ON EXISTING INDEX\n";
	cout << "\nSelect ( 1 , 3 )\n";
	cout << ra.Select(1, 3) << endl;

	try
	{
		cout << "\nTESTING SELECT() ON NONEXISTING ROW\n";
		cout << "\nSelect ( 5 , 3 )\n";
		cout << ra.Select(5, 3) << endl;
	}
	catch (const Exception & e)
	{
		cout << '\n' << e << '\n' << endl;
	}

	try
	{
		cout << "\nTESTING SELECT() ON NONEXISTING COLUMN\n";
		cout << "\nSelect ( 1 , -18 )\n";
		cout << ra.Select(1, -18) << endl;
	}
	catch (const Exception & e)
	{
		cout << '\n' << e << '\n' << endl;
	}
}


void PrintArray2D(const Array2D<ComplexData> & ra)
{
	if (ra.Rows() == 0 || ra.Columns() == 0)
		cout << "Array2D is empty..." << endl;

	for (int i = 0; i < ra.Rows(); ++i)
	{
		for (int j = 0; j < ra.Columns(); ++j)
			cout << ra[i][j] << ' ';

		cout << endl;
	}
}

