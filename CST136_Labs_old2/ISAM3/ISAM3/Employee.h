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
using std::ios;

#include <iomanip>
using std::setw;
using std::left;
using std::right;



/************************************************************************
* Class: Employee
*
* Purpose: This class stores Employee data
*
* Manager functions:
* 	Employee(const string & _worknum, const string & _last, const string & _first,
*				const string & _bdate, const string & _employed, stringstream * _output)
*		_output = stringstream to print all data to
*
*	~Employee()
*
* Methods:
*	Public:
*		Display()												: virtual
*		CalculatePaycheck()										: pure virtual
*		DisplayEmployee(Employee *);							: static
*		PrintPaycheck(Employee *);								: static
*	Private:
*		N/A
*
*************************************************************************/
class Employee
{
public:
	virtual ~Employee();

public:
	//Getters
	const string & WorkNumber() const { return m_workNum; }
	const string & LastName() const { return m_lastName; }
	const string & FirstName() const { return m_firstName; }
	const string & BirthDate() const { return m_bdate; }
	const string & Employed() const { return m_employed; }
	stringstream * Output() const { return m_output; }


	// Public Member Functions
	virtual void Display() const;
	virtual float CalculatePaycheck() const = 0;

	static void DisplayEmployee(Employee * _emp);
	static void PrintPaycheck(Employee * _emp);

	operator char();

	bool operator==(const Employee & _emp) const;
	bool operator<=(const Employee & _emp) const;
	bool operator>=(const Employee & _emp) const;
	bool operator<(const Employee & _emp) const;
	bool operator>(const Employee & _emp) const;

	friend bool operator==(const Employee & _emp, const string & _key);
	friend bool operator!=(const Employee & _emp, const string & _key);
	friend bool operator<=(const Employee & _emp, const string & _key);
	friend bool operator>=(const Employee & _emp, const string & _key);
	friend bool operator<(const Employee & _emp, const string & _key);
	friend bool operator>(const Employee & _emp, const string & _key);

protected:
	Employee();
	Employee(const string & _worknum, const string & _last, const string & _first, const string & _bdate, const string & _employed, stringstream * _output);

protected:
	string	m_workNum;
	string	m_lastName;
	string	m_firstName;
	string	m_bdate;
	string	m_employed;

	stringstream * m_output;
};

#endif