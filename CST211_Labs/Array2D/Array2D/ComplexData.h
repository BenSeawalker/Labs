/************************************************************************
* Author:		Garrett Fleischer
* Filename:		ComplexData.h
* Date Created:	1/11/16
* Modifications:
*	N/A
*************************************************************************/
#ifndef COMPLEXDATA_H
#define COMPLEXDATA_H

#include <string>
using std::string;
#include <ostream>
using std::ostream;

/************************************************************************
* Class: ComplexData
*
* Purpose: This class is used to test a templated data structure with a complex data type
*
* Manager functions:
*	ComplexData (const string & data = "*")
*
*	ComplexData (const ComplexData & copy)
*	operator = (const ComplexData & rhs)
*
*	~Exception()
*
* Methods:
*	operator<<(std::ostream & stream, const ComplexData & complex)
*		Returns ostream with complex's data appended to it
*
*************************************************************************/
class ComplexData
{
public:
	ComplexData(const string & data = "*");
	ComplexData(const ComplexData & copy);
	~ComplexData();

	// OPERATORS
	ComplexData & operator=(const ComplexData & rhs);
	friend ostream & operator<<(ostream & stream, const ComplexData & complex);

private:
	string m_data;
};


#endif // COMPLEXDATA_H