#ifndef Personnel_h__
#define Personnel_h__

#include <iostream>
using std::cout;
using std::endl;

class Personnel
{
public:
	Personnel(int _workNum, char _lName[10]);
	~Personnel();

	static void DisplayPersonnel(Personnel * _person);

private:
	int m_workNum;
	char m_lName[10];

	void Display();
};


#endif // Personnel_h__