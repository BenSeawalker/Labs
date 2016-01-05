#include "Salary.h"


/////////////////////////////////////////////////////////
//	C'tor and D'tor
//////////

	Salary::Salary()
	{}

	Salary::Salary(const string & _worknum, const string & _last, const string & _first,
					const string & _bdate, const string & _employed, int _sales, float _commision, stringstream * _output)
		: Employee(_worknum, _last, _first, _bdate, _employed, _output), m_sales(_sales), m_commission(_commision)
	{
	}

	Employee * Salary::Copy()
	{
		return new Salary(*this);
	}

	Salary::Salary(const Salary & _temp)
		: Employee(_temp), m_sales(_temp.m_sales), m_commission(_temp.m_commission)
	{}

	Salary::~Salary()
	{}

//////////
// END C'tor and D'tor
/////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////
//	PUBLIC METHODS
//////////

	void Salary::Display() const
	{
		Employee::Display();
		*(Output()) << setw(9) << "Sales: " << setw(10) << right << m_sales << setw(13) << left << "\tCommission: " << setw(8) << right << m_commission << left <<  endl; // setw(10) = in case employee is in the 6 digit range...
	}

	float Salary::CalculatePaycheck() const
	{
		return (m_sales * m_commission);
	}

//////////
// END PUBLIC METHODS
/////////////////////////////////////////////////////////