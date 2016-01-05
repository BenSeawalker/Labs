#include "ISAMController.h"

#include "Salary.h"
#include "Temporary.h"
#include "Manager.h"

// INITIALIZE STATIC VARIABLE
stringstream ISAMController::m_output = stringstream("");

///////////////////////////////////////////////////////////////////////
//	C'tor and D'tor
//////

	/**********************************************************************
	* Purpose: This C'tor sets up m_output to display monetary values
	*			and calls ProcessFile();
	************************************************************************/
	ISAMController::ISAMController(String _filename)
{
		m_output << setiosflags(ios::fixed | ios::showpoint) << setprecision(2); // Setup m_output to display monetary values

		m_ISAM = new ISAM<Employee, string>(&m_output);

		m_iterators[G] = new GenericIterator<Employee, string>(m_ISAM);
		m_iterators[S] = new SkipIterator<Employee, string>(m_ISAM);
		m_iterators[A] = new RangeIterator<Employee, string, char>(m_ISAM, 'A', 'L');
		m_iterators[M] = new RangeIterator<Employee, string, char>(m_ISAM, 'M', 'Z');
	
		ProcessFile(_filename);
	}


	ISAMController::~ISAMController()
	{
		delete m_ISAM;

		for (int i = 0; i < NUM_ITERATORS; ++i)
			delete m_iterators[i];
	}
	
//////
// END C'tor and D'tor
///////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////
//	PRIVATE STATIC METHODS
//////

	void ISAMController::DisplayType(Employee * _emp)
	{
		// SALARY
		if (dynamic_cast<Salary *>(_emp))
			m_output << setw(12) << _emp->LastName() << " is a Salary      employee" << endl;

		// TEMPORARY
		else if (dynamic_cast<Temporary *>(_emp))
			m_output << setw(12) << _emp->LastName() << " is a Temporary   employee" << endl;

		// MANAGER
		else if (dynamic_cast<Manager *>(_emp))
			m_output << setw(12) << _emp->LastName() << " is a Managerial  employee" << endl;
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
	void ISAMController::ProcessFile(String _filename)
	{
		bool program_running = true;

		ifstream inputFile(_filename);

		if (inputFile.is_open())
		{
			while (!inputFile.eof() && program_running)
			{
				char command;
				string line;

				getline(inputFile, line);	// read in the arguments
				command = line[0];

				if (line.length() > 1)
					line = line.substr(2, line.length());

				program_running = ProcessCommand(command, stringstream(line));
			}

			inputFile.close();
		}
		else
			m_output << "Unable to open \"" << _filename << "\" !" << endl;


		
		cout << m_output.str();			// Print program output to the console

		
		ofstream outputFile("Output.txt");	// Save program output to a File
		if (outputFile.is_open())
		{
			outputFile << m_output.str();
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
	bool ISAMController::ProcessCommand(char _command, stringstream & _arguments)
	{
		bool running = true;

		switch (_command)
		{
		case 'I':
			Insert(_arguments);
			break;

		case 'D':
			Delete(_arguments);
			break;

		case 'S':
			Search(_arguments);
			break;

		case 'R':
			DisplayRows(_arguments);
			break;

		case '$':
			DisplayWages(_arguments);
			break;

		case 'C':
			DisplayTypes(_arguments);
			break;

		case 'M':
			MoveIterator(_arguments);
			break;

		case 'F':
			FirstIterator(_arguments);
			break;

		case 'G':
			GetIterator(_arguments);
			break;

		case 'E':
			m_output << endl << "Program ending...\n" << endl;
			running = false;
			break;

		default:
			m_output << "\nInvalid Command: \"" << _command << "\"!\n" << endl;
			break;
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
	void ISAMController::Insert(stringstream & _arguments)
	{
		m_output << "Inserting: " << _arguments.str() << endl;

		string worknum, last, first, bdate, employed;
		char employee_type;
		float pay1, pay2;

		_arguments >> worknum >> last >> first >> bdate >> employed // EMPLOYEE DATA
			>> employee_type >> pay1 >> pay2;						// UNIQUE DATA

		switch (employee_type)
		{
		case 'S':
			m_ISAM->Insert(new Salary(worknum, last, first, bdate, employed, (int)pay1, pay2, &m_output));
			break;

		case 'T':
			m_ISAM->Insert(new Temporary(worknum, last, first, bdate, employed, pay1, pay2, &m_output));
			break;

		case 'M':
			m_ISAM->Insert(new Manager(worknum, last, first, bdate, employed, pay1, pay2, &m_output));
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
	void ISAMController::Delete(stringstream & _arguments)
	{
		string lname = _arguments.str();
		m_output << endl << "Deleting: \"" << lname << "\"" << endl;

		for (int i = 0; i < NUM_ITERATORS; ++i)
		{
			if ((!m_iterators[i]->IsDone()) && (m_iterators[i]->GetCurrent()->LastName() == lname))
			{
				m_output << "Moving iterator \"" << ((i == G) ? 'G' : ((i == S) ? 'S' : ((i == A) ? 'A' : (i == M) ? 'M' : ' '))) << "\"... ";

				m_iterators[i]->MoveNext();

				if (m_iterators[i]->IsDone())
					m_output << "Done!";

				m_output << endl;
			}
		}

		if (m_ISAM->Delete(lname))
			m_output << "Success!" << endl;
		else
			m_output << "Failure!" << endl;
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
	void ISAMController::Search(stringstream & _arguments)
	{
		m_output << endl << "Searching for: \"" << _arguments.str() << "\"" << endl;

		int row, column;
		Employee * const found = m_ISAM->Find(_arguments.str(), row, column);

		if (found)
		{
			m_output << "Found at: Element " << column << " of Row " << row << endl;
			found->Display();
		}
		else
			m_output << "Unable to find \"" << _arguments.str() << "\"..." << endl;

		m_output << endl;
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
	void ISAMController::DisplayRows(stringstream & _arguments)
	{
		int start = 0;
		int end = 0;
		_arguments >> start >> end;

		if (start == end)
			m_output << endl << "===================Displaying Row: " << start << "===================";
		else
			m_output << endl << "=============Displaying Rows: " << start << " through " << end << "==============";

		m_ISAM->Traverse(start, end, &Employee::DisplayEmployee);

		m_output << "=======================================================" << endl;
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
	void ISAMController::DisplayWages(stringstream & _arguments)
	{
		int start = 0;
		int end = 0;
		_arguments >> start >> end;

		if (start == end)
			m_output << endl << "=================Paychecks for Row: " << start << "==================";
		else
			m_output << endl << "===========Paychecks for Rows: " << start << " through " << end << "=============";

		m_ISAM->Traverse(start, end, &Employee::PrintPaycheck);

		m_output << "=======================================================" << endl;
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
	void ISAMController::DisplayTypes(stringstream & _arguments)
	{
		int index = 0;
		_arguments >> index;

		m_output << endl << "===============Employee Types in Row: " << index << "================";

		m_ISAM->Traverse(index, index, &DisplayType);

		m_output << "=======================================================" << endl;
	}

	void ISAMController::MoveIterator(stringstream & _arguments)
	{
		char iterator;
		int spaces;
		_arguments >> iterator >> spaces;

		ITYPE type = GetITYPE(iterator);

		m_output << endl << "Moving iterator " << iterator << "'s cursor forward " << spaces << " spaces." << endl;

		if (type == NONE)
			m_output << "Invalid iterator type \"" << iterator << "\"" << endl;
		else
		{
			for (int s = 0; s < spaces; ++s)
				m_iterators[type]->MoveNext();
		}
	}

	void ISAMController::FirstIterator(stringstream & _arguments)
	{
		char iterator;
		_arguments >> iterator;

		ITYPE type = GetITYPE(iterator);

		m_output << endl << "Moving iterator " << iterator << "'s cursor to the first element" << endl;

		if (type == NONE)
			m_output << "Invalid iterator type \"" << iterator << "\"" << endl;
		else
			m_iterators[type]->First();
	}

	void ISAMController::GetIterator(stringstream & _arguments)
	{
		char iterator;
		_arguments >> iterator;

		ITYPE type = GetITYPE(iterator);

		m_output << endl << "=======Displaying current item for iterator \"" << iterator << "\"========" << endl;

		if (type == NONE)
			m_output << "Invalid iterator type \"" << iterator << "\"" << endl;
		else
		{
			if (!m_iterators[type]->IsDone())
				m_iterators[type]->GetCurrent()->Display();
			else
				m_output << "Done!" << endl;
		}

		m_output << "=======================================================" << endl;
	}

	ISAMController::ITYPE ISAMController::GetITYPE(char _type)
	{
		ITYPE type = NONE;
		if (_type == 'G')
			type = G;
		else if (_type == 'S')
			type = S;
		else if (_type == 'A')
			type = A;
		else if (_type == 'M')
			type = M;

		return type;
	}

//////
// END PRIVATE METHODS
///////////////////////////////////////////////////////////////////////