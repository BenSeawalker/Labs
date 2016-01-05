#include "EmployeeManager.h"

#include "Salary.h"
#include "Temporary.h"
#include "Manager.h"

// INITIALIZE STATIC VARIABLE
stringstream * EmployeeManager::m_output = new stringstream;

///////////////////////////////////////////////////////////////////////
//	C'tor and D'tor
//////

	/**********************************************************************
	* Purpose: This C'tor sets up m_output to display monetary values
	*			and calls ProcessFile();
	************************************************************************/
	EmployeeManager::EmployeeManager(String _filename)
{
		*m_output << setiosflags(ios::fixed | ios::showpoint) << setprecision(2); // Setup m_output to display monetary values

		m_ISAM = new ISAM<Employee>(&Employee::CompareEmployee, &Employee::CompareKey, m_output);
	
		ProcessFile(_filename);
	}


	EmployeeManager::~EmployeeManager()
	{
		delete m_output;
		delete m_ISAM;
	}
	
//////
// END C'tor and D'tor
///////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////
//	PRIVATE STATIC METHODS
//////

	void EmployeeManager::DisplayType(Employee * _emp)
	{
		// SALARY
		if (dynamic_cast<Salary *>(_emp))
			*m_output << setw(12) << _emp->LastName() << " is a Salary      employee" << endl;

		// TEMPORARY
		else if (dynamic_cast<Temporary *>(_emp))
			*m_output << setw(12) << _emp->LastName() << " is a Temporary   employee" << endl;

		// MANAGER
		else if (dynamic_cast<Manager *>(_emp))
			*m_output << setw(12) << _emp->LastName() << " is a Managerial  employee" << endl;
	}

