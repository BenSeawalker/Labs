#ifndef Test_h__
#define Test_h__

#include "GObject.h"



class Test : public GObject
{
public:
	Test();
	virtual ~Test();

private:
	void bar(int j);
};

#endif // Test_h__
