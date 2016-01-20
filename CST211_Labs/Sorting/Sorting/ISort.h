#ifndef SORT_H
#define SORT_H

#include <vector>
using std::vector;

#include "Array.h"


template<typename RT>
class ISort
{
protected:
	virtual void Sort(RT & ra, int length) = 0;
};

#endif // Sort_h__
