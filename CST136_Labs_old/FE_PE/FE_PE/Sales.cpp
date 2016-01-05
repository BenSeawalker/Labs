#include "Sales.h"



Sales::Sales(char _lName[10], float _base, float _commission)
	: Employee(_lName, 'S'), m_base(_base), m_commission(_commission)
{}


Sales::~Sales()
{}


void Sales::Print(ostream & _os) const
{
	Employee::Print(_os);
	_os << endl << "Paycheck: $" << (m_base * m_commission);
}


ostream& operator<<(ostream & _os, Sales & _this)
{
	_this.Print(_os);
	return _os;
}