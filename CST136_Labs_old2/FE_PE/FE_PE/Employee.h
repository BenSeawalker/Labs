#pragma once

#include <cstring>

#include <ostream>
using std::ostream;

#include <iostream>
using std::endl;

class Employee
{
public:
	virtual ~Employee();

	virtual void Print(ostream & _os) const;

	friend ostream& operator<<(ostream & _os, const Employee & _this);

	bool operator<(const Employee & _other);

protected:
	char m_lName[10];
	char m_code;

	Employee(char _lName[10], char _code);

};