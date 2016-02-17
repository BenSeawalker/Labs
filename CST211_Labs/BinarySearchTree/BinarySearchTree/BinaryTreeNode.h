/************************************************************************
* Author:		Garrett Fleischer
* Filename:		BinaryTreeNode.h
* Date Created:	2/12/16
* Modifications:
*	N/A
*************************************************************************/
#ifndef TREENODE_H
#define TREENODE_H


/************************************************************************
* Class: BinaryTreeNode
*
* Purpose: This class provides data storage and convenience methods for
*			nodes in a binary tree structure ADT
*
* Manager functions:
* 	BinaryTreeNode(data : const T &)
*
*	BinaryTreeNode(copy : const BinaryTreeNode &)
*	operator = (rhs : const BinaryTreeNode &)
*
*	~BinaryTreeNode()
*
* Methods:
*
*	Data()	: T &
*
*	Left()	: BinaryTreeNode *
*
*	Right()	: BinaryTreeNode *
*
*************************************************************************/
template<typename T>
class BinaryTreeNode
{
	template<typename BT>
	friend class BinarySearchTree;

	template<typename AT>
	friend class AVLTree;

protected:
	// CTORS & DTOR
	BinaryTreeNode(const T & data);
	BinaryTreeNode(const BinaryTreeNode & copy);
	
	virtual ~BinaryTreeNode();

	// OPERATORS
	BinaryTreeNode & operator=(const BinaryTreeNode & rhs);

	// METHODS
	T & Data();
	const T & Data() const;

	BinaryTreeNode *& Left();
	const BinaryTreeNode * Left() const;

	BinaryTreeNode *& Right();
	const BinaryTreeNode * Right() const;

	// MEMBERS
	T m_data;

	BinaryTreeNode * m_left;
	BinaryTreeNode * m_right;
};


///////////////////////////////////////////////////////////////
//	C'TORS & D'TOR
//////

template<typename T>
BinaryTreeNode<T>::BinaryTreeNode(const T & data)
	: m_data(data), m_left(nullptr), m_right(nullptr)
{}

template<typename T>
BinaryTreeNode<T>::BinaryTreeNode(const BinaryTreeNode & copy)
	: m_data(copy.m_data), m_left(copy.m_left), m_right(copy.m_right)
{}

template<typename T>
BinaryTreeNode<T>::~BinaryTreeNode()
{
	m_left = nullptr;
	m_right = nullptr;
}

//////
//	END C'TORS & D'TOR
///////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////
//	OPERATORS
//////

template<typename T>
BinaryTreeNode<T> & BinaryTreeNode<T>::operator=(const BinaryTreeNode & rhs)
{
	if (this != &rhs)
	{
		m_data = rhs.m_data;
		m_left = rhs.m_left;
		m_right = rhs.m_right;
	}

	return *this;
}

//////
//	END OPERATORS
///////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////
//	PRIVATE METHODS
//////

template<typename T>
T & BinaryTreeNode<T>::Data()
{
	return m_data;
}

template<typename T>
const T & BinaryTreeNode<T>::Data() const
{
	return m_data;
}


template<typename T>
BinaryTreeNode<T> *& BinaryTreeNode<T>::Left()
{
	return m_left;
}

template<typename T>
const BinaryTreeNode<T> * BinaryTreeNode<T>::Left() const
{
	return m_left;
}


template<typename T>
BinaryTreeNode<T> *& BinaryTreeNode<T>::Right()
{
	return m_right;
}

template<typename T>
const BinaryTreeNode<T> * BinaryTreeNode<T>::Right() const
{
	return m_right;
}

//////
//	END PRIVATE METHODS
///////////////////////////////////////////////////////////////


#endif // TREENODE_H
