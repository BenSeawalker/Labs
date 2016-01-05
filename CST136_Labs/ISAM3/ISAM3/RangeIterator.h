#ifndef AtoLIterator_h__
#define AtoLIterator_h__

#include "ISAMIterator.h"

/************************************************************************
* Class: RangeIterator<T>
*
* Purpose: This class ensures the cursor points to an item that is between m_from and m_to
*
* Manager functions:
*	RangeIterator(ISAM<T, KT> *)
*	~RangeIterator() : virtual
*
* Methods:
*	Public:
*		First()		 : void virtual
*		MoveNext()	 : void virtual
*	Private:
*		FindNext()   : void
*************************************************************************/
template<typename T, typename KT, typename RT>
class RangeIterator : public ISAMIterator<T, KT>
{
public:
	RangeIterator(ISAM<T, KT> * _ISAM, RT _from, RT _to);
	virtual ~RangeIterator();

public:
	virtual void First();
	virtual void MoveNext();

private:
	RT m_from;
	RT m_to;

	void FindNext();
};

template<typename T, typename KT, typename RT>
RangeIterator<T, KT, RT>::RangeIterator(ISAM<T, KT> * _ISAM, RT _from, RT _to)
	: ISAMIterator(_ISAM), m_from(_from), m_to(_to)
{
	First();
}

template<typename T, typename KT, typename RT>
RangeIterator<T, KT, RT>::~RangeIterator()
{}


/**********************************************************************
* Purpose: This function jumps to the very first item in the ISAM,
*			and then seeks the first matching item
*
* Precondition:
*		N/A
*
* Postcondition:
*		m_cursor points to the first matching Node or nullptr
*
************************************************************************/
template<typename T, typename KT, typename RT>
void RangeIterator<T, KT, RT>::First()
{
	ISAMIterator::First();
	FindNext();
}


/**********************************************************************
* Purpose: This function jumps to the next item in the ISAM, checks if it matches,
*			and if it does not: seeks the next matching item
*
* Precondition:
*		N/A
*
* Postcondition:
*		m_cursor points to the next matching Node or nullptr
*
************************************************************************/
template<typename T, typename KT, typename RT>
void RangeIterator<T, KT, RT>::MoveNext()
{
	ISAMIterator::MoveNext();
	FindNext();
}


/**********************************************************************
* Purpose: This function iterates through
*
* Precondition:
*		N/A
*
* Postcondition:
*		m_cursor points to the next matching Node or nullptr
*
************************************************************************/
template<typename T, typename KT, typename RT = char>
void RangeIterator<T, KT, RT>::FindNext()
{
	bool found = false;
	RT data;

	while (!found && !IsDone())
	{
		data = RT(*(m_cursor->data));
		found = ((data >= m_from) && (data <= m_to));

		if (!found)
			ISAMIterator::MoveNext();
	}
}

#endif // AtoLIterator_h__