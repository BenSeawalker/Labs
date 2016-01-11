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

void TestSetRows(Array2D<Exception> & ra, int rows);

void PrintArray2D(const Array2D<Exception> & ra);


int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	
	try
	{

		Array2D<Exception> ra(5, 5);

		for (int i = 0; i < ra.getRows(); ++i)
			for (int j = 0; j < ra.getColumns(); ++j)
			{
				char c[2];
				c[0] = 'A' + j;
				c[1] = '\0';
				ra[i][j] = Exception(c);
			}

		ra.setSize(8, 8);
		PrintArray2D(ra);

		ra.setSize(3, 3);
		PrintArray2D(ra);

		ra.setSize(5, 5);
		PrintArray2D(ra);

		/*PrintArray2D(ra);
		ra.setColumns(8);
		PrintArray2D(ra);
		ra.setColumns(1);
		PrintArray2D(ra);
		ra.setColumns(5);
		PrintArray2D(ra);

		cout << "\nROWS\n" << endl;
		ra.setRows(8);
		PrintArray2D(ra);
		ra.setRows(1);
		PrintArray2D(ra);
		ra.setRows(5);
		PrintArray2D(ra);*/
	}
	catch (const Exception & e)
	{
		cout << '\n' << e << '\n' << endl;
	}

	
	system("pause");
	return 0;
}


void TestSetRows(Array2D<Exception> & ra, int rows)
{
	ra.setRows(rows);
}



void PrintArray2D(const Array2D<Exception> & ra)
{
	for (int i = 0; i < ra.getRows(); ++i)
	{
		for (int j = 0; j < ra.getColumns(); ++j)
			cout << ra[i][j];

		cout << endl;
	}

	cout << "\nDONE!\n" << endl;
}

