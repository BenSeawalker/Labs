#pragma once

#include <fstream>
using std::ifstream;

#include "Array.h"
class Employee;

#include <iostream>
using std::cout;
using std::endl;

class ArrayController
{
public:
	ArrayController();
	~ArrayController();

private:
	Array<Employee> * m_array;

private:
	void ProcFile();
	void Display();
};

