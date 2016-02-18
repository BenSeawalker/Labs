#ifndef AVLTREE_H
#define AVLTREE_H


#include "BinarySearchTree.h"
#include "AVLTreeNode.h"

template<typename T>
class AVLTree : public BinarySearchTree<T>
{
public:
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
};



template<typename T>
void AVLTree<T>::Insert(const T & data)
{
	bool taller = false;
	Insert(m_root, data, taller);
}

template<typename T>
void AVLTree<T>::Delete(const T & data)
{
	bool shorter = false;
	if (!Delete(m_root, data, shorter))
		shorter = true;
		//throw Exception("Node to delete not found!");
}

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

template<typename T>
bool AVLTree<T>::Delete(BinaryTreeNode<T>*& root, const T & data, bool & shorter)
{
	bool success = false;

	if (root == nullptr)
	{
		shorter = false;
	}
	else if (data < root->Data())
	{
		success = Delete(root->Left(), data, shorter);

		if (shorter)
			DeleteRightBalance(root, shorter);
	}
	else if (data > root->Data())
	{
		success = Delete(root->Right(), data, shorter);

		if (shorter)
			DeleteLeftBalance(root, shorter);
	}
	else
	{
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

template<typename T>
void AVLTree<T>::DeleteLeftBalance(BinaryTreeNode<T>*& root, bool & shorter)
{
	AVLTreeNode<T> * _root = dynamic_cast<AVLTreeNode<T> *>(root);
	AVLTreeNode<T> * left;// = dynamic_cast<AVLTreeNode<T> *>(root->Left());
	AVLTreeNode<T> * right;// = dynamic_cast<AVLTreeNode<T> *>(left->Right());

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
				left->Balance() = RH;
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


#endif // AVLTREE_H