#include "Cell.h"


Cell::Cell(int value)
	: m_value(value), m_checked(false)
{}


Cell::~Cell()
{
}

Cell & Cell::operator=(const Cell & rhs)
{
	m_value = rhs.m_value;
	m_checked = rhs.m_checked;

	return *this;
}
