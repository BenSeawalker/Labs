/************************************************************************
* Author:		Garrett Fleischer
* Filename:		BinarySearchTree.h
* Date Created:	2/12/16
* Modifications:
*	N/A
*************************************************************************/
#ifndef BSTREE_H
#define BSTREE_H

#include "BinaryTreeNode.h"
#include "Exception.h"

#include "Queue.h"


/************************************************************************
* Class: BinarySearchTree
*
* Purpose: This class provides data storage in an efficient to search tree
*
* Manager functions:
* 	BinarySearchTree()
*
*	BinarySearchTree(copy : const BinarySearchTree &)
*	operator = (rhs : const BinarySearchTree &)
*
*	~BinarySearchTree()
*
* Methods:
*
*	Insert(data : const T &) : void
*
*	Delete(data : const T &) : void
*
*	Height() : int
*
*	Purge() : void
*
*	PreOrderTraversal(visit : visit_t) : void
*
*	InOrderTraversal(visit : visit_t) : void
*
*	PostOrderTraversal(visit : visit_t) : void
*
*	BreadthFirstTraversal(visit : visit_t) : void
*
*************************************************************************/
template<typename T>
class BinarySearchTree
{
public:
	typedef void(*visit_t)(T &);
	typedef void(*cvisit_t)(const T &);

	// CTORS AND DTOR
	BinarySearchTree();
	BinarySearchTree(const BinarySearchTree & copy);
	virtual ~BinarySearchTree();

	// OPERATORS
	BinarySearchTree & operator=(const BinarySearchTree & rhs);

	// METHODS
	virtual void Insert(const T & data);
	virtual void Delete(const T & data);

	int Height() const;

	void Purge();

	void PreOrderTraversal(visit_t visit);
	void PreOrderTraversal(cvisit_t visit) const;

	void InOrderTraversal(visit_t visit);
	void InOrderTraversal(cvisit_t visit) const;

	void PostOrderTraversal(visit_t visit);
	void PostOrderTraversal(cvisit_t visit) const;

	virtual void BreadthFirstTraversal(visit_t visit);
	virtual void BreadthFirstTraversal(cvisit_t visit) const;

protected:
	// METHODS
	void Insert(BinaryTreeNode<T> *& root, const T & data);
	bool Delete(BinaryTreeNode<T> *& root, const T & data);

	int Height(const BinaryTreeNode<T> * root) const;

	virtual void DeepCopy(BinaryTreeNode<T> *& root, const BinaryTreeNode<T> * copy);

	void Purge(BinaryTreeNode<T> *& root);

	void PreOrderTraversal(BinaryTreeNode<T> * root, visit_t visit);
	void PreOrderTraversal(BinaryTreeNode<T> * root, cvisit_t visit) const;

	void InOrderTraversal(BinaryTreeNode<T> * root, visit_t visit);
	void InOrderTraversal(BinaryTreeNode<T> * root, cvisit_t visit) const;

	void PostOrderTraversal(BinaryTreeNode<T> * root, visit_t visit);
	void PostOrderTraversal(BinaryTreeNode<T> * root, cvisit_t visit) const;

	// MEMBERS
	BinaryTreeNode<T> * m_root;
};


///////////////////////////////////////////////////////////////
//	C'TORS & D'TOR
//////

template<typename T>
BinarySearchTree<T>::BinarySearchTree()
	: m_root(nullptr)
{}

template<typename T>
BinarySearchTree<T>::BinarySearchTree(const BinarySearchTree & copy)
{
	DeepCopy(m_root, copy.m_root);
}

template<typename T>
BinarySearchTree<T>::~BinarySearchTree()
{
	Purge();
}

//////
//	END C'TORS & D'TOR
///////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////
//	OPERATORS
//////

template<typename T>
BinarySearchTree<T> & BinarySearchTree<T>::operator=(const BinarySearchTree & rhs)
{
	if (this != &rhs)
	{
		Purge();
		DeepCopy(m_root, rhs.m_root);
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
* Purpose: Wrapper around private recursive insert
*
* Precondition:
*
* Postcondition:
*		Modifies:	Nodes in the tree
*		Throws:		N/A
*		Returns:	N/A
*************************************************************************/
template<typename T>
void BinarySearchTree<T>::Insert(const T & data)
{
	Insert(m_root, data);
}

/************************************************************************
* Purpose: Wrapper around private recursive delete
*
* Precondition:
*
* Postcondition:
*		Modifies:	Nodes in the tree
*		Throws:	Exception("Tree is empty!")
*				Exception("Data not found!")
*		Returns:	N/A
*************************************************************************/
template<typename T>
void BinarySearchTree<T>::Delete(const T & data)
{
	if (m_root == nullptr)
		throw Exception("Tree is empty!");

	if (!Delete(m_root, data))
		throw Exception("Data not found!");
}

/************************************************************************
* Purpose: Wrapper around private recursive height
*
* Precondition:
*
* Postcondition:
*		Modifies:	N/A
*		Throws:		N/A
*		Returns:	The height of the tree
*************************************************************************/
template<typename T>
int BinarySearchTree<T>::Height() const
{
	return Height(m_root);
}

/************************************************************************
* Purpose: Wrapper around private recursive purge
*
* Precondition:
*
* Postcondition:
*		Modifies:	All nodes in the tree
*		Throws:		N/A
*		Returns:	N/A
*************************************************************************/
template<typename T>
void BinarySearchTree<T>::Purge()
{
	Purge(m_root);
}

/************************************************************************
* Purpose: Wrapper around private recursive pre-order traversal
*
* Precondition:
*
* Postcondition:
*		Modifies:	N/A
*		Throws:		N/A
*		Returns:	N/A
*************************************************************************/
template<typename T>
void BinarySearchTree<T>::PreOrderTraversal(visit_t visit)
{
	PreOrderTraversal(m_root, visit);
}

template<typename T>
void BinarySearchTree<T>::PreOrderTraversal(cvisit_t visit) const
{
	PreOrderTraversal(m_root, visit);
}

/************************************************************************
* Purpose: Wrapper around private recursive in-order traversal
*
* Precondition:
*
* Postcondition:
*		Modifies:	N/A
*		Throws:		N/A
*		Returns:	N/A
*************************************************************************/
template<typename T>
void BinarySearchTree<T>::InOrderTraversal(visit_t visit)
{
	InOrderTraversal(m_root, visit);
}

template<typename T>
void BinarySearchTree<T>::InOrderTraversal(cvisit_t visit) const
{
	InOrderTraversal(m_root, visit);
}

/************************************************************************
* Purpose: Wrapper around private recursive post-order traversal
*
* Precondition:
*
* Postcondition:
*		Modifies:	N/A
*		Throws:		N/A
*		Returns:	N/A
*************************************************************************/
template<typename T>
void BinarySearchTree<T>::PostOrderTraversal(visit_t visit)
{
	PostOrderTraversal(m_root, visit);
}

template<typename T>
void BinarySearchTree<T>::PostOrderTraversal(cvisit_t visit) const
{
	PostOrderTraversal(m_root, visit);
}

/************************************************************************
* Purpose: To "visit" all items in the tree in a breadth-first manner
*
* Precondition:
*
* Postcondition:
*		Modifies:	N/A
*		Throws:		N/A
*		Returns:	N/A
*************************************************************************/
template<typename T>
void BinarySearchTree<T>::BreadthFirstTraversal(visit_t visit)
{
	Queue<BinaryTreeNode<T> *> nodes;
	nodes.Enqueue(m_root);

	while (nodes.Size() > 0)
	{
		BinaryTreeNode<T> * node = nodes.Dequeue();

		if (node)
		{
			visit(node->Data());
			nodes.Enqueue(node->Left());
			nodes.Enqueue(node->Right());
		}
	}
}

template<typename T>
void BinarySearchTree<T>::BreadthFirstTraversal(cvisit_t visit) const
{
	Queue<BinaryTreeNode<T> *> nodes;
	nodes.Enqueue(m_root);

	while (nodes.Size() > 0)
	{
		BinaryTreeNode<T> * node = nodes.Dequeue();

		if (node)
		{
			visit(node->Data());
			nodes.Enqueue(node->Left());
			nodes.Enqueue(node->Right());
		}
	}
}

//////
//	END PUBLIC METHODS
///////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////
//	PROTECTED METHODS
//////

/************************************************************************
* Purpose: Recursive method of inserting a node in the tree
*
* Precondition:
*
* Postcondition:
*		Modifies:	m_root
*		Throws:		N/A
*		Returns:	N/A
*************************************************************************/
template<typename T>
void BinarySearchTree<T>::Insert(BinaryTreeNode<T> *& root, const T & data)
{
	if (root == nullptr)
		root = new BinaryTreeNode<T>(data);
	else if (data <= root->Data())
		Insert(root->Left(), data);
	else
		Insert(root->Right(), data);
}

/************************************************************************
* Purpose: Recursive method of removing a node from the tree
*
* Precondition:
*
* Postcondition:
*		Modifies:	m_root
*		Throws:		N/A
*		Returns:	TRUE if @data was found in the tree
*************************************************************************/
template<typename T>
bool BinarySearchTree<T>::Delete(BinaryTreeNode<T> *& root, const T & data)
{
	bool success = false;

	if (root != nullptr)
	{
		if (root->Data() == data)
		{
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
				Delete(root->Left(), data);
			}

			// Case 3
			else if(root->Left())
			{
				BinaryTreeNode<T> * left = root->Left();
				delete root;
				root = left;
			}

			// Case 2
			else if(root->Right())
			{
				BinaryTreeNode<T> * right = root->Right();
				delete root;
				root = right;
			}

			// Case 1
			else
			{
				delete root;
				root = nullptr;
			}
		}
		else
		{
			// more efficient to go right first due to Case 4
			success = (Delete(root->Right(), data) || Delete(root->Left(), data));
		}
	}

	return success;
}


/************************************************************************
* Purpose: Recursive method of getting the height of the tree from the given node
*
* Precondition:
*
* Postcondition:
*		Modifies:	N/A
*		Throws:		N/A
*		Returns:	The height of the tree
*************************************************************************/
template<typename T>
int BinarySearchTree<T>::Height(const BinaryTreeNode<T> * root) const
{
	int height = 0;

	if (root)
	{
		int lheight;
		int rheight;

		height = (root->Left() || root->Right());

		lheight = Height(root->Left());
		rheight = Height(root->Right());

		height += ((lheight > rheight) ? lheight : rheight);
	}

	return height;
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
void BinarySearchTree<T>::DeepCopy(BinaryTreeNode<T> *& root, const BinaryTreeNode<T> * copy)
{
	if (copy)
	{
		root = new BinaryTreeNode<T>(copy->Data());

		DeepCopy(root->Left(), copy->Left());
		DeepCopy(root->Right(), copy->Right());
	}
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
void BinarySearchTree<T>::Purge(BinaryTreeNode<T> *& root)
{
	if (root)
	{
		Purge(root->Left());
		Purge(root->Right());

		delete root;
		root = nullptr;
	}
}


/************************************************************************
* Purpose: Recursive method of traversing the tree in a pre-order manner
*
* Precondition:
*
* Postcondition:
*		Modifies:	m_root
*		Throws:		N/A
*		Returns:	N/A
*************************************************************************/
template<typename T>
void BinarySearchTree<T>::PreOrderTraversal(BinaryTreeNode<T> * root, visit_t visit)
{
	if (root)
	{
		visit(root->Data());
		PreOrderTraversal(root->Left(), visit);
		PreOrderTraversal(root->Right(), visit);
	}
}

template<typename T>
void BinarySearchTree<T>::PreOrderTraversal(BinaryTreeNode<T>* root, cvisit_t visit) const
{
	if (root)
	{
		visit(root->Data());
		PreOrderTraversal(root->Left(), visit);
		PreOrderTraversal(root->Right(), visit);
	}
}

/************************************************************************
* Purpose: Recursive method of traversing the tree in an in-order manner
*
* Precondition:
*
* Postcondition:
*		Modifies:	m_root
*		Throws:		N/A
*		Returns:	N/A
*************************************************************************/
template<typename T>
void BinarySearchTree<T>::InOrderTraversal(BinaryTreeNode<T> * root, visit_t visit)
{
	if (root)
	{
		InOrderTraversal(root->Left(), visit);
		visit(root->Data());
		InOrderTraversal(root->Right(), visit);
	}
}

template<typename T>
void BinarySearchTree<T>::InOrderTraversal(BinaryTreeNode<T>* root, cvisit_t visit) const
{
	if (root)
	{
		InOrderTraversal(root->Left(), visit);
		visit(root->Data());
		InOrderTraversal(root->Right(), visit);
	}
}

/************************************************************************
* Purpose: Recursive method of traversing the tree in a post-order manner
*
* Precondition:
*
* Postcondition:
*		Modifies:	m_root
*		Throws:		N/A
*		Returns:	N/A
*************************************************************************/
template<typename T>
void BinarySearchTree<T>::PostOrderTraversal(BinaryTreeNode<T> * root, visit_t visit)
{
	if (root)
	{
		PostOrderTraversal(root->Left(), visit);
		PostOrderTraversal(root->Right(), visit);
		visit(root->Data());
	}
}

template<typename T>
void BinarySearchTree<T>::PostOrderTraversal(BinaryTreeNode<T>* root, cvisit_t visit) const
{
	if (root)
	{
		PostOrderTraversal(root->Left(), visit);
		PostOrderTraversal(root->Right(), visit);
		visit(root->Data());
	}
}

//////
//	END PROTECTED METHODS
///////////////////////////////////////////////////////////////

#endif // BSTREE_H
