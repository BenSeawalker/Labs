#ifndef SkipIterator_h__
#define SkipIterator_h__

#include "ISAMIterator.h"


/************************************************************************
* Class: SkipIterator<T>
*
* Purpose: This class skips every other item in the ISAM while iterating
*
* Manager functions:
*	SkipIterator(ISAM<T, KT> *)
*	~SkipIterator() : virtual
*
* Methods:
*	Public:
*		MoveNext()	 : void virtual
*	Private:
*		N/A
*************************************************************************/
template<typename T, typename KT>
class SkipIterator : public ISAMIterator<T, KT>
{
public:
	SkipIterator(ISAM<T, KT> * _ISAM);
	virtual ~SkipIterator();

public:
	virtual void MoveNext();
};


template<typename T, typename KT>
SkipIterator<T, KT>::SkipIterator(ISAM<T, KT> * _ISAM)
	: ISAMIterator(_ISAM)
{
	ISAMIterator<T, KT>::First();
}

template<typename T, typename KT>
SkipIterator<T, KT>::~SkipIterator()
{}


/**********************************************************************
* Purpose: This function moves the cursor forward twice
*
* Precondition:
*		N/A
*
* Postcondition:
*		m_cursor points to the Node after the next or nullptr
*
************************************************************************/
template<typename T, typename KT>
void SkipIterator<T, KT>::MoveNext()
{
	ISAMIterator::MoveNext();
	ISAMIterator::MoveNext();
}

#endif // SkipIterator_h__