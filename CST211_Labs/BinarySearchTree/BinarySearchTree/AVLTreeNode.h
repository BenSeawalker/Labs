#ifndef AVLTREENODE_H
#define AVLTREENODE_H

#include "BinaryTreeNode.h"

enum BALANCE { LH, EH, RH };

template<typename T>
class AVLTreeNode : public BinaryTreeNode<T>
{
	template<typename AT>
	friend class AVLTree;

protected:
	// CTORS & DTOR
	AVLTreeNode(const T & data);
	AVLTreeNode(const AVLTreeNode & copy);

	virtual ~AVLTreeNode();

	// OPERATORS
	AVLTreeNode & operator=(const AVLTreeNode & rhs);

	// METHODS
	void SetBalance(int balance);

	BALANCE & Balance();
	const BALANCE & Balance() const;

	BALANCE m_balance;
};




template<typename T>
AVLTreeNode<T>::AVLTreeNode(const T & data)
	: BinaryTreeNode(data), m_balance(EH)
{}

template<typename T>
AVLTreeNode<T>::AVLTreeNode(const AVLTreeNode & copy)
	: BinaryTreeNode(copy), m_balance(copy.m_balance)
{}

template<typename T>
AVLTreeNode<T>::~AVLTreeNode()
{}

template<typename T>
AVLTreeNode<T> & AVLTreeNode<T>::operator=(const AVLTreeNode & rhs)
{
	if (this != &rhs)
	{
		BinaryTreeNode::operator=(rhs);
		m_balance = rhs.m_balance;
	}

	return *this;
}

template<typename T>
void AVLTreeNode<T>::SetBalance(int balance)
{
	if (balance == 0)
		m_balance = EH;
	else if (balance < 0)
		m_balance = RH;
	else
		m_balance = LH;
}

template<typename T>
BALANCE & AVLTreeNode<T>::Balance()
{
	return m_balance;
}

template<typename T>
const BALANCE & AVLTreeNode<T>::Balance() const
{
	return m_balance;
}

#endif // AVLTREENODE_H