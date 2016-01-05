#include "Array.h"

#include "Office.h"
#include "Sales.h"

#include <iostream>
using std::cout;

int main()
{
	/*Array<int> arr(5);

	arr.Insert(new int(10));
	arr.Insert(new int(3));
	arr.Insert(new int(5));
	arr.Insert(new int(20));
	arr.Insert(new int(15));*/

	Array<Employee> emps(4);

	emps.Insert(new Office("B", 10));
	emps.Insert(new Sales("A", 2, 5));
	emps.Insert(new Office("D", 15));
	emps.Insert(new Sales("C", 2, 3));

	for (UINT i = 0; i < emps.Size(); ++i)
		cout << *(emps[i]) << endl;

	cout << endl;

	return 0;
}