//////
// END PRIVATE STATIC METHODS
///////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////
//	PRIVATE METHODS
//////

	/**********************************************************************
	* Purpose: This opens a given file and reads each line separating "Commands" from "Arguments"
	*			and passes them to ProcessCommand().
	*
	* Precondition:
	*     _filename = the name of the file to be opened
	*
	* Postcondition:
	*		Returns N/A
	*		Overwrites the file: "\ISAM2\Output.txt"
	*
	************************************************************************/
	void EmployeeManager::ProcessFile(String _filename)
	{
		bool program_running = true;

		ifstream inputFile(_filename);

		if (inputFile.is_open())
		{
			while (!inputFile.eof() && program_running)
			{
				char command[2];
				string arguments;

				inputFile.read(command, 2);		// read in the command (and space)
				getline(inputFile, arguments);	// read in the arguments

				program_running = ProcessCommand(command[0], stringstream(arguments));
			}

			inputFile.close();
		}
		else
			*m_output << "Unable to open \"" << _filename << "\" !" << endl;


		
		cout << m_output->str();			// Print program output to the console

		
		ofstream outputFile("Output.txt");	// Save program output to a File
		if (outputFile.is_open())
		{
			outputFile << m_output->str();
			outputFile.close();
		}
	}


	/**********************************************************************
	* Purpose: This function processes the command by calling the appropriate method.
	*
	* Precondition:
	*     _command		=	single character command
	*	  _arguments	=	list of arguments associated with the command
	*
	* Postcondition:
	*      Returns true if the [E]xit command is processed.
	*
	************************************************************************/
	bool EmployeeManager::ProcessCommand(char _command, stringstream & _arguments)
	{
		bool running = true;

		// COMMAND 'I'
		if (_command == 'I')
			Insert(_arguments);

		// COMMAND 'D'
		else if (_command == 'D')
			Delete(_arguments);

		// COMMAND 'S'
		else if (_command == 'S')
			Search(_arguments);

		// COMMAND 'R'
		else if (_command == 'R')
			DisplayRows(_arguments);

		// COMMAND '$'
		else if (_command == '$')
			DisplayWages(_arguments);

		// COMMAND 'C'
		else if (_command == 'C')
			DisplayTypes(_arguments);

		// COMMAND 'E'
		else if (_command == 'E')
		{
			*m_output << endl << "Program ending...\n" << endl;
			running = false;
		}

		// COMMAND ???
		else
		{
			*m_output << "\nInvalid Command: \"" << _command << "\"!\n" << endl;
		}

		return running;
	}



	/**********************************************************************
	* Purpose: This function Inserts an Employee into m_ISAM.
	*
	* Precondition:
	*     _arguments = work# last first birth employdate (S,T,M) ... ...
	*
	* Postcondition:
	*      Returns N/A.
	*      Modifies m_ISAM.
	*
	************************************************************************/
	void EmployeeManager::Insert(stringstream & _arguments)
	{
		*m_output << "Inserting: " << _arguments.str() << endl;

		string worknum, last, first, bdate, employed;
		char employee_type;
		float pay1, pay2;

		_arguments >> worknum >> last >> first >> bdate >> employed // EMPLOYEE DATA
			>> employee_type >> pay1 >> pay2;						// UNIQUE DATA

		switch (employee_type)
		{
		case 'S':
			m_ISAM->Insert(new Salary(worknum, last, first, bdate, employed, int(pay1), pay2, m_output));
			break;

		case 'T':
			m_ISAM->Insert(new Temporary(worknum, last, first, bdate, employed, pay1, pay2, m_output));
			break;

		case 'M':
			m_ISAM->Insert(new Manager(worknum, last, first, bdate, employed, pay1, pay2, m_output));
			break;

		default:
			break;
		}
	}


	/**********************************************************************
	* Purpose: This function searches for and Deletes an
	*			Employee from m_ISAM.
	*
	* Precondition:
	*     _arguments = last
	*
	* Postcondition:
	*      Returns N/A.
	*      Modifies m_ISAM.
	*
	************************************************************************/
	void EmployeeManager::Delete(stringstream & _arguments)
	{
		*m_output << endl << "Deleting: \"" << _arguments.str() << "\"" << endl;

		if (m_ISAM->Delete(_arguments.str()))
			*m_output << "Success!" << endl;
		else
			*m_output << "Failure!" << endl;
	}


	/**********************************************************************
	* Purpose: This function Searches for and Displays an Employee in m_ISAM.
	*
	* Precondition:
	*     _arguments = last
	*
	* Postcondition:
	*      Returns N/A.
	*
	************************************************************************/
	void EmployeeManager::Search(stringstream & _arguments)
	{
		*m_output << endl << "Searching for: \"" << _arguments.str() << "\"" << endl;

		FoundItem<Employee> * FI = m_ISAM->Find(_arguments.str());

		if (FI->item)
		{
			*m_output << "Found at: Element " << FI->column << " of Row " << FI->row << endl;
			FI->item->Display();
		}
		else
			*m_output << "Unable to find \"" << _arguments.str() << "\"..." << endl;

		*m_output << endl;

		delete FI;
	}


	/**********************************************************************
	* Purpose: This function Displays all Employees between the
	*			two rows specified.
	*
	* Precondition:
	*     _arguments = start_row end_row
	*
	* Postcondition:
	*      Returns N/A.
	*
	************************************************************************/
	void EmployeeManager::DisplayRows(stringstream & _arguments)
	{
		int start = 0;
		int end = 0;
		_arguments >> start >> end;

		if (start == end)
			*m_output << endl << "===================Displaying Row: " << start << "===================";
		else
			*m_output << endl << "=============Displaying Rows: " << start << " through " << end << "==============";

		m_ISAM->Traverse(start, end, &Employee::DisplayEmployee);

		*m_output << "=======================================================" << endl;
	}


	/**********************************************************************
	* Purpose: This function Displays the Wages of all Employees between the
	*			two rows specified.
	*
	* Precondition:
	*     _arguments = start_row end_row
	*
	* Postcondition:
	*      Returns N/A.
	*
	************************************************************************/
	void EmployeeManager::DisplayWages(stringstream & _arguments)
	{
		int start = 0;
		int end = 0;
		_arguments >> start >> end;

		if (start == end)
			*m_output << endl << "=================Paychecks for Row: " << start << "==================";
		else
			*m_output << endl << "===========Paychecks for Rows: " << start << " through " << end << "=============";

		m_ISAM->Traverse(start, end, &Employee::PrintPaycheck);

		*m_output << "=======================================================" << endl;
	}


	/**********************************************************************
	* Purpose: This function Displays the Types of all Employees in the
	*			specified row.
	*
	* Precondition:
	*     _arguments = row
	*
	* Postcondition:
	*      Returns N/A.
	*
	************************************************************************/
	void EmployeeManager::DisplayTypes(stringstream & _arguments)
	{
		int index = 0;
		_arguments >> index;

		*m_output << endl << "===============Employee Types in Row: " << index << "================";

		m_ISAM->Traverse(index, index, &DisplayType);

		*m_output << "=======================================================" << endl;
	}

//////
// END PRIVATE METHODS
///////////////////////////////////////////////////////////////////////