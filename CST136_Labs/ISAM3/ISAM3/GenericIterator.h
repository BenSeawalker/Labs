#ifndef GenericIterator_h__
#define GenericIterator_h__

#include "ISAMIterator.h"


/************************************************************************
* Class: GenericIterator<T>
*
* Purpose: This class is an instantiate-able version of the ISAMIterator 
*
* Manager functions:
*	GenericIterator(ISAM<T, KT> *)
*	~GenericIterator() : virtual
*
* Methods:
*	Public:
*		N/A
*	Private:
*		N/A
*************************************************************************/
template<typename T, typename KT>
class GenericIterator : public ISAMIterator<T, KT>
{
public:
	GenericIterator(ISAM<T, KT> * _ISAM);
	virtual ~GenericIterator();
};

template<typename T, typename KT>
GenericIterator<T, KT>::GenericIterator(ISAM<T, KT> * _ISAM)
	: ISAMIterator<T, KT>(_ISAM)
{}

template<typename T, typename KT>
GenericIterator<T, KT>::~GenericIterator()
{}

#endif // GenericIterator_h__


