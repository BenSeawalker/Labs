#include "ArrayController.h"

#include "Office.h"
#include "Sales.h"


ArrayController::ArrayController()
{
	m_array = new Array<Employee>(15);

	ProcFile();
	Display();
}


ArrayController::~ArrayController()
{
	delete m_array;
}

void ArrayController::ProcFile()
{
	char lname[10];
	char code;

	ifstream file("employee.txt");

	if (file.is_open())
	{
		while (!file.eof())
		{
			file >> lname >> code;
			Employee * emp;

			if (code == 'O')
			{
				int salary;
				file >> salary;
				emp = new Office(lname, salary);
			}
			else
			{
				float base, com;
				file >> base >> com;
				emp = new Sales(lname, base, com);
			}

			try
			{
				m_array->Insert(emp);
			}
			catch (const char * err)
			{
				delete emp;
				cout << err << endl << endl;
			}
		}

		file.close();
	}
}

void ArrayController::Display()
{
	for (UINT i = 0; i < m_array->Size(); ++i)
		cout << *((*m_array)[i]) << endl;
}
