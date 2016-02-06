#include <iostream>
using std::cout;
using std::endl;

#include "Delegate.h"

//#include <cstdio>
//#include "Callback.h"
//
//using util::Callback;
//
//class Foo
//{
//public:
//	Foo() {}
//	double MemberFunction(int a, int b) { return a + b; }
//	double ConstMemberFunction(int a, int b) const { return a - b; }
//	static double StaticFunction(int a, int b) { return a*b; }
//};
//
//double GlobalFunction(int a, int b) { return a / (double)b; }
//
//void Invoke(int a, int b, Callback<double(int, int)> callback)
//{
//	if (callback)
//	{
//		::printf("%f\n", callback(a, b));
//	}
//	else
//	{
//		::printf("Nothing to call.\n");
//	}
//}

class Foo
{
public:
	Foo();
	~Foo();

private:

};

class Bar
{
public:
	Bar(Delegate<Foo,  );
	~Bar();

	void Update()
	{

	}

private:
};

void TestFunc();

int main()
{
	Bar b;
	b.Update();
	/*Foo f;
	Invoke(10, 20, BIND_MEM_CB(&Foo::MemberFunction, &f));
	Invoke(10, 20, BIND_MEM_CB(&Foo::ConstMemberFunction, &f));
	Invoke(10, 20, BIND_FREE_CB(&Foo::StaticFunction));

	Callback<double(int, int)> cb = BIND_FREE_CB(&GlobalFunction);
	Invoke(10, 20, cb);

	cb = util::NullCallback();
	Invoke(10, 20, cb);
*/

	/* Expected output:
	30.000000
	-10.000000
	200.000000
	0.500000
	Nothing to call.
	*/

	return 0;
}


void TestFunc()
{
	cout << "TestFunc()" << endl;
}