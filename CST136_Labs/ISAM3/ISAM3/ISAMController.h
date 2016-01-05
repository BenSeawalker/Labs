
#ifndef ISAMController_h__
#define ISAMController_h__


#include <sstream>
using std::stringstream;

#include <fstream>
using std::ifstream;
using std::ofstream;

#include <iostream>
using std::ios;

#include <iomanip>
using std::setiosflags;
using std::setprecision;

#include <string>
using std::string;

#include "ISAM.h"
class Employee;

#include "GenericIterator.h"
#include "SkipIterator.h"
#include "RangeIterator.h"


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
class ISAMController
{
public:
	typedef const string & String;
	
	ISAMController(String _filename = "Input.txt");
	~ISAMController();

private:
	// MEMBER CONSTANTS
	static stringstream m_output;

	static const int NUM_ITERATORS = 4;
	enum ITYPE { G, S, A, M, NONE };

	// MEMBER VARIABLES
	ISAM<Employee, string> * m_ISAM;
	
	ISAMIterator<Employee, string> * m_iterators[NUM_ITERATORS];


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
	void MoveIterator(stringstream & _arguments);
	void FirstIterator(stringstream & _arguments);
	void GetIterator(stringstream & _arguments);

	ITYPE GetITYPE(char _type);
};

#endif // ISAMController_h__

