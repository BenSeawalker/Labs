/************************************************************************
* Author:		Garrett Fleischer
* Filename:		AbstractIterator.h
* Date Created:	2/20/16
* Modifications:
*	N/A
*************************************************************************/
#ifndef ABSTRACTITERATOR_H
#define ABSTRACTITERATOR_H

#include "Exception.h"

/************************************************************************
* Class: AbstractIterator<T>
*
* Purpose: This class acts as an interface for all types of iterator
*
* Manager functions:
*	~AbstractIterator : virtual
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
template<typename T>
class AbstractIterator
{
public:
	virtual ~AbstractIterator() {}

	virtual void Reset() = 0;
	virtual void MoveNext() = 0;
	virtual T & GetCurrent() = 0;
	virtual bool IsDone() const = 0;
};


#endif // ABSTRACTITERATOR_H
