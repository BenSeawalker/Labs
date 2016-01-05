#ifndef Manager_h__
#define Manager_h__

#include "Employee.h"


/************************************************************************
* Class: Manager
*
* Purpose: This class stores data for a Temporary Employee
*
* Manager functions:
* 	Manager(const string & _worknum, const string & _last, const string & _first, const string & _bdate,
*						const string & _employed, float _salary, float _bonus, stringstream * _output);
*		_output = stringstream to print all data to
*
*	~Manager()
*
* Methods:
*	Public:
*		Display()			: virtual
*		CalculatePaycheck()	: virtual
*	Private:
*		N/A
*
*************************************************************************/
class Manager :	public Employee
{
public:
	Manager(const string & _worknum, const string & _last, const string & _first,
				const string & _bdate, const string & _employed, float _salary, float _bonus, stringstream * _output);

	virtual Employee * Copy();
	Manager(const Manager & _temp);

	virtual ~Manager();


	virtual void Display() const;
	virtual float CalculatePaycheck() const;

private:
	float m_salary;
	float m_bonus;
};


#endif // Manager_h__