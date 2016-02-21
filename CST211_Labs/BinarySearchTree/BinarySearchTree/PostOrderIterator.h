#ifndef POSTORDERITERATOR_H
#define POSTORDERITERATOR_H

#include "BSTIterator.h"
#include "Queue.h"

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

template<typename T>
PostOrderIterator<T>& PostOrderIterator<T>::operator=(const PostOrderIterator<T> & rhs)
{
	if (this != &rhs)
	{
		BSTIterator::operator=(rhs);
	}

	return *this;
}

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

#endif // POSTORDERITERATOR_H