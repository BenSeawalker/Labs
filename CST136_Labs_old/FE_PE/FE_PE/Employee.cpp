#include "Employee.h"

Employee::Employee(char _lName[10], char _code)
	: m_code(_code)
{
	strcpy(m_lName, _lName);
}

Employee::~Employee()
{}

ostream& operator<<(ostream & _os, const Employee & _this)
{
	_this.Print(_os);
	return _os;
}


void Employee::Print(ostream & _os) const
{
	_os << m_lName << " : " << m_code;
}

bool Employee::operator<(const Employee & _other)
{
	return (stricmp(m_lName, _other.m_lName) < 0);
}
//
//ostream & operator<<(ostream & _os, const Employee & _this)
//{
//	_os << _this.m_lName << " : " << _this.m_code << endl;
//	return _os;
//}

