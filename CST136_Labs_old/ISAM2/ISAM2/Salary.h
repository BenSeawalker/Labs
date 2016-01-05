#ifndef Salary_h__
#define Salary_h__

#include "Employee.h"


/************************************************************************
* Class: Salary
*
* Purpose: This class stores data for a Salary Employee
*
* Manager functions:
* 	Salary(const string & _worknum, const string & _last, const string & _first, const string & _bdate,
*						const string & _employed, int _sales, float _commision, stringstream * _output);
*		_output = stringstream to print all data to
*
*	~Salary()
*
* Methods:
*	Public:
*		Display()			: virtual
*		CalculatePaycheck()	: virtual
*	Private:
*		N/A
*
*************************************************************************/
class Salary : public Employee
{
public:
	Salary();
	Salary(const string & _worknum, const string & _last, const string & _first, const string & _bdate, const string & _employed, int _sales, float _commision, stringstream * _output);

	virtual Employee * Copy();
	Salary(const Salary & _temp);

	virtual ~Salary();

	virtual void Display() const;
	virtual float CalculatePaycheck() const;

private:
	int m_sales;
	float m_commission;
};


#endif // Salary_h__