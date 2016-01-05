
#ifndef EmployeeManager_h__
#define EmployeeManager_h__

#include "ISAM.h"

#include <sstream>
using std::stringstream;

#include <iostream>
using std::ifstream;
using std::ofstream;

#include <iomanip>
using std::setiosflags;
using std::setprecision;


#include "ISAM.h"
class Employee;



/************************************************************************
* Class: EmployeeManager
*
* Purpose: This class creates an ISAM matrix of Employees and modifies it
*			with commands from a file.
*
* Manager functions:
* 	EmployeeManager (const string & _filename )
* 		The default filename is "Input.txt".
*	~EmployeeManager()
*
* Methods:
*	Public:
*		N/A
*	Private:
*		ProcessFile(String _filename);
*		ProcessCommand(char _command, stringstream & _arguments);
*
*		Insert(stringstream & _arguments);
*		Delete(stringstream & _arguments);
*		Search(stringstream & _arguments);
*		DisplayRows(stringstream & _arguments);
*		DisplayWages(stringstream & _arguments);
*		DisplayType(stringstream & _arguments);
*************************************************************************/
class EmployeeManager
{
public:
	typedef const string & String;
	
	EmployeeManager(String _filename = "Input.txt");
	~EmployeeManager();

private:
	// MEMBER VARIABLES
	ISAM<Employee> * m_ISAM;
	static stringstream * m_output;

	// STATIC MEMBER FUNCTIONS
	static void DisplayType(Employee * _emp);

	// MEMBER FUNCTIONS
	void ProcessFile(String _filename);

	bool ProcessCommand(char _command, stringstream & _arguments);

	void Insert(stringstream & _arguments);
	void Delete(stringstream & _arguments);
	void Search(stringstream & _arguments);
	void DisplayRows(stringstream & _arguments);
	void DisplayWages(stringstream & _arguments);
	void DisplayTypes(stringstream & _arguments);
};

#endif // EmployeeManager_h__

