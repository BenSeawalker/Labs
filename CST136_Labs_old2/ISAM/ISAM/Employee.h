/*
@Author: Garrett Fleischer
@Date:	 10/18/15
*/

#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <string>
using std::string;

#include <sstream>
using std::stringstream;

#include <iostream>
using std::cout;
using std::endl;

#include <ios>
using std::ofstream;

#include <iomanip>
using std::setw;
using std::left;



class Employee
{
public:
	static int InstanceCount;

	Employee();
	Employee(const Employee & _copy);
	Employee(const string & _lastName, stringstream * _outptut);
	Employee(const Employee & _emp, stringstream * _outptut);
	Employee(stringstream & _data, stringstream * _outptut);
	
	~Employee();


	const string & WorkNumber() const { return m_workNum; }
	const string & LastName() const { return m_lastName; }
	const string & FirstName() const { return m_firstName; }
	const string & BirthDate() const { return m_bdate; }
	const string & Employed() const { return m_employed; }


	void Display() const;

	static void DisplayEmployee(const Employee * _emp);

	static int CompareEmployee(const Employee * _e1, const Employee * _e2);
	static bool CompareKey(const Employee * _emp, const string & _key);

private:
	string	m_workNum;
	string	m_lastName;
	string	m_firstName;
	string	m_bdate;
	string	m_employed;

	stringstream * m_output;
};

#endif