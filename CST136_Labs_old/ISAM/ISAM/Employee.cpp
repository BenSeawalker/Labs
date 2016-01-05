/*
@Author: Garrett Fleischer
@Date:	 10/18/15
*/

#include "Employee.h"


#define npos string::npos

int Employee::InstanceCount = 0;


Employee::Employee()
	: m_output(nullptr)
{
	++InstanceCount;
}

Employee::Employee(const Employee & _copy)
	: m_bdate(_copy.m_bdate), m_lastName(_copy.m_lastName), m_firstName(_copy.m_firstName),
	m_workNum(_copy.m_workNum), m_employed(_copy.m_employed), m_output(_copy.m_output)
{
	++InstanceCount;
}

Employee::Employee(const string & _lastName, stringstream * _outptut)
	: m_lastName(_lastName), m_output(_outptut)
{
	++InstanceCount;
}

Employee::Employee(const Employee & _emp, stringstream * _outptut)
	: m_output(_outptut)
{
	++InstanceCount;
	*this = _emp;
}

Employee::Employee(stringstream & _data, stringstream * _outptut)
	: m_output(_outptut)
{
	++InstanceCount;
	_data >> m_workNum >> m_lastName >> m_firstName >> m_bdate >> m_employed;
}


Employee::~Employee()
{
	--InstanceCount;
}

void Employee::Display() const
{
	if (m_output)
	{
		*m_output << left << setw(8) << m_workNum << setw(12) << m_lastName
			<< setw(12) << m_firstName << setw(10) << m_bdate << setw(10) << m_employed << endl;
	}
}

void Employee::DisplayEmployee(const Employee * _emp)
{
	if(_emp)
		_emp->Display();
}


int Employee::CompareEmployee(const Employee * _e1, const Employee * _e2)
{
	int diff = 0;

	if (_e1 && _e2)
		diff = _e1->m_lastName.compare(_e2->m_lastName);

	return diff;
}

bool Employee::CompareKey(const Employee * _emp, const string & _key)
{
	int diff = -1;

	if (_emp)
		diff = _emp->m_lastName.compare(_key);

	return (diff == 0);
}

