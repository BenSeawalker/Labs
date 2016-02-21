//#ifndef BSTITERATOR_H
//#define BSTITERATOR_H
//
//#include "AbstractIterator.h"
//#include "BinarySearchTree.h"
//#include "BinaryTreeNode.h"
//
//template<typename T>
//class BSTIterator : public AbstractIterator<T>
//{
//public:
//	// DTOR
//	virtual ~BSTIterator();
//
//	// METHODS
//	virtual void Reset();
//	
//	virtual void MoveNext();
//
//	virtual T & GetCurrent();
//
//	virtual bool IsDone();
//
//protected:
//	// CTORS
//	BSTIterator(BinarySearchTree<T> * tree);
//	BSTIterator(const BinarySearchTree<T> * tree);
//	BSTIterator(const BSTIterator & copy);
//
//	// OPERATORS
//	BSTIterator<T> & operator=(const BSTIterator & rhs);
//
//	// METHODS
//	virtual void BuildQueue(BinaryTreeNode<T> * root) = 0;
//
//	// MEMBERS
//	BinarySearchTree<T> * m_tree;
//	const BinarySearchTree<T> * m_tree;
//	BinaryTreeNode<T> * m_current;
//	Queue<BinaryTreeNode<T> *> m_queue;
//};
//
//
//template<typename T>
//BSTIterator<T>::BSTIterator(BinarySearchTree<T> * tree)
//	: m_tree(tree), m_current(nullptr)
//{}
//
//template<typename T>
//BSTIterator<T>::BSTIterator(const BSTIterator & copy)
//	: m_tree(copy.m_tree), m_current(copy.m_current)
//{}
//
//template<typename T>
//BSTIterator<T>::~BSTIterator()
//{
//	m_tree = nullptr;
//	m_current = nullptr;
//	m_queue.Purge();
//}
//
//template<typename T>
//inline BSTIterator<T>& BSTIterator<T>::operator=(const BSTIterator & rhs)
//{
//	if (this != &rhs)
//	{
//		m_tree = rhs.m_tree;
//		m_current = rhs.m_current;
//	}
//
//	return *this;
//}
//
//template<typename T>
//void BSTIterator<T>::Reset()
//{
//	if (!m_tree)
//		throw Exception("Error accessing non-existent list!");
//
//	m_queue.Purge();
//	BuildQueue(m_tree->m_root);
//	MoveNext();
//}
//
//template<typename T>
//void BSTIterator<T>::MoveNext()
//{
//	m_current = (m_queue.isEmpty() ? nullptr : m_queue.Dequeue());
//}
//
//template<typename T>
//T & BSTIterator<T>::GetCurrent()
//{
//	if (IsDone())
//		throw Exception("Cannot access current element! Iterator is done.");
//
//	return m_current->Data();
//}
//
//template<typename T>
//bool BSTIterator<T>::IsDone()
//{
//	return m_current == nullptr;
//}
//
//#endif // BSTITERATOR_H