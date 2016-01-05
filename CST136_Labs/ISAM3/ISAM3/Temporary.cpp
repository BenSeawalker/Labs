#include "Temporary.h"



/////////////////////////////////////////////////////////
//	C'tor and D'tor
//////////

	Temporary::Temporary(const string & _worknum, const string & _last, const string & _first,
							const string & _bdate, const string & _employed, float _rate, float _hours, stringstream * _output)
		: Employee(_worknum, _last, _first, _bdate, _employed, _output), m_rate(_rate), m_hours(_hours)
	{}

	Temporary::Temporary(const Temporary & _temp)
		: Employee(_temp), m_hours(_temp.m_hours), m_rate(_temp.m_rate)
	{}

	Temporary::~Temporary()
	{}

//////////
// END C'tor and D'tor
/////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////
//	PUBLIC METHODS
//////////

	void Temporary::Display() const
	{
		Employee::Display();
		*(Output()) << setw(9) << "Rate: " << setw(10) << right << m_rate << setw(13) << left << "\tHours: " << setw(8) << right << m_hours << left << endl;
	}

	float Temporary::CalculatePaycheck() const
	{
		return (m_hours * m_rate);
	}

//////////
// END PUBLIC METHODS
/////////////////////////////////////////////////////////