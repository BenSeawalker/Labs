/************************************************************************
* Author:		Garrett Fleischer
* Filename:		listnode.h
* Date Created:	1/6/16
* Modifications:
*	2/20/16 Fixed constness of getters and setters
*************************************************************************/

#ifndef LISTNODE_H
#define LISTNODE_H


/************************************************************************
* Class: ListNode
*
* Purpose: Necessary for DoubleLinkedList to function
*
* Manager functions:
* 	ListNode ( )
* 		The default next and prev values are nullptr
*
*	ListNode (const T & data)
*		Convenience C'tor for initializing with data
*
*	ListNode (const ListNode & copy)
*	operator = (const ListNode & rhs)
*
*	~ListNode()
*
* Methods:
*	PUBLIC
*		T & Data();
*		void SetData(const T & data);
*
*	PRIVATE
*		ListNode<T> *& Prev();
*		ListNode<T> *& Next();
*
*************************************************************************/
template<typename T>
class ListNode
{
	template<typename DT>
	friend class DoubleLinkedList;

public:
    // METHODS
    T & Data();
	const T & Data() const;
    
	ListNode<T> *& Prev();
	const ListNode<T> * Prev() const;

	ListNode<T> *& Next();
	const ListNode<T> * Next() const;

private:
    // C'TORS & D'TOR
    ListNode();
    ListNode(const T & data);
    ListNode(const ListNode & copy);
    
    ~ListNode();
    
    // OPERATORS
    ListNode<T> & operator=(const ListNode & rhs);

    // MEMBERS
    T m_data;
    ListNode<T> * m_prev;
    ListNode<T> * m_next;
};


///////////////////////////////////////////////////////////////
// C'TORS & D'TOR
//////

template<typename T>
ListNode<T>::ListNode()
    : m_prev(nullptr), m_next(nullptr)
{}

template<typename T>
ListNode<T>::ListNode(const T & data)
    : m_data(data), m_prev(nullptr), m_next(nullptr)
{}

template<typename T>
ListNode<T>::ListNode(const ListNode & copy)
    : m_data(copy.Data()), m_prev(copy.Prev()), m_next(copy.Next())
{}

template<typename T>
ListNode<T>::~ListNode()
{
	m_prev = nullptr;
	m_next = nullptr;
}

//////
// END C'TORS & D'TOR
///////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////
// OPERATORS
//////

template<typename T>
ListNode<T> & ListNode<T>::operator=(const ListNode & rhs)
{
    m_data = rhs.Data();
    m_prev = rhs.Prev();
    m_next = rhs.Next();
}

//////
// END OPERATORS
///////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////
// PUBLIC METHODS
//////

template<typename T>
T & ListNode<T>::Data()
{
    return m_data;
}

template<typename T>
const T & ListNode<T>::Data() const
{
	return m_data;
}

template<typename T>
ListNode<T> *& ListNode<T>::Prev()
{
	return m_prev;
}

template<typename T>
const ListNode<T>* ListNode<T>::Prev() const
{
	return m_prev;
}

template<typename T>
ListNode<T> *& ListNode<T>::Next()
{
	return m_next;
}

template<typename T>
const ListNode<T>* ListNode<T>::Next() const
{
	return m_next;
}

//////
// END PUBLIC METHODS
///////////////////////////////////////////////////////////////

#endif // LISTNODE_H

