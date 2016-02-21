//#ifndef INORDERITERATOR_H
//#define INORDERITERATOR_H
//
//#include "BSTIterator.h"
//#include "Queue.h"
//
//template<typename T>
//class InOrderIterator : public BSTIterator<T>
//{
//public:
//	// CTORS & DTOR
//	InOrderIterator(BinarySearchTree<T> * tree);
//	InOrderIterator(const InOrderIterator<T> & copy);
//
//	virtual ~InOrderIterator();
//
//	// OPERATORS
//	InOrderIterator<T> & operator=(const InOrderIterator<T> & rhs);
//
//protected:
//	// METHODS
//	virtual void BuildQueue(BinaryTreeNode<T> * root);
//};
//
//
//template<typename T>
//InOrderIterator<T>::InOrderIterator(BinarySearchTree<T> * tree)
//	: BSTIterator(tree)
//{}
//
//template<typename T>
//InOrderIterator<T>::InOrderIterator(const InOrderIterator<T> & copy)
//	: BSTIterator(copy)
//{}
//
//template<typename T>
//InOrderIterator<T>::~InOrderIterator()
//{}
//
//template<typename T>
//InOrderIterator<T>& InOrderIterator<T>::operator=(const InOrderIterator<T> & rhs)
//{
//	if (this != &rhs)
//	{
//		BSTIterator::operator=(rhs);
//	}
//
//	return *this;
//}
//
//template<typename T>
//void InOrderIterator<T>::BuildQueue(BinaryTreeNode<T> * root)
//{
//	if (root)
//	{
//		BuildQueue(root->Left());
//		m_queue.Enqueue(root);
//		BuildQueue(root->Right());
//	}
//}
//
//#endif // INORDERITERATOR_H