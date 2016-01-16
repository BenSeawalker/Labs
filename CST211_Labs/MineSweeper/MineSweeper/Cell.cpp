#include "Cell.h"


Cell::Cell(int value)
	: m_value(value), m_checked(false), m_flagged(false)
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

int Cell::Value() const
{
	return m_value;
}

void Cell::SetValue(int value)
{
	m_value = value;
}

bool Cell::Checked() const
{
	return m_checked;
}

void Cell::SetChecked(bool checked)
{
	m_checked = checked;
}

bool Cell::Flagged() const
{
	return m_flagged;
}

void Cell::SetFlagged(bool flagged)
{
	m_flagged = flagged;
}


