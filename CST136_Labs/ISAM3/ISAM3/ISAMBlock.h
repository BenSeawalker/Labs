/*
@Author: Garrett Fleischer
@Date:	 10/18/15
*/

#ifndef ISAM_Block_h
#define ISAM_Block_h

#include "LinkedList.h"



/************************************************************************
* Class: ISAMBlock<T, KT>
*
* Purpose: This class acts as a wrapper around the LinkedList class
*			with a few convenience methods
*
* Manager functions:
* 	Block ()
*	~Block()
*
* Methods:
*	Public:
*		MoveTailNode(_to : ISAM_Block &) : void
*	Private:
*************************************************************************/
template<typename T, typename KT>
class ISAMBlock : public LinkedList<T, KT>
{
public:
	template<typename IT, typename IKT>
	friend class ISAMIterator;

	ISAMBlock();
	~ISAMBlock();

	void MoveTailNode(ISAMBlock & _to);

	const T * const FirstItem() { return (m_head ? m_head->data : nullptr); }
	const T * const LastItem() { return (m_tail ? m_tail->data : nullptr); }
};


/////////////////////////////////////////////////////////
//	C'tor and D'tor
//////////

template<typename T, typename KT>
ISAMBlock<T, KT>::ISAMBlock()
{}

template<typename T, typename KT>
ISAMBlock<T, KT>::~ISAMBlock()
{}

//////////
// END C'tor and D'tor
/////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////
//	PUBLIC METHODS
//////////
/**********************************************************************
* Purpose: This function Inserts a copy of this instance's tail node
*			into another Block and deletes this tail node.
*
* Precondition:
*		_to = the block to move the tail node to
*
* Postcondition:
*		Returns N/A
*
************************************************************************/
template<typename T, typename KT>
void ISAMBlock<T, KT>::MoveTailNode(ISAMBlock & _to)
{
	// move the tail to the specified block
	_to.Insert(m_tail);

	// if the previous node is m_head, set m_tail to nullptr
	// otherwise set m_tail to the previous node
	if (m_tail->previous == m_head)
		m_tail = nullptr;
	else
		m_tail = m_tail->previous;

	// make sure that m_tail's next is nullptr
	m_tail->next = nullptr;

	// decrement the size
	m_size--;
}

//////////
// END PUBLIC METHODS
/////////////////////////////////////////////////////////


#endif // ISAM_Block_h