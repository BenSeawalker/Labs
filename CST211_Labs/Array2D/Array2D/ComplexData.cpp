/************************************************************************
* Author:		Garrett Fleischer
* Filename:		ComplexData.cpp
* Date Created:	1/11/16
* Modifications:
*	N/A
*************************************************************************/
#include "ComplexData.h"


ComplexData::ComplexData(const string & data)
	: m_data(data)
{}

ComplexData::ComplexData(const ComplexData & copy)
{
	m_data = copy.m_data;
}

ComplexData::~ComplexData()
{}

ComplexData & ComplexData::operator=(const ComplexData & rhs)
{
	if (this != &rhs)
		m_data = rhs.m_data;

	return *this;
}

ostream & operator<<(ostream & stream, const ComplexData & complex)
{
	return (stream << complex.m_data);
}