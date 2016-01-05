#ifndef ISAMIterator_h__
#define ISAMIterator_h__

#include "Iterator.h"


/************************************************************************
* Class: ISAMIterator<T, KT>
*
* Purpose: This class implements the basic methods for iterating through
*			every item in an ISAM DS
*
* Manager functions:
*	Public:
*		~IsamIterator() : virtual
*	Protected:
*		ISAMIterator(ISAM<T, KT> *)
*		
*
* Methods:
*	Public:
*		First()		 : void
*		MoveNext()	 : void
*		GetCurrent() : T *
*		IsDone()	 : bool
*	Private:
*		N/A
*************************************************************************/
template<typename T, typename KT>
class ISAMIterator : public Iterator<T>
{
public:
	virtual ~ISAMIterator();

	virtual void First();
	virtual void MoveNext();
	virtual T * GetCurrent();
	virtual bool IsDone();

protected:
	ISAMIterator(ISAM<T, KT> * _ISAM);

	ISAM<T, KT> * m_ISAM;

	bool	  m_isDone;
	int		  m_row;
	Node<T> * m_cursor;
};



template<typename T, typename KT>
ISAMIterator<T, KT>::ISAMIterator(ISAM<T, KT> * _ISAM)
	: m_ISAM(_ISAM), m_row(0), m_cursor(nullptr)
{
	First();
}

template<typename T, typename KT>
ISAMIterator<T, KT>::~ISAMIterator()
{}

template<typename T, typename KT>
void ISAMIterator<T, KT>::First()
{
	if (m_ISAM)
	{
		m_row = 0;
		m_cursor = m_ISAM->m_blocks[m_row]->m_head;
		m_isDone = !m_cursor;
	}
}

template<typename T, typename KT>
void ISAMIterator<T, KT>::MoveNext()
{
	if (m_ISAM)
	{
		if (!m_isDone && m_cursor)
			m_cursor = m_cursor->next;

		while (!m_cursor && ++m_row < m_ISAM->MAX_BLOCKS)
			m_cursor = m_ISAM->m_blocks[m_row]->m_head;

		m_isDone = ((m_row >= m_ISAM->MAX_BLOCKS) && !m_cursor);
	}
}

template<typename T, typename KT>
T * ISAMIterator<T, KT>::GetCurrent()
{
	return  (!m_isDone ? m_cursor->data : nullptr);
}

template<typename T, typename KT>
bool ISAMIterator<T, KT>::IsDone()
{
	return m_isDone;
}


#endif // ISAMIterator_h__

