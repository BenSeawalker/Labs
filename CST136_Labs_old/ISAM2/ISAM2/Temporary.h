
#ifndef Temporary_h__
#define Temporary_h__

#include "Employee.h"


/************************************************************************
* Class: Temporary
*
* Purpose: This class stores data for a Temporary Employee
*
* Manager functions:
* 	Temporary(const string & _worknum, const string & _last, const string & _first, const string & _bdate,
*						const string & _employed, float _rate, float _hours, stringstream * _output);
*		_output = stringstream to print all data to
*
*	~Temporary()
*
* Methods:
*	Public:
*		Display()			: virtual
*		CalculatePaycheck()	: virtual
*	Private:
*		N/A
*
*************************************************************************/
class Temporary : public Employee
{
public:
	Temporary(const string & _worknum, const string & _last, const string & _first,
				const string & _bdate, const string & _employed, float _rate, float _hours, stringstream * _output);
	
	virtual Employee * Copy();
	Temporary(const Temporary & _temp);

	virtual ~Temporary();


	virtual void Display() const;
	virtual float CalculatePaycheck() const;

private:
	float m_rate;
	float m_hours;
};

#endif // Temporary_h__

