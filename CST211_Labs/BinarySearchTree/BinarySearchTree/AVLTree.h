/************************************************************************
* Author:		Garrett Fleischer
* Filename:		AVLTree.h
* Date Created:	2/15/16
* Modifications:
*	N/A
*************************************************************************/
#ifndef AVLTREE_H
#define AVLTREE_H


#include "BinarySearchTree.h"
#include "AVLTreeNode.h"


/************************************************************************
* Class: AVLTree
*
* Purpose: This class provides data storage in a balanced BinarySearchTree
*
* Manager functions:
* 	AVLTree()
*
*	AVLTree(copy : const AVLTree &)
*	operator = (rhs : const AVLTree &)
*
*	~AVLTree()
*
* Methods:
*
*	Insert(data : const T &) : void
*
*	Delete(data : const T &) : void
*
* Inherited from BinarySearchTree :
*
*		Height() : int
*
*		Purge() : void
*
*		PreOrderTraversal(visit : visit_t) : void
*
*		InOrderTraversal(visit : visit_t) : void
*
*		PostOrderTraversal(visit : visit_t) : void
*
*		BreadthFirstTraversal(visit : visit_t) : void
*
*************************************************************************/
template<typename T>
class AVLTree : public BinarySearchTree<T>
{
public:
	AVLTree();
	AVLTree(const AVLTree<T> & copy);

	virtual ~AVLTree();

	AVLTree<T> & operator=(const AVLTree<T> & rhs);


	virtual void Insert(const T & data);
	virtual void Delete(const T & data);

protected:
	void Insert(BinaryTreeNode<T> *& root, const T & data, bool & taller);

	bool Delete(BinaryTreeNode<T> *& root, const T & data, bool & shorter);

	void LeftBalance(BinaryTreeNode<T> *& root, bool & taller);
	void RightBalance(BinaryTreeNode<T> *& root, bool & taller);

	void DeleteRightBalance(BinaryTreeNode<T> *& root, bool & shorter);
	void DeleteLeftBalance(BinaryTreeNode<T> *& root, bool & shorter);

	void RotateRight(BinaryTreeNode<T> *& root);
	void RotateLeft(BinaryTreeNode<T> *& root);

	virtual void DeepCopy(BinaryTreeNode<T> *& root, const BinaryTreeNode<T> * copy);
};


///////////////////////////////////////////////////////////////
//	C'TORS & D'TOR
//////

template<typename T>
AVLTree<T>::AVLTree()
{}

template<typename T>
AVLTree<T>::AVLTree(const AVLTree<T>& copy)
{
	DeepCopy(m_root, copy.m_root);
}

template<typename T>
AVLTree<T>::~AVLTree()
{
	Purge(m_root);
}

//////
//	END C'TORS & D'TOR
///////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////
//	OPERATORS
//////

template<typename T>
AVLTree<T>& AVLTree<T>::operator=(const AVLTree<T>& rhs)
{
	if (this != &rhs)
	{
		BinarySearchTree<T>::operator=(rhs);
	}

	return *this;
}

//////
//	END OPERATORS
///////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////
//	PUBLIC METHODS
//////

/************************************************************************
* Purpose: Public wrapper around recursive Insert()
*
* Precondition:
*
* Postcondition:
*		Modifies:	N/A
*		Throws:		N/A
*		Returns:	N/A
*************************************************************************/
template<typename T>
void AVLTree<T>::Insert(const T & data)
{
	bool taller = false;
	Insert(m_root, data, taller);
}


/************************************************************************
* Purpose: Public wrapper around recursive Delete()
*
* Precondition:
*
* Postcondition:
*		Modifies:	N/A
*		Throws:	Exception("Node to delete not found!")
*		Returns:	N/A
*************************************************************************/
template<typename T>
void AVLTree<T>::Delete(const T & data)
{
	bool shorter = false;
	if (!Delete(m_root, data, shorter))
		throw Exception("Node to delete not found!");
}

