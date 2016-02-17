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

	void LeftBalance(BinaryTreeNode<T> *& root);
	void RightBalance(BinaryTreeNode<T> *& root);

	void BalanceLL(BinaryTreeNode<T> *& root);
	void BalanceRR(BinaryTreeNode<T> *& root);
	void BalanceRL(BinaryTreeNode<T> *& root);
	void BalanceLR(BinaryTreeNode<T> *& root);
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
				LeftBalance(root);
				break;

			case EH:
				_root->Balance() = LH;
				break;

			case RH:
				_root->Balance() = EH;
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
				break;

			case EH:
				_root->Balance() = RH;
				break;

			case RH:
				RightBalance(root);
				break;
			}
		}
	}
}

template<typename T>
void AVLTree<T>::LeftBalance(BinaryTreeNode<T>*& root)
{
	int balance = (Height(root->Left()) - Height(root->Right()));
	if (abs(balance) > 1)
	{
		if (dynamic_cast<AVLTreeNode<T> *>(root->Left())->Balance() < 0)
		{
			BalanceLL(root);
		}
		else
		{
			BalanceLR(root);
		}
	}
}

template<typename T>
void AVLTree<T>::RightBalance(BinaryTreeNode<T>*& root)
{
	int balance = ((Height(root->Left()) + root->Left() - Height(root->Right()));
	if (abs(balance) > 1)
	{
		if (dynamic_cast<AVLTreeNode<T> *>(root->Right())->Balance() > 0)
		{
			BalanceRR(root);
		}
		else
		{
			BalanceRL(root);
		}
	}
}

template<typename T>
void AVLTree<T>::BalanceLL(BinaryTreeNode<T> *& root)
{
	BinaryTreeNode<T> * parent = root;
	BinaryTreeNode<T> * child = root->Left();
	BinaryTreeNode<T> * T2 = child->Right();

	root = child;
	child->Right() = parent;
	parent->Left() = T2;

	int balance = Height(parent->Left()) - Height(parent->Right());
	dynamic_cast<AVLTreeNode<T> *>(parent)->SetBalance(balance);

	// CHILD
	balance = Height(child->Left()) - Height(child->Right());
	dynamic_cast<AVLTreeNode<T> *>(child)->SetBalance(balance);

	// T2
	if (T2)
	{
		balance = Height(T2->Left()) - Height(T2->Right());
		dynamic_cast<AVLTreeNode<T> *>(T2)->SetBalance(balance);
	}
}

template<typename T>
void AVLTree<T>::BalanceRR(BinaryTreeNode<T> *& root)
{
	BinaryTreeNode<T> * parent = root;
	BinaryTreeNode<T> * child = root->Right();
	BinaryTreeNode<T> * T2 = child->Left();

	root = child;
	child->Left() = parent;
	parent->Right() = T2;

	// recalculate balances
	// ROOT
	int balance = Height(parent->Left()) - Height(parent->Right());
	dynamic_cast<AVLTreeNode<T> *>(parent)->SetBalance(balance);

	// CHILD
	balance = Height(child->Left()) - Height(child->Right());
	dynamic_cast<AVLTreeNode<T> *>(child)->SetBalance(balance);

	// T2
	if (T2)
	{
		balance = Height(T2->Left()) - Height(T2->Right());
		dynamic_cast<AVLTreeNode<T> *>(T2)->SetBalance(balance);
	}
}

template<typename T>
void AVLTree<T>::BalanceRL(BinaryTreeNode<T>*& root)
{
	BalanceLL(root->Right());
	BalanceRR(root);
}

template<typename T>
void AVLTree<T>::BalanceLR(BinaryTreeNode<T>*& root)
{
	BalanceRR(root->Left());
	BalanceLL(root);
}


#endif // AVLTREE_H