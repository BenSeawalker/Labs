#include "Office.h"



Office::Office(char _lName[10], int _salary)
	: Employee(_lName, 'O'), m_salary(_salary)
{}


Office::~Office()
{}

void Office::Print(ostream & _os) const
{
	Employee::Print(_os);
	_os << endl << "Paycheck: $" << m_salary;
}


ostream& operator<<(ostream & _os, Office & _this)
{
	_this.Print(_os);
	return _os;
}
