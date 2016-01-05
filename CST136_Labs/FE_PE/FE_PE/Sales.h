#pragma once
#include "Employee.h"
class Sales : public Employee
{
public:
	Sales(char _lName[10], float _base, float _commission);
	virtual ~Sales();

	virtual void Print(ostream & _os) const;

	friend ostream& operator<<(ostream & _os, Sales & _this);

protected:
	float m_base;
	float m_commission;
};

