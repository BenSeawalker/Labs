#ifndef BREADTHFIRSTITERATOR_H
#define BREADTHFIRSTITERATOR_H

#include "BSTIterator.h"
#include "Queue.h"

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

template<typename T>
BreadthFirstIterator<T>& BreadthFirstIterator<T>::operator=(const BreadthFirstIterator<T> & rhs)
{
	if (this != &rhs)
	{
		BSTIterator::operator=(rhs);
	}

	return *this;
}

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

#endif // BREADTHFIRSTITERATOR_H