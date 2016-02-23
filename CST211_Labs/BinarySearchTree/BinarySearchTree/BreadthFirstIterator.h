/************************************************************************
* Author:		Garrett Fleischer
* Filename:		BreadthFirstIterator.h
* Date Created:	2/20/16
* Modifications:
*	N/A
*************************************************************************/
#ifndef BREADTHFIRSTITERATOR_H
#define BREADTHFIRSTITERATOR_H

#include "BSTIterator.h"

/************************************************************************
* Class: BreadthFirstIterator
*
* Purpose:
*
* Manager functions:
* 	BreadthFirstIterator ( )
*	BreadthFirstIterator (const BreadthFirstIterator & copy)
*	operator = (const BreadthFirstIterator & rhs)
*
*	~BreadthFirstIterator()
*
* Methods:
*	PRIVATE
*		BuildQueue(root : BinaryTreeNode<T> *) : void
*
*************************************************************************/
template<typename T>
class BreadthFirstIterator : public BSTIterator<T>
{
public:
	// CTORS & DTOR
	BreadthFirstIterator(BinarySearchTree<T> * tree);
	BreadthFirstIterator(const BreadthFirstIterator<T> & copy);

	virtual ~BreadthFirstIterator();

	// OPERATORS
	BreadthFirstIterator<T> & operator=(const BreadthFirstIterator<T> & rhs);

protected:
	// METHODS
	virtual void BuildQueue(BinaryTreeNode<T> * root);
};


///////////////////////////////////////////////////////////////
// C'TORS & D'TOR
//////

template<typename T>
BreadthFirstIterator<T>::BreadthFirstIterator(BinarySearchTree<T> * tree)
	: BSTIterator(tree)
{}

template<typename T>
BreadthFirstIterator<T>::BreadthFirstIterator(const BreadthFirstIterator<T> & copy)
	: BSTIterator(copy)
{}

template<typename T>
BreadthFirstIterator<T>::~BreadthFirstIterator()
{}

//////
// END C'TORS & D'TOR
///////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////
// OPERATORS
//////

template<typename T>
BreadthFirstIterator<T>& BreadthFirstIterator<T>::operator=(const BreadthFirstIterator<T> & rhs)
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
* Purpose: To iteratively build @m_queue with the breadth-first algorithm
*
* Precondition:
*
* Postcondition:
*		Modifies:	@m_queue
*		Throws:		N/A
*		Returns:	N/A
*************************************************************************/
template<typename T>
void BreadthFirstIterator<T>::BuildQueue(BinaryTreeNode<T> * root)
{
	Queue<BinaryTreeNode<T> *> temp;
	temp.Enqueue(root);

	while (temp.Size() > 0)
	{
		BinaryTreeNode<T> * node = temp.Dequeue();

		if (node)
		{
			m_queue.Enqueue(node);
			temp.Enqueue(node->Left());
			temp.Enqueue(node->Right());
		}
	}
}

//////
// END PRIVATE METHODS
///////////////////////////////////////////////////////////////

#endif // BREADTHFIRSTITERATOR_H