#include "Personnel.h"

Personnel::Personnel(int _workNum, char _lName[])
	: m_workNum(_workNum)
{
	strcpy(m_lName, _lName);
}

Personnel::~Personnel()
{
}

void Personnel::DisplayPersonnel(Personnel * _person)
{
	if (_person)
		_person->Display();
}

void Personnel::Display()
{
	cout << "Work #: " << m_workNum << " LName: " << m_lName << endl;
}
