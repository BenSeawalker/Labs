/************************************************************************
* Author:		Garrett Fleischer
* Filename:		InOrderIterator.h
* Date Created:	2/20/16
* Modifications:
*	N/A
*************************************************************************/
#ifndef INORDERITERATOR_H
#define INORDERITERATOR_H

#include "BSTIterator.h"

/************************************************************************
* Class: InOrderIterator
*
* Purpose:
*
* Manager functions:
* 	InOrderIterator ( )
*	PreOrderIterator (const InOrderIterator & copy)
*	operator = (const InOrderIterator & rhs)
*
*	~InOrderIterator()
*
* Methods:
*	PRIVATE
*		BuildQueue(root : BinaryTreeNode<T> *) : void
*
*************************************************************************/
template<typename T>
class InOrderIterator : public BSTIterator<T>
{
public:
	// CTORS & DTOR
	InOrderIterator(BinarySearchTree<T> * tree);
	InOrderIterator(const InOrderIterator<T> & copy);

	virtual ~InOrderIterator();

	// OPERATORS
	InOrderIterator<T> & operator=(const InOrderIterator<T> & rhs);

protected:
	// METHODS
	virtual void BuildQueue(BinaryTreeNode<T> * root);
};


///////////////////////////////////////////////////////////////
// C'TORS & D'TOR
//////

template<typename T>
InOrderIterator<T>::InOrderIterator(BinarySearchTree<T> * tree)
	: BSTIterator(tree)
{}

template<typename T>
InOrderIterator<T>::InOrderIterator(const InOrderIterator<T> & copy)
	: BSTIterator(copy)
{}

template<typename T>
InOrderIterator<T>::~InOrderIterator()
{}

//////
// END C'TORS & D'TOR
///////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////
// OPERATORS
//////

template<typename T>
InOrderIterator<T>& InOrderIterator<T>::operator=(const InOrderIterator<T> & rhs)
{
	if (this != &rhs)
	{
		BSTIterator::operator=(rhs);
	}

	return *this;
}

//////
// END OPERATORS
///////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////
// PRIVATE METHODS
//////

/************************************************************************
* Purpose: To recursively build @m_queue with the in-order algorithm
*
* Precondition:
*		Recursion ends when root == nullptr
*
* Postcondition:
*		Modifies:	@m_queue
*		Throws:		N/A
*		Returns:	N/A
*************************************************************************/
template<typename T>
void InOrderIterator<T>::BuildQueue(BinaryTreeNode<T> * root)
{
	if (root)
	{
		BuildQueue(root->Left());
		m_queue.Enqueue(root);
		BuildQueue(root->Right());
	}
}

//////
// END PRIVATE METHODS
///////////////////////////////////////////////////////////////

#endif // INORDERITERATOR_H