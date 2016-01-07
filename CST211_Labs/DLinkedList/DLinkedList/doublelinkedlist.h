#ifndef DOUBLELINKEDLIST_H
#define DOUBLELINKEDLIST_H

#include "listnode.h"

template<typename T>
class DoubleLinkedList
{
public:
    // C'TORS & D'TOR
    DoubleLinkedList();
    DoubleLinkedList(const DoubleLinkedList & copy);
    
    ~DoubleLinkedList();
   
    // OPERATORS
    DoubleLinkedList<T> & operator=(const DoubleLinkedList & rhs);
    
    // METHODS
    bool isEmpty() const;
    const T & First() const;
    const T & Last() const;
    
    void Prepend(const T & item);
    void Append(const T & item);
    
    void InsertAfter(const T & item, const T & after);
    void InsertBefore(const T & item, const T & before);
    
    void Purge();
    void Extract(const T & item);
    
    void Traverse(void (*Visit)(const T &));
    
    // TESTING
    ListNode<T> * getHead();
    ListNode<T> * getTail();
    
private:
    // METHODS
    ListNode<T> * FindNode(const T & data);
    static void DeepCopyNodes(DoubleLinkedList * dest, const DoubleLinkedList * source);
    
    // MEMBERS
    ListNode<T> * m_head;
    ListNode<T> * m_tail;
};


///////////////////////////////////////////////////////////////
// C'TORS & D'TOR
//////

template<typename T>
DoubleLinkedList<T>::DoubleLinkedList()
    : m_head(nullptr), m_tail(nullptr)
{}

template<typename T>
DoubleLinkedList<T>::DoubleLinkedList(const DoubleLinkedList & copy)
    : m_head(nullptr), m_tail(nullptr)
{
    DeepCopyNodes(this, &copy);
}

template<typename T>
DoubleLinkedList<T>::~DoubleLinkedList()
{
    Purge();
}

//////
// END C'TORS & D'TOR
///////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////
// OPERATORS
//////

template<typename T>
DoubleLinkedList<T> & DoubleLinkedList<T>::operator=(const DoubleLinkedList & rhs)
{
    if(this != &rhs)
        DeepCopyNodes(this, &rhs);

	return *this;
}

//////
// END OPERATORS
///////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////
// PUBLIC METHODS
//////

template<typename T>
bool DoubleLinkedList<T>::isEmpty() const
{
    return (m_head == nullptr);
}

template<typename T>
const T & DoubleLinkedList<T>::First() const
{
    if(m_head == nullptr)
        throw "Cannot access first element: LIST_IS_EMPTY";
    
    return m_head->Data();
}

template<typename T>
const T & DoubleLinkedList<T>::Last() const
{
    if(m_head == nullptr)
        throw "Cannot access last element: LIST_IS_EMPTY";
    else if(m_tail == nullptr)
        throw "Cannot access last element: LIST_CONTAINS_ONE_ELEMENT";
    
    return m_tail->Data();
}

template<typename T>
void DoubleLinkedList<T>::Prepend(const T & item)
{
    ListNode<T> * node = new ListNode<T>(item);
    node->Next() = m_head;
    m_head->Prev() = node;
    
    m_head = node;
}

template<typename T>
void DoubleLinkedList<T>::Append(const T & item)
{
    ListNode<T> * node = new ListNode<T>(item);
    ListNode<T> * last = ((m_tail) ? m_tail : m_head);
    
    if(last == nullptr)
    {
        m_head = node;
    }
    else
    {
        node->Prev() = last;
        last->Next() = node;
        
        m_tail = node;
    }
    
}

template<typename T>
void DoubleLinkedList<T>::InsertBefore(const T & item, const T & before)
{
    ListNode<T> * found_node = FindNode(before);
    
    if(found_node == nullptr)
    {
        throw "Before node not found!";
    }
    else
    {
        ListNode<T> * node = new ListNode<T>(item);
        
        if(found_node == m_head)
            m_head = node;
        else
            found_node->Prev()->Next() = node;
         
        node->Prev() = found_node->Prev();
        node->Next() = found_node;
        found_node->Prev() = node;
    }
}



template<typename T>
void DoubleLinkedList<T>::InsertAfter(const T & item, const T & after)
{
    ListNode<T> * found_node = FindNode(after);
    
    if(found_node == nullptr)
    {
        throw "After node not found!";
    }
    else
    {
        ListNode<T> * node = new ListNode<T>(item);
        
        if((found_node == m_tail) || (found_node == m_head && !m_tail))
            m_tail = node;
        else
            found_node->Next()->Prev() = node;
        
        node->Prev() = found_node;
        node->Next() = found_node->Next();
        found_node->Next() = node;
    }
}


template<typename T>
void DoubleLinkedList<T>::Traverse(void (*Visit)(const T &))
{
    ListNode<T> * travel = m_head;
    
    while(travel)
    {
        Visit(travel->Data());
        travel = travel->Next();
    }
}



template<typename T>
void DoubleLinkedList<T>::Purge()
{
    ListNode<T> * travel = m_head;
    ListNode<T> * trail = nullptr;
    
    while(travel)
    {
        trail = travel;
        travel = travel->Next();
        
        delete trail;
    }
}

template<typename T>
void DoubleLinkedList<T>::Extract(const T & item)
{
    ListNode<T> * found_node = FindNode(item);
    
    if(found_node == nullptr)
    {
        throw "Extract node not found!";
    }
    else
    {
        if(found_node == m_head)
        {
            m_head = m_head->Next();
            m_head->Prev() = nullptr;
        }
        else if(found_node == m_tail)
        {
            m_tail = m_tail->Prev();
            m_tail->Next() = nullptr;
        }
        else
        {
            found_node->Next()->Prev() = found_node->Prev();
            found_node->Prev()->Next() = found_node->Next();
        }
        
        if(m_head == m_tail)
            m_tail = nullptr;
        
        delete found_node;
    }
}

//////
// END PUBLIC METHODS
///////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////
// PRIVATE METHODS
//////

template<typename T>
ListNode<T> * DoubleLinkedList<T>::FindNode(const T & data)
{
    bool found = false;
    ListNode<T> * travel = m_head;
    
    while(travel && !found)
    {
        if(travel->Data() == data)            
            found = true;
        else
            travel = travel->Next();
    }
    
    return travel;
}

template<typename T>
void DoubleLinkedList<T>::DeepCopyNodes(DoubleLinkedList * dest, const DoubleLinkedList * source)
{
    ListNode<T> * travel_copy = source->m_head;
    ListNode<T> * trail = nullptr;
    
    while(travel_copy)
    {
        ListNode<T> * node = new ListNode<T>(travel_copy->Data());
        node->Prev() = trail;
        if(trail)
            trail->Next() = node;
        
        if(travel_copy == source->m_head)
            dest->m_head = node;
        else if(travel_copy == source->m_tail)
            dest->m_tail = node;
        
        trail = node;
        travel_copy = travel_copy->Next();
    }
}

//////
// END PRIVATE METHODS
///////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////
// TESTING
//////

template<typename T>
ListNode<T> * DoubleLinkedList<T>::getHead()
{
    return m_head;
}

template<typename T>
ListNode<T> * DoubleLinkedList<T>::getTail()
{
    return m_tail;
}

//////
// END TESTING
///////////////////////////////////////////////////////////////



#endif // DOUBLELINKEDLIST_H



