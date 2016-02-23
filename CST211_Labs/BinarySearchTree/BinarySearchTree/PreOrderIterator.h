/************************************************************************
* Author:		Garrett Fleischer
* Filename:		PreOrderIterator.h
* Date Created:	2/20/16
* Modifications:
*	N/A
*************************************************************************/
#ifndef PREORDERITERATOR_H
#define PREORDERITERATOR_H

#include "BSTIterator.h"

/************************************************************************
* Class: PreOrderIterator
*
* Purpose: 
*
* Manager functions:
* 	PreOrderIterator ( )
*	PreOrderIterator (const PreOrderIterator & copy)
*	operator = (const PreOrderIterator & rhs)
*
*	~PreOrderIterator()
*
* Methods:
*	PRIVATE
*		BuildQueue(root : BinaryTreeNode<T> *) : void
*
*************************************************************************/
template<typename T>
class PreOrderIterator : public BSTIterator<T>
{
public:
	// CTORS & DTOR
	PreOrderIterator(BinarySearchTree<T> * tree);
	PreOrderIterator(const PreOrderIterator<T> & copy);

	virtual ~PreOrderIterator();

	// OPERATORS
	PreOrderIterator<T> & operator=(const PreOrderIterator<T> & rhs);

protected:
	// METHODS
	virtual void BuildQueue(BinaryTreeNode<T> * root);
};


///////////////////////////////////////////////////////////////
// C'TORS & D'TOR
//////

template<typename T>
PreOrderIterator<T>::PreOrderIterator(BinarySearchTree<T> * tree)
	: BSTIterator(tree)
{}

template<typename T>
PreOrderIterator<T>::PreOrderIterator(const PreOrderIterator<T> & copy)
	: BSTIterator(copy)
{}

template<typename T>
PreOrderIterator<T>::~PreOrderIterator()
{}

//////
// END C'TORS & D'TOR
///////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////
// OPERATORS
//////

template<typename T>
PreOrderIterator<T>& PreOrderIterator<T>::operator=(const PreOrderIterator<T> & rhs)
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
* Purpose: To recursively build @m_queue with the pre-order algorithm
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
void PreOrderIterator<T>::BuildQueue(BinaryTreeNode<T> * root)
{
	if (root)
	{
		m_queue.Enqueue(root);
		BuildQueue(root->Left());
		BuildQueue(root->Right());
	}
}

//////
// END PRIVATE METHODS
///////////////////////////////////////////////////////////////

#endif // PREORDERITERATOR_H