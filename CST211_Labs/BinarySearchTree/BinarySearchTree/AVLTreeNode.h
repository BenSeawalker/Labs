/************************************************************************
* Author:		Garrett Fleischer
* Filename:		AVLTreeNode.h
* Date Created:	2/15/16
* Modifications:
*	N/A
*************************************************************************/
#ifndef AVLTREENODE_H
#define AVLTREENODE_H

#include "BinaryTreeNode.h"

enum BALANCE { RH = -1, EH, LH };


/************************************************************************
* Class: AVLTreeNode
*
* Purpose: This class provides data storage and convenience methods for
*			nodes in a balanced binary tree structure ADT
*
* Manager functions:
* 	AVLTreeNode(data : const T &)
*
*	AVLTreeNode(copy : const AVLTreeNode &)
*	operator = (rhs : const AVLTreeNode &)
*
*	~AVLTreeNode()
*
* Methods:
*
*	Balance() : BALANCE &
*	
* Inherited from BinaryTreeNode :
*
*		Data()	: T &
*
*		Left()	: BinaryTreeNode *&
*
*		Right()	: BinaryTreeNode *&
*
*************************************************************************/
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
	BALANCE & Balance();
	const BALANCE & Balance() const;

	// MEMBERS
	BALANCE m_balance;
};


///////////////////////////////////////////////////////////////
//	C'TORS & D'TOR
//////

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

//////
//	END C'TORS & D'TOR
///////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////
//	OPERATORS
//////


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

//////
//	END OPERATORS
///////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////
//	PROTECTED METHODS
//////

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

//////
//	END PROTECTED METHODS
///////////////////////////////////////////////////////////////

#endif // AVLTREENODE_H