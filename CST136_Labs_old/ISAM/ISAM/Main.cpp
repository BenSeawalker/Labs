/*
	@Author: Garrett Fleischer
	@Date:	 10/18/15
*/


#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include "Employee.h"
#include "LinkedList.h"
#include "ISAM.h"

void InitializeEmployeeISAM(const string & _inputFile, const string & _outputFile);

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	// Initialize the ISAM with data from "Input.txt"
	InitializeEmployeeISAM("Input.txt", "Output.txt");

	return 0;
}

void InitializeEmployeeISAM(const string &  _inputFile, const string &  _outputFile)
{
	ifstream employees(_inputFile);

	if (employees.is_open())
	{
		stringstream output;

		// Create the ISAM designed to handle Employees
		ISAM<Employee> * isam = new ISAM<Employee>(employees, &output, &Employee::CompareEmployee, &Employee::CompareKey, &Employee::DisplayEmployee);

		// Print the ISAM's output to the console
		cout << output.str();

		// Suedo memory leak checker
		cout << Employee::InstanceCount << " Employee instances\n" << endl;

		cout << "Deleting ISAM...\n" << endl;
		delete isam;

		// Suedo memory leak checker
		cout << Employee::InstanceCount << " Employee instances\n" << endl;

		// Attempt to open the outputFile
		// and write the ISAM's output to the file
		ofstream outputFile(_outputFile);
		if(outputFile.is_open())
			outputFile << output.str();
	}
}