/*
@Author: Garrett Fleischer
@Date:	 10/18/15
*/

#include "Employee.h"


/////////////////////////////////////////////////////////
//	C'tor and D'tor
//////////

	Employee::Employee()
		: m_output(nullptr)
	{}

	Employee::Employee(const string & _worknum, const string & _last, const string & _first, const string & _bdate, const string & _employed, stringstream * _output)
		: m_workNum(_worknum), m_lastName(_last), m_firstName(_first), m_bdate(_bdate), m_employed(_employed), m_output(_output)
	{}

	Employee::~Employee()
	{}

//////////
// END C'tor and D'tor
/////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////
//	PUBLIC METHODS
//////////

	/**********************************************************************
	* Purpose: This virtual function displays Employee data to m_output
	*
	* Precondition:
	*		m_output cannot be null
	*
	* Postcondition:
	*		Returns N/A
	*		Modifies m_output
	*
	************************************************************************/
	void Employee::Display() const
	{
		if (m_output)
		{
			*m_output << left << setw(8) << m_workNum << setw(15) << m_lastName
				<< setw(15) << m_firstName << setw(10) << m_bdate << setw(10) << m_employed;
		}
	}


	/**********************************************************************
	* Purpose: This virtual function calls CalculatePaycheck on the given Employee
				and Displays it to m_output
	*
	* Precondition:
	*		m_output should not be null
	*
	* Postcondition:
	*		Returns N/A
	*		Modifies m_output
	*
	************************************************************************/
	void Employee::PrintPaycheck(Employee * _emp)
	{
		*(_emp->m_output) << setw(15) << left << _emp->m_lastName << setw(10) << right << _emp->CalculatePaycheck() << left << endl;
	}


	/**********************************************************************
	* Purpose: This static function attempts to call _emp->Display()
	*			it can be passed as a function pointer to LinkedList::Traverse()
	*
	* Precondition:
	*		_emp should not be null
	*
	* Postcondition:
	*		Returns N/A
	*
	************************************************************************/
	void Employee::DisplayEmployee(Employee * _emp)
	{
		if(_emp)
			_emp->Display();
	}


	/**********************************************************************
	* Purpose: This static function compares the last names of two Employees
	*			it can be passed as a function pointer to a LinkedList<Employee>
	*
	* Precondition:
	*		_e1 and _e2 should not be null
	*
	* Postcondition:
	*		Returns the difference between the two last names
	*
	************************************************************************/
	int Employee::CompareEmployee(const Employee * _e1, const Employee * _e2)
	{
		int diff = 0;

		if (_e1 && _e2)
			diff = _e1->m_lastName.compare(_e2->m_lastName);

		return diff;
	}


	/**********************************************************************
	* Purpose: This static function compares an Employee's last name with a given key
	*			it can be passed as a function pointer to a LinkedList<Employee>
	*
	* Precondition:
	*		_emp should not be null
	*
	* Postcondition:
	*		Returns the difference between the key and the Employee's last name
	*
	************************************************************************/
	int Employee::CompareKey(const Employee * _emp, const string & _key)
	{
		int diff = -1;

		if (_emp)
			diff = _key.compare(_emp->m_lastName);

		return diff;
	}

//////////
// END PUBLIC METHODS
/////////////////////////////////////////////////////////