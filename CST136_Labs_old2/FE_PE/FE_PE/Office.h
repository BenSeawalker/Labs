#pragma once

#include "Employee.h"

class Office : public Employee
{
public:
	Office(char _lName[10], int _salary);
	virtual ~Office();

	virtual void Print(ostream & _os) const;

	friend ostream& operator<<(ostream & _os, Office & _this);

protected:
	int m_salary;
};

