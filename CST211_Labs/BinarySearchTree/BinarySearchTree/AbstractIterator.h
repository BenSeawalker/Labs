#ifndef ABSTRACTITERATOR_H
#define ABSTRACTITERATOR_H

#include "Exception.h"

/************************************************************************
* Class: AbstractIterator<T>
*
* Purpose: This class acts as an interface for all types of AbstractIterator
*
* Manager functions:
*	N/A
*
* Methods:
*	Public:
*		Reset()		 : void
*		MoveNext()	 : void
*		GetCurrent() : T *
*		IsDone()	 : bool
*	Private:
*		N/A
*************************************************************************/
template<typename ST, typename RT, typename T>
class AbstractIterator
{
public:
	virtual void Reset() = 0;
	virtual void MoveNext() = 0;
	virtual RT & GetCurrent() = 0;
	virtual bool IsDone() const = 0;
};


#endif // ABSTRACTITERATOR_H
