#ifndef PREORDERITERATOR_H
#define PREORDERITERATOR_H

#include "BSTIterator.h"
#include "Queue.h"

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

template<typename T>
PreOrderIterator<T>& PreOrderIterator<T>::operator=(const PreOrderIterator<T> & rhs)
{
	if (this != &rhs)
	{
		BSTIterator::operator=(rhs);
	}

	return *this;
}

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

#endif // PREORDERITERATOR_H