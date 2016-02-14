#ifndef BSTREE_H
#define BSTREE_H

#include "crtdbg_new.h"

#include "TreeNode.h"
#include "Exception.h"

#include "Queue.h"

template<typename T>
class BSTree
{
public:
	typedef void(*visit_t)(T &);

	// CTORS AND DTOR
	BSTree();
	BSTree(const BSTree & copy);
	~BSTree();

	// OPERATORS
	BSTree & operator=(const BSTree & rhs);

	// METHODS
	void Insert(const T & data);
	void Delete(const T & data);

	int Height() const;

	void Purge();

	void PreOrderTraversal(visit_t visit);
	void InOrderTraversal(visit_t visit);
	void PostOrderTraversal(visit_t visit);
	void BreadthFirstTraversal(visit_t visit);

private:
	// METHODS
	void Insert(TreeNode<T> *& root, const T & data);
	bool Delete(TreeNode<T> *& root, const T & data);

	int Height(const TreeNode<T> * root) const;

	void DeepCopy(TreeNode<T> *& root, const TreeNode<T> * copy);

	void Purge(TreeNode<T> *& root);

	void PreOrderTraversal(TreeNode<T> * root, visit_t visit);
	void InOrderTraversal(TreeNode<T> * root, visit_t visit);
	void PostOrderTraversal(TreeNode<T> * root, visit_t visit);

	// MEMBERS
	TreeNode<T> * m_root;
};


///////////////////////////////////////////////////////////////
//	C'TORS & D'TOR
//////

template<typename T>
BSTree<T>::BSTree()
	: m_root(nullptr)
{}

template<typename T>
BSTree<T>::BSTree(const BSTree & copy)
{
	DeepCopy(m_root, copy.m_root);
}

template<typename T>
BSTree<T>::~BSTree()
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
BSTree<T> & BSTree<T>::operator=(const BSTree & rhs)
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

template<typename T>
void BSTree<T>::Insert(const T & data)
{
	Insert(m_root, data);
}

template<typename T>
void BSTree<T>::Delete(const T & data)
{
	if (m_root == nullptr)
		throw Exception("List is empty!");

	if (!Delete(m_root, data))
		throw Exception("Data not found!");
}

template<typename T>
int BSTree<T>::Height() const
{
	return Height(m_root);
}

template<typename T>
void BSTree<T>::Purge()
{
	Purge(m_root);
}

template<typename T>
void BSTree<T>::PreOrderTraversal(visit_t visit)
{
	PreOrderTraversal(m_root, visit);
}

template<typename T>
void BSTree<T>::InOrderTraversal(visit_t visit)
{
	InOrderTraversal(m_root, visit);
}

template<typename T>
void BSTree<T>::PostOrderTraversal(visit_t visit)
{
	PostOrderTraversal(m_root, visit);
}

template<typename T>
void BSTree<T>::BreadthFirstTraversal(visit_t visit)
{
	Queue<TreeNode<T> *> nodes;
	nodes.Enqueue(m_root);

	while (nodes.Size() > 0)
	{
		TreeNode<T> * node = nodes.Dequeue();

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
//	PRIVATE METHODS
//////

template<typename T>
void BSTree<T>::Insert(TreeNode<T> *& root, const T & data)
{
	if (root == nullptr)
		root = new TreeNode<T>(data);
	else if (data < root->Data())
		Insert(root->Left(), data);
	else
		Insert(root->Right(), data);
}

template<typename T>
bool BSTree<T>::Delete(TreeNode<T> *& root, const T & data)
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
				TreeNode<T> * rightmost = root->Left();
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
				TreeNode<T> * left = root->Left();
				delete root;
				root = left;
			}

			// Case 2
			else if(root->Right())
			{
				TreeNode<T> * right = root->Right();
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
			success = Delete(root->Right(), data);
			if(!success)
				success = Delete(root->Left(), data);
		}
	}

	return success;
}


template<typename T>
int BSTree<T>::Height(const TreeNode<T> * root) const
{
	int height = 0;

	if (root)
	{
		int lheight;
		int rheight;

		height = (root->Left() || root->Right());

		lheight = height + Height(root->Left());
		rheight = height + Height(root->Right());

		height = ((lheight > rheight) ? lheight : rheight);
	}

	return height;
}

template<typename T>
void BSTree<T>::DeepCopy(TreeNode<T> *& root, const TreeNode<T> * copy)
{
	if (copy)
	{
		root = new TreeNode<T>(copy->Data());

		DeepCopy(root->Left(), copy->Left());
		DeepCopy(root->Right(), copy->Right());
	}
}

template<typename T>
void BSTree<T>::Purge(TreeNode<T> *& root)
{
	if (root)
	{
		Purge(root->Left());
		Purge(root->Right());

		delete root;
		root = nullptr;
	}
}


template<typename T>
void BSTree<T>::PreOrderTraversal(TreeNode<T> * root, visit_t visit)
{
	if (root)
	{
		visit(root->Data());
		PreOrderTraversal(root->Left(), visit);
		PreOrderTraversal(root->Right(), visit);
	}
}

template<typename T>
void BSTree<T>::InOrderTraversal(TreeNode<T> * root, visit_t visit)
{
	if (root)
	{
		InOrderTraversal(root->Left(), visit);
		visit(root->Data());
		InOrderTraversal(root->Right(), visit);
	}
}

template<typename T>
void BSTree<T>::PostOrderTraversal(TreeNode<T> * root, visit_t visit)
{
	if (root)
	{
		PostOrderTraversal(root->Left(), visit);
		PostOrderTraversal(root->Right(), visit);
		visit(root->Data());
	}
}

//////
//	END PRIVATE METHODS
///////////////////////////////////////////////////////////////

#endif // BSTREE_H
