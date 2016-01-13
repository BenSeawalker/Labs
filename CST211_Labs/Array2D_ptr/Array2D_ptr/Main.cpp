/*****************************************************************************************
Author:			Garrett Fleischer
Filename:		Main.cpp
Date Created:	1/7/16
Modifications:

Lab/Assignment: A4

Overview: Test class Array2D<T> which uses T**

Input: All input is hard coded into the stub file: Main.cpp

Output: The output for this program is to the console window and consist of debugging
text and data stored in the array. The output will have the following form:

-----------------------------------------------------------------------

///////////////////////// SECTION HEADER /////////////////////////

*************** TEST HEADER ***************
Input: ra.SetSize(3, 5)
Output:
. 0 1 2 3 4
0 * * * * *
1 * * * * *
2 * * * * *

*****************************************************************************************/
#include <crtdbg.h> 
#define _CRTDBG_MAP_ALLOC

#include <iostream>
using std::cout;
using std::endl;


#include "Array2D.h"
#include "ComplexData.h"

void TestCanonical(const Array2D<ComplexData> & ra);
void TestDataAccess(const Array2D<ComplexData> & ra);
void TestDataModification(Array2D<ComplexData> & ra);
void TestMisc(Array2D<ComplexData> & ra);

void PrintArray2D(const Array2D<ComplexData> & ra);


int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	// Create test array and fill it with data
	Array2D<ComplexData> ra(5, 5);
	for (int i = 0; i < ra.getRow(); ++i)
	{
		for (int j = 0; j < ra.getColumn(); ++j)
		{
			char c[2];
			c[0] = 'A' + i + j;
			c[1] = '\0';
			ra[i][j] = ComplexData(c);
		}
	}

	// Test all Array2D functions
	TestCanonical(ra);
	TestDataAccess(ra);
	TestDataModification(ra);
	TestMisc(ra);

	cout << endl;
	system("pause");

	return 0;
}



void TestCanonical(const Array2D<ComplexData> & ra)
{
	cout << "\n\n\n--------------------------------------------------------------------------";
	cout << "\n\n\n///////////////////////// TEST CANONICAL METHODS /////////////////////////\n";

	cout << "\n*************** TEST ra CONTENT ***************\n";
	cout << "Input: ra\n";
	PrintArray2D(ra);

	cout << "\n*************** TEST DEFAULT CTOR ***************\n";
	cout << "Input: Array2D<ComplexData>()\n";
	PrintArray2D(Array2D<ComplexData>());

	cout << "\n*************** TEST TWO ARG CTOR ***************\n";
	cout << "Input: Array2D<ComplexData>( 4, 8 )\n";
	PrintArray2D(Array2D<ComplexData>(4, 8));

	cout << "\n*************** TEST TWO ARG CTOR WITH NEGATIVE ROW ***************\n";
	cout << "Input: Array2D<ComplexData>( -4, 8 )\nOutput:\n";
	try	{
		PrintArray2D(Array2D<ComplexData>(-4, 8));
	}
	catch (const Exception & exc) {
		cout << exc << endl;
	}

	cout << "\n*************** TEST TWO ARG CTOR WITH NEGATIVE COLUMN ***************\n";
	cout << "Input: Array2D<ComplexData>( 4, -8 )\nOutput:\n";
	try	{
		PrintArray2D(Array2D<ComplexData>(4, -8));
	}
	catch (const Exception & exc) {
		cout << exc << endl;
	}


	cout << "\n*************** TEST COPY CTOR ***************\n";
	cout << "Input: Array2D<ComplexData>(ra)\n";
	PrintArray2D(Array2D<ComplexData>(ra));

	cout << "\n*************** TEST OP= ***************\n";
	cout << "Input: ra2 = ra\n";
	Array2D<ComplexData> ra2;
	ra2 = ra;
	PrintArray2D(ra2);

	cout << "\n*************** TEST PURGE ***************\n";
	cout << "Input: ra2.Purge()\n";
	ra2.Purge();
	PrintArray2D(ra2);


	cout << endl;
}

void TestDataAccess(const Array2D<ComplexData> & ra)
{
	cout << "\n\n\n--------------------------------------------------------------------------";
	cout << "\n\n\n///////////////////////// TEST DATA ACCESS /////////////////////////\n";

	cout << "\n*************** TEST ra CONTENT ***************\n";
	cout << "Input: ra\n";
	PrintArray2D(ra);

	// [][]
	cout << "\n--------------- TEST [][] ---------------\n";
	cout << "\n*************** TEST [][] ON EXISTING INDEX ***************\n";
	cout << "Input: ra[1][2]\nOutput:\n";
	cout << ra[1][2] << endl;

	cout << "\n*************** TEST [][] ON NEGATIVE ROW ***************\n";
	cout << "Input: ra[-1][2]\nOutput:\n";
	try	{
		cout << ra[-1][2] << endl;
	}
	catch (const Exception & exc)	{
		cout << exc << endl;
	}

	cout << "\n*************** TEST [][] ON LARGE ROW ***************\n";
	cout << "Input: ra[234][2]\nOutput:\n";
	try	{
		cout << ra[234][2] << endl;
	}
	catch (const Exception & exc)	{
		cout << exc << endl;
	}

	cout << "\n*************** TEST [][] ON NEGATIVE COLUMN ***************\n";
	cout << "Input: ra[1][-2]\nOutput:\n";
	try	{
		cout << ra[1][-2] << endl;
	}
	catch (const Exception & exc)	{
		cout << exc << endl;
	}

	cout << "\n*************** TEST [][] ON LARGE COLUMN ***************\n";
	cout << "Input: ra[3][52]\nOutput:\n";
	try	{
		cout << ra[3][52] << endl;
	}
	catch (const Exception & exc)	{
		cout << exc << endl;
	}

	cout << "\n*************** TEST [][] ON BOUNDARY ***************\n";
	cout << "Input: ra[0][0]\nOutput:\n";
	cout << ra[0][0] << endl;

	cout << "\nInput: ra[4][4]\nOutput:\n";
	cout << ra[4][4] << endl;

	// SELECT()
	cout << "\n--------------- TEST SELECT() ---------------\n";
	cout << "\n*************** TEST SELECT() ON EXISTING INDEX ***************\n";
	cout << "Input: ra.Select(1, 2)\nOutput:\n";
	cout << ra.Select(1, 2) << endl;

	cout << "\n*************** TEST SELECT() ON NEGATIVE ROW ***************\n";
	cout << "Input: ra.Select(-1, 2)\nOutput:\n";
	try	{
		cout << ra.Select(-1, 2) << endl;
	}
	catch (const Exception & exc)	{
		cout << exc << endl;
	}

	cout << "\n*************** TEST SELECT() ON LARGE ROW ***************\n";
	cout << "Input: ra.Select(234, 2)\nOutput:\n";
	try	{
		cout << ra.Select(234, 2) << endl;
	}
	catch (const Exception & exc)	{
		cout << exc << endl;
	}

	cout << "\n*************** TEST SELECT() ON NEGATIVE COLUMN ***************\n";
	cout << "Input: ra.Select(1, -2)\nOutput:\n";
	try	{
		cout << ra.Select(1, -2) << endl;
	}
	catch (const Exception & exc)	{
		cout << exc << endl;
	}

	cout << "\n*************** TEST SELECT() ON LARGE COLUMN ***************\n";
	cout << "Input: ra.Select(3, 52)\nOutput:\n";
	try	{
		cout << ra.Select(3, 52) << endl;
	}
	catch (const Exception & exc)	{
		cout << exc << endl;
	}
}


void TestDataModification(Array2D<ComplexData> & ra)
{
	cout << "\n\n\n--------------------------------------------------------------------------";
	cout << "\n\n\n///////////////////////// TEST DATA MODIFICATION /////////////////////////\n";

	cout << "\n*************** TEST ra CONTENT ***************\n";
	cout << "Input: ra\n";
	PrintArray2D(ra);

	cout << "\n--------------- MAKING COPY ra2 ---------------\n";
	Array2D<ComplexData> ra2(ra);

	cout << "\n--------------- TEST CHANGE COPY ARRAY DATA ---------------\n";
	cout << "\n*************** TEST SET WITH [][] ***************\n";
	cout << "Input: ra2[2][1] = ComplexData(\".\")\n";
	ra2[2][1] = ComplexData(".");
	PrintArray2D(ra2);

	cout << "\n*************** TEST SET WITH SELECT() ***************\n";
	cout << "Input: ra2.Select(0, 0) = ComplexData(\"!\")\n";
	ra2.Select(0, 0) = ComplexData("!");
	PrintArray2D(ra2);


	cout << "\n--------------- TEST RESIZE COPY ARRAY ---------------\n";
	cout << "\n*************** TEST SET ROWS LARGER ***************\n";
	cout << "Input: ra2.setRow(8)\n";
	ra2.setRow(8);
	PrintArray2D(ra2);

	cout << "\n*************** TEST SET ROWS SMALLER ***************\n";
	cout << "Input: ra2.setRow(3)\n";
	ra2.setRow(3);
	PrintArray2D(ra2);

	cout << "\n*************** TEST SET COLUMNS LARGER ***************\n";
	cout << "Input: ra2.setColumn(8)\n";
	ra2.setColumn(8);
	PrintArray2D(ra2);

	cout << "\n*************** TEST SET COLUMNS SMALLER ***************\n";
	cout << "Input: ra2.setColumn(3)\n";
	ra2.setColumn(3);
	PrintArray2D(ra2);

	cout << "\n*************** TEST SET SIZE ON COPY ***************\n";
	cout << "Input: ra2.setSize(7, 10)\n";
	ra2.setSize(7, 10);
	PrintArray2D(ra2);


	cout << "\n*************** TEST INTEGRITY OF ra ***************\n";
	cout << "Input: ra\n";
	PrintArray2D(ra);

	cout << "\n*************** TEST SET SIZE ON ra ***************\n";
	cout << "Input: ra.setSize(7, 10)\n";
	ra.setSize(7, 10);
	PrintArray2D(ra);

	// UNCOMMENT TO OBSERVE CONSTNESS
	//const Array2D<ComplexData> ra3(ra);
	//ra3[1][1] = ComplexData("%");

}


void TestMisc(Array2D<ComplexData> & ra)
{
	cout << "\n\n\n--------------------------------------------------------------------------";
	cout << "\n\n\n///////////////////////// TEST MISC FUNCTIONS /////////////////////////\n";

	cout << "\n*************** TEST GETTERS ***************\n";
	cout << "Input: ra.getRow()\nOutput:\n";
	cout << ra.getRow() << endl;

	cout << "\nInput: ra.getColumn()\nOutput:\n";
	cout << ra.getColumn() << endl;


	cout << "\n*************** TEST CONTAINS() ON VALID POINT ***************\n";
	cout << "Input: ra.Contains(2, 4)\nOutput:\n";
	cout << ((ra.Contains(2, 4)) ? "True" : "False") << endl;

	cout << "\n*************** TEST CONTAINS() ON INVALID POINT ***************\n";
	cout << "Input: ra.Contains(12, 116)\nOutput:\n";
	cout << ((ra.Contains(12, 116)) ? "True" : "False") << endl;

}


void PrintArray2D(const Array2D<ComplexData> & ra)
{
	cout << "Output:\n\n";
	if (ra.getRow() == 0 || ra.getColumn() == 0)
		cout << "Array2D is empty..." << endl;
	else
	{
		cout << "   ";
		for (int i = 0; i < ra.getColumn(); ++i)
			cout << i << " ";

		cout << "\n" << endl;

		for (int i = 0; i < ra.getRow(); ++i)
		{
			cout << i << "  ";
			for (int j = 0; j < ra.getColumn(); ++j)
				cout << ra[i][j] << ' ';

			cout << endl;
		}
	}
}

