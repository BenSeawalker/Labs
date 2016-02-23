/************************************************************************
* Author:		Garrett Fleischer
* Filename:		BSTIterator.h
* Date Created:	2/20/16
* Modifications:
*	N/A
*************************************************************************/
#ifndef BSTITERATOR_H
#define BSTITERATOR_H

#include "AbstractIterator.h"
#include "BinarySearchTree.h"
#include "BinaryTreeNode.h"
#include "Queue.h"


/************************************************************************
* Class: BSTIterator
*
* Purpose: To provide base functionality for iterating over all elements in a Tree
*			Default functionality is to BuildQueue() and move through all its elements
*
* Manager functions:
* 	BSTIterator ( )
*	BSTIterator (const BSTIterator & copy)
*	operator = (const BSTIterator & rhs)
*
*	~BSTIterator()
*
* Methods:
*	PUBLIC
*		Reset()			: void
*		MoveNext()		: void
*		GetCurrent()	: T &
*		IsDone()		: void
*
*	PRIVATE
*		BuildQueue(root : BinaryTreeNode<T> *) : void
*
*************************************************************************/
template<typename T>
class BSTIterator : public AbstractIterator<T>
{
public:
	// DTOR
	virtual ~BSTIterator();

	// METHODS
	virtual void Reset();
	
	virtual void MoveNext();

	virtual T & GetCurrent();

	virtual bool IsDone() const;

protected:
	// CTORS
	BSTIterator(BinarySearchTree<T> * tree);
	BSTIterator(const BinarySearchTree<T> * tree);
	BSTIterator(const BSTIterator & copy);

	// OPERATORS
	BSTIterator<T> & operator=(const BSTIterator & rhs);

	// METHODS
	virtual void BuildQueue(BinaryTreeNode<T> * root) = 0;

	// MEMBERS
	BinarySearchTree<T> * m_tree;
	BinaryTreeNode<T> * m_current;
	Queue<BinaryTreeNode<T> *> m_queue;
};


///////////////////////////////////////////////////////////////
// C'TORS & D'TOR
//////

template<typename T>
BSTIterator<T>::BSTIterator(BinarySearchTree<T> * tree)
	: m_tree(tree), m_current(nullptr)
{}

template<typename T>
BSTIterator<T>::BSTIterator(const BSTIterator & copy)
	: m_tree(copy.m_tree), m_current(copy.m_current)
{}

template<typename T>
BSTIterator<T>::~BSTIterator()
{
	m_tree = nullptr;
	m_current = nullptr;
	m_queue.Purge();
}

//////
// END C'TORS & D'TOR
///////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////
// OPERATORS
//////

template<typename T>
BSTIterator<T>& BSTIterator<T>::operator=(const BSTIterator & rhs)
{
	if (this != &rhs)
	{
		m_tree = rhs.m_tree;
		m_current = rhs.m_current;
	}

	return *this;
}

//////
// END OPERATORS
///////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////
// PUBLIC METHODS
//////

/************************************************************************
* Purpose: To rebuild @m_queue and set m_current to the first item in it
*
* Precondition:
*		@m_list : cannot be nullptr
*
* Postcondition:
*		Modifies:	@m_current, @m_queue
*		Throws:		Exception("Error accessing non-existent list!")
*		Returns:	N/A
*************************************************************************/
template<typename T>
void BSTIterator<T>::Reset()
{
	if (!m_tree)
		throw Exception("Error accessing non-existent list!");

	m_queue.Purge();
	BuildQueue(m_tree->m_root);
	MoveNext();
}

/************************************************************************
* Purpose: To move @m_current to the "next" item in @m_queue
*
* Precondition:
*		IsDone() must return false
*
* Postcondition:
*		Modifies:	@m_current
*		Throws:		Exception("Cannot access next element! Iterator is done.")
*		Returns:	N/A
*************************************************************************/
template<typename T>
void BSTIterator<T>::MoveNext()
{
	m_current = (m_queue.isEmpty() ? nullptr : m_queue.Dequeue());

	if (IsDone())
		Exception("Cannot access next element! Iterator is done.");
}

/************************************************************************
* Purpose: To get the data stored at the current element
*
* Precondition:
*		IsDone() must return false
*
* Postcondition:
*		Modifies:	N/A
*		Throws:		Exception("Cannot access current element! Iterator is done.")
*		Returns:	N/A
*************************************************************************/
template<typename T>
T & BSTIterator<T>::GetCurrent()
{
	if (IsDone())
		throw Exception("Cannot access current element! Iterator is done.");

	return m_current->Data();
}

/************************************************************************
* Purpose: To check if all the elements have been iterated over
*
* Precondition:
*		@m_current is equivalent to nullptr
*
* Postcondition:
*		Modifies:	N/A
*		Throws:		N/A
*		Returns:	TRUE if the iterator has finished
*************************************************************************/
template<typename T>
bool BSTIterator<T>::IsDone() const
{
	return m_current == nullptr;
}

//////
// END PUBLIC METHODS
///////////////////////////////////////////////////////////////

#endif // BSTITERATOR_H