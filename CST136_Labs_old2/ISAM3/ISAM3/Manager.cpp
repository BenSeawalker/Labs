#include "Manager.h"


/////////////////////////////////////////////////////////
//	C'tor and D'tor
//////////

	Manager::Manager(const string & _worknum, const string & _last, const string & _first,
						const string & _bdate, const string & _employed, float _salary, float _bonus, stringstream * _output)
		: Employee(_worknum, _last, _first, _bdate, _employed, _output), m_salary(_salary), m_bonus(_bonus)
	{}

	Manager::Manager(const Manager & _temp)
		: Employee(_temp), m_bonus(_temp.m_bonus), m_salary(_temp.m_salary)
	{}

	Manager::~Manager()
	{}

//////////
// END C'tor and D'tor
/////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////
//	PUBLIC METHODS
//////////

	void Manager::Display() const
	{
		Employee::Display();
		*(Output()) << setw(9) << "Salary: " << setw(10) << right << m_salary << setw(13) << left << "\tBonus: " << setw(8) << right << m_bonus << left << endl; // setw(10) = in case employee is in the 6 digit range...
	}

	float Manager::CalculatePaycheck() const
	{
		return (m_salary + m_bonus);
	}

//////////
// END PUBLIC METHODS
/////////////////////////////////////////////////////////