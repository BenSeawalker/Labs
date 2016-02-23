/************************************************************************
* Author:		Garrett Fleischer
* Filename:		PostOrderIterator.h
* Date Created:	2/20/16
* Modifications:
*	N/A
*************************************************************************/
#ifndef POSTORDERITERATOR_H
#define POSTORDERITERATOR_H

#include "BSTIterator.h"

/************************************************************************
* Class: PostOrderIterator
*
* Purpose:
*
* Manager functions:
* 	PostOrderIterator ( )
*	PreOrderIterator (const PostOrderIterator & copy)
*	operator = (const PostOrderIterator & rhs)
*
*	~PostOrderIterator()
*
* Methods:
*	PRIVATE
*		BuildQueue(root : BinaryTreeNode<T> *) : void
*
*************************************************************************/
template<typename T>
class PostOrderIterator : public BSTIterator<T>
{
public:
	// CTORS & DTOR
	PostOrderIterator(BinarySearchTree<T> * tree);
	PostOrderIterator(const PostOrderIterator<T> & copy);

	virtual ~PostOrderIterator();

	// OPERATORS
	PostOrderIterator<T> & operator=(const PostOrderIterator<T> & rhs);

protected:
	// METHODS
	virtual void BuildQueue(BinaryTreeNode<T> * root);
};

///////////////////////////////////////////////////////////////
// C'TORS & D'TOR
//////

template<typename T>
PostOrderIterator<T>::PostOrderIterator(BinarySearchTree<T> * tree)
	: BSTIterator(tree)
{}

template<typename T>
PostOrderIterator<T>::PostOrderIterator(const PostOrderIterator<T> & copy)
	: BSTIterator(copy)
{}

template<typename T>
PostOrderIterator<T>::~PostOrderIterator()
{}

//////
// END C'TORS & D'TOR
///////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////
// OPERATORS
//////

template<typename T>
PostOrderIterator<T>& PostOrderIterator<T>::operator=(const PostOrderIterator<T> & rhs)
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
* Purpose: To recursively build @m_queue with the post-order algorithm
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
void PostOrderIterator<T>::BuildQueue(BinaryTreeNode<T> * root)
{
	if (root)
	{
		BuildQueue(root->Left());
		BuildQueue(root->Right());
		m_queue.Enqueue(root);
	}
}

//////
// END PRIVATE METHODS
///////////////////////////////////////////////////////////////

#endif // POSTORDERITERATOR_H