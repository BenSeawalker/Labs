#ifndef LISTNODE_H
#define LISTNODE_H

#include "doublelinkedlist.h"

template<typename T>
class ListNode
{ 
    template<typename DT>
    friend class DoubleLinkedList;

public:
    // METHODS
    T & Data();
    
    ListNode<T> *& Prev();
    ListNode<T> *& Next();
    
private:
    // C'TORS & D'TOR
    ListNode();
    ListNode(const T & data);
    ListNode(const ListNode & copy);
    
    ~ListNode();
    
    // OPERATORS
    ListNode<T> & operator=(const ListNode & rhs);
    
    // METHODS
    
    
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
{
	cout << "Node Default c'tor" << endl;
}

template<typename T>
ListNode<T>::ListNode(const T & data)
    : m_data(data), m_prev(nullptr), m_next(nullptr)
{
	cout << "Node Data c'tor" << endl;
}

template<typename T>
ListNode<T>::ListNode(const ListNode & copy)
    : m_data(copy.Data()), m_prev(copy.Prev()), m_next(copy.Next())
{
	cout << "Node Copy c'tor" << endl;
}

template<typename T>
ListNode<T>::~ListNode()
{
	cout << "Node d'tor" << endl;
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
ListNode<T> *& ListNode<T>::Prev()
{
    return m_prev;
}

template<typename T>
ListNode<T> *& ListNode<T>::Next()
{
    return m_next;
}

//////
// END PUBLIC METHODS
///////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////
// PRIVATE METHODS
//////

//////
// END PRIVATE METHODS
///////////////////////////////////////////////////////////////

#endif // LISTNODE_H

