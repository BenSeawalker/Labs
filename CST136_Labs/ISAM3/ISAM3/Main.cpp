/***********************************************************************
* AUTHOR		:	Garrett Fleischer
* ASSIGNMENT	:	ISAM Polymorphism
* FILENAME		:	Main.cpp
* DATE CREATED	:	10/28/15
*
* MODIFICATIONS:
*	N/A
*
* OVERVIEW:
*	This program will read in "Employee" data from a file
*	and store it in an ISAM Matrix of Employees
*	Further commands from the file can be used to
*	display certain Employee data or delete employees.
*
* INPUT:
*	The input will consist of commands from a file: "\ISAM2\Input.txt"
*
*	Acceptable commands are:
*		[I]nsert, [D]elete, Display [R]ows, [S]earch,
*		Display Wages [$], Display Type [C], [E]xit
*
*	Command Format:
*		I work# last first birth employdate S sales commission
*		I work# last first birth employdate T hourlyrate hours
*		I work# last first birth employdate M salary bonus
*		D last
*		R start_row, end_row
*		S last
*		$ start_row, end_row
*		C row
*		E
*
* OUTPUT:	
*	The output is printed to the console and
*	saved to a file: "\ISAM2\Output.txt" 
*	It will consist of "Echoed" commands and their corresponding output
*	such as Displaying Employee data,
*	or whether an Employee was successfully Deleted or not.
*
***********************************************************************/



#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include <iostream>
using std::cout;
using std::endl;

#include "ISAMController.h"

#include "GenericIterator.h"
#include "SkipIterator.h"
#include "RangeIterator.h"

void IntISAMTest();

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	//ISAMController IC;
	
	IntISAMTest();

	return 0;
}


void IntISAMTest()
{
	stringstream * output = new stringstream;
	ISAM<int, int> * isam = new ISAM<int, int>(output);

	isam->Insert(new int(1));
	isam->Insert(new int(9));
	isam->Insert(new int(5));
	isam->Insert(new int(3));
	isam->Insert(new int(0));
	isam->Insert(new int(7));
	isam->Insert(new int(11));
	isam->Insert(new int(2));
	isam->Insert(new int(4));
	isam->Insert(new int(6));
	isam->Insert(new int(8));
	isam->Insert(new int(10));

	for (GenericIterator<int, int> IT(isam); !IT.IsDone(); IT.MoveNext())
		cout << *(IT.GetCurrent()) << endl;

	cout << endl;

	for (SkipIterator<int, int> IT(isam); !IT.IsDone(); IT.MoveNext())
		cout << *(IT.GetCurrent()) << endl;

	cout << endl;

	for (RangeIterator<int, int, int> IT(isam, 0, 5); !IT.IsDone(); IT.MoveNext())
		cout << *(IT.GetCurrent()) << endl;

	cout << endl;

	for (RangeIterator<int, int, int> IT(isam, 6, 11); !IT.IsDone(); IT.MoveNext())
		cout << *(IT.GetCurrent()) << endl;

	cout << endl;

	delete isam;
	delete output;
}