//////
//	END PUBLIC METHODS
///////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////
//	PROTECTED METHODS
//////

/************************************************************************
* Purpose: Recursively find and insert the given data into the tree
*
* Precondition:
*
* Postcondition:
*		Modifies:	root, taller
*		Throws:		N/A
*		Returns:	N/A
*************************************************************************/
template<typename T>
void AVLTree<T>::Insert(BinaryTreeNode<T> *& root, const T & data, bool & taller)
{
	if (root == nullptr)
	{
		root = new AVLTreeNode<T>(data);
		taller = true;
	}
	else if (data <= root->Data())
	{
		Insert(root->Left(), data, taller);

		if (taller)
		{
			AVLTreeNode<T> * _root = dynamic_cast<AVLTreeNode<T> *>(root);
			switch (_root->Balance())
			{
			case LH:
				LeftBalance(root, taller);
				break;

			case EH:
				_root->Balance() = LH;
				break;

			case RH:
				_root->Balance() = EH;
				taller = false;
				break;
			}
		}
	}
	else
	{
		Insert(root->Right(), data, taller);

		if (taller)
		{
			AVLTreeNode<T> * _root = dynamic_cast<AVLTreeNode<T> *>(root);
			switch (_root->Balance())
			{
			case LH:
				_root->Balance() = EH;
				taller = false;
				break;

			case EH:
				_root->Balance() = RH;
				break;

			case RH:
				RightBalance(root, taller);
				break;
			}
		}
	}
}


/************************************************************************
* Purpose: Recursively find and remove the given data from the tree
*
* Precondition:
*
* Postcondition:
*		Modifies:	root, shorter
*		Throws:		N/A
*		Returns:	TRUE if a matching node was found
*************************************************************************/
template<typename T>
bool AVLTree<T>::Delete(BinaryTreeNode<T>*& root, const T & data, bool & shorter)
{
	bool success = false;

	// not found
	if (root == nullptr)
	{
		shorter = false;
	}
	// left
	else if (data < root->Data())
	{
		success = Delete(root->Left(), data, shorter);

		if (shorter)
			DeleteRightBalance(root, shorter);
	}
	// right
	else if (data > root->Data())
	{
		success = Delete(root->Right(), data, shorter);

		if (shorter)
			DeleteLeftBalance(root, shorter);
	}
	// found
	else
	{
		// We found a matching node!
		success = true;

		// Case 4
		if (root->Left() && root->Right())
		{
			// find left-rightmost data
			BinaryTreeNode<T> * rightmost = root->Left();
			while (rightmost->Right())
				rightmost = rightmost->Right();

			// swap with root
			// temp swap var not necessary because @data is already equivalent to @root->m_data
			root->Data() = rightmost->Data();
			rightmost->Data() = data;

			// @data is now in the left-rightmost node
			// so handle Case 1 or Case 3 on it
			success = Delete(root->Left(), data, shorter);

			if (shorter)
				DeleteRightBalance(root, shorter);
		}

		// Case 3
		else if (root->Left())
		{
			shorter = true;

			BinaryTreeNode<T> * left = root->Left();
			delete root;
			root = left;
		}

		// Case 2
		else if (root->Right())
		{
			shorter = true;

			BinaryTreeNode<T> * right = root->Right();
			delete root;
			root = right;
		}

		// Case 1
		else
		{
			shorter = true;

			delete root;
			root = nullptr;
		}
	}

	return success;
}


/************************************************************************
* Purpose: Update balances and rotate the tree after a node has been inserted
*
* Precondition:
*
* Postcondition:
*		Modifies:	root, taller
*		Throws:		N/A
*		Returns:	N/A
*************************************************************************/
template<typename T>
void AVLTree<T>::LeftBalance(BinaryTreeNode<T> *& root, bool & taller)
{
	AVLTreeNode<T> * _root = dynamic_cast<AVLTreeNode<T> *>(root);
	AVLTreeNode<T> * left = dynamic_cast<AVLTreeNode<T> *>(root->Left());
	AVLTreeNode<T> * right = dynamic_cast<AVLTreeNode<T> *>(left->Right());

	// LL rotation
	if (left->Balance() == LH)
	{
		RotateRight(root);

		_root->Balance() = EH;
		left->Balance() = EH;

		taller = false;
	}

	// LR rotation
	else
	{
		switch (right->Balance())
		{
		case LH:
			_root->Balance() = RH;
			left->Balance() = EH;
			break;

		case EH:
			left->Balance() = EH;
			break;

		case RH:
			_root->Balance() = EH;
			left->Balance() = LH;
			break;
		}

		right->Balance() = EH;

		RotateLeft(root->Left());
		RotateRight(root);

		taller = false;
	}
}


/************************************************************************
* Purpose: Update balances and rotate the tree after a node has been inserted
*
* Precondition:
*
* Postcondition:
*		Modifies:	root, taller
*		Throws:		N/A
*		Returns:	N/A
*************************************************************************/
template<typename T>
void AVLTree<T>::RightBalance(BinaryTreeNode<T> *& root, bool & taller)
{
	AVLTreeNode<T> * _root = dynamic_cast<AVLTreeNode<T> *>(root);
	AVLTreeNode<T> * right = dynamic_cast<AVLTreeNode<T> *>(root->Right());
	AVLTreeNode<T> * left = dynamic_cast<AVLTreeNode<T> *>(right->Left());

	// RR rotation
	if (right->Balance() == RH)
	{
		RotateLeft(root);

		_root->Balance() = EH;
		right->Balance() = EH;

		taller = false;
	}

	// RL rotation
	else
	{
		switch (left->Balance())
		{
		case LH:
			_root->Balance() = EH;
			right->Balance() = RH;
			break;

		case EH:
			right->Balance() = EH;
			break;

		case RH:
			_root->Balance() = LH;
			right->Balance() = EH;
			break;
		}

		left->Balance() = EH;

		RotateRight(root->Right());
		RotateLeft(root);

		taller = false;
	}
}


/************************************************************************
* Purpose: Update balances and rotate the tree after a node has been deleted
*
* Precondition:
*
* Postcondition:
*		Modifies:	root, shorter
*		Throws:		N/A
*		Returns:	N/A
*************************************************************************/
template<typename T>
void AVLTree<T>::DeleteRightBalance(BinaryTreeNode<T>*& root, bool & shorter)
{
	AVLTreeNode<T> * _root = dynamic_cast<AVLTreeNode<T> *>(root);
	AVLTreeNode<T> * right;// = dynamic_cast<AVLTreeNode<T> *>(root->Right());
	AVLTreeNode<T> * left;// = dynamic_cast<AVLTreeNode<T> *>(right->Left());

	switch(_root->Balance())
	{
	case LH:
		_root->Balance() = EH;
		break;

	case EH:
		_root->Balance() = RH;
		shorter = false;
		break;

	case RH:
		right = dynamic_cast<AVLTreeNode<T> *>(root->Right());
		// RL rotation
		if (right->Balance() == LH)
		{
			left = dynamic_cast<AVLTreeNode<T> *>(right->Left());
			// Left
			switch (left->Balance())
			{
			case LH:
				_root->Balance() = EH;
				right->Balance() = RH;
				break;

			case EH:
				_root->Balance() = LH;
				right->Balance() = EH;
				break;

			case RH:
				_root->Balance() = LH;
				right->Balance() = EH;
				break;
			}

			left->Balance() = EH;

			RotateRight(root->Right());
			RotateLeft(root);
		}

		// RR rotation
		else
		{
			switch (right->Balance())
			{
			case  EH:
				_root->Balance() = RH;
				right->Balance() = LH;
				shorter = false;
				break;

			case  RH:
				_root->Balance() = EH;
				right->Balance() = EH;
				break;
			}

			RotateLeft(root);
		}
		break;
	}
}


/************************************************************************
* Purpose: Update balances and rotate the tree after a node has been deleted
*
* Precondition:
*
* Postcondition:
*		Modifies:	root, shorter
*		Throws:		N/A
*		Returns:	N/A
*************************************************************************/
template<typename T>
void AVLTree<T>::DeleteLeftBalance(BinaryTreeNode<T>*& root, bool & shorter)
{
	AVLTreeNode<T> * _root = dynamic_cast<AVLTreeNode<T> *>(root);
	AVLTreeNode<T> * left;
	AVLTreeNode<T> * right;

	switch (_root->Balance())
	{
	case LH:
		left = dynamic_cast<AVLTreeNode<T> *>(root->Left());
		// LR rotation
		if (left->Balance() == RH)
		{
			right = dynamic_cast<AVLTreeNode<T> *>(left->Right());
			// Left
			switch (right->Balance())
			{
			case LH:
				_root->Balance() = RH;
				left->Balance() = EH;
				break;

			case EH:
				_root->Balance() = EH;
				left->Balance() = EH;
				break;

			case RH:
				_root->Balance() = EH;
				left->Balance() = LH;
				break;
			}

			right->Balance() = EH;

			RotateLeft(root->Left());
			RotateRight(root);
		}

		// LL rotation
		else
		{
			switch (left->Balance())
			{
			case  LH:
				_root->Balance() = EH;
				left->Balance() = EH;
				break;

			case  EH:
				_root->Balance() = LH;
				left->Balance() = RH;
				shorter = false;
				break;
			}

			RotateRight(root);
		}
		break;

	case EH:
		_root->Balance() = LH;
		shorter = false;
		break;

	case RH:
		_root->Balance() = EH;
		break;
	}
}

/************************************************************************
* Purpose: Rotate nodes right from the given root
*
* Precondition:
*
* Postcondition:
*		Modifies:	root
*		Throws:		N/A
*		Returns:	N/A
*************************************************************************/
template<typename T>
void AVLTree<T>::RotateRight(BinaryTreeNode<T> *& root)
{
	BinaryTreeNode<T> * parent = root;
	BinaryTreeNode<T> * child = root->Left();
	BinaryTreeNode<T> * T2 = child->Right();

	root = child;
	child->Right() = parent;
	parent->Left() = T2;
}


/************************************************************************
* Purpose: Rotate nodes left from the given root
*
* Precondition:
*
* Postcondition:
*		Modifies:	root
*		Throws:		N/A
*		Returns:	N/A
*************************************************************************/
template<typename T>
void AVLTree<T>::RotateLeft(BinaryTreeNode<T> *& root)
{
	BinaryTreeNode<T> * parent = root;
	BinaryTreeNode<T> * child = root->Right();
	BinaryTreeNode<T> * T2 = child->Left();

	root = child;
	child->Left() = parent;
	parent->Right() = T2;
}


/************************************************************************
* Purpose: Recursive method of copying all data from another tree
*
* Precondition:
*
* Postcondition:
*		Modifies:	m_root
*		Throws:		N/A
*		Returns:	N/A
*************************************************************************/
template<typename T>
void AVLTree<T>::DeepCopy(BinaryTreeNode<T> *& root, const BinaryTreeNode<T> * copy)
{
	if (copy)
	{
		const AVLTreeNode<T> * _copy = dynamic_cast<const AVLTreeNode<T> *>(copy);
		root = new AVLTreeNode<T>(*_copy);
		root->Left() = nullptr;
		root->Right() = nullptr;

		DeepCopy(root->Left(), copy->Left());
		DeepCopy(root->Right(), copy->Right());
	}
}

//////
//	END PROTECTED METHODS
///////////////////////////////////////////////////////////////

#endif // AVLTREE_H