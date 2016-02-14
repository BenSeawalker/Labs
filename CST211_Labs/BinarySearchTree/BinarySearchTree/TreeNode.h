#ifndef TREENODE_H
#define TREENODE_H

template<typename T>
class TreeNode
{
	template<typename BT>
	friend class BSTree;

public:
	T & Data();
	const T & Data() const;

	TreeNode *& Left();
	const TreeNode * Left() const;

	TreeNode *& Right();
	const TreeNode * Right() const;
	
protected:
	TreeNode(const T & data);
	TreeNode(const TreeNode & copy);
	~TreeNode();

	TreeNode & operator=(const TreeNode & rhs);

private:
	T m_data;

	TreeNode * m_left;
	TreeNode * m_right;
};



template<typename T>
TreeNode<T>::TreeNode(const T & data)
	: m_data(data), m_left(nullptr), m_right(nullptr)
{}

template<typename T>
TreeNode<T>::TreeNode(const TreeNode & copy)
	: m_data(copy.m_data), m_left(copy.m_left), m_right(copy.m_right)
{}

template<typename T>
TreeNode<T>::~TreeNode()
{}

template<typename T>
TreeNode<T> & TreeNode<T>::operator=(const TreeNode & rhs)
{
	if (this != &rhs)
	{
		m_data = rhs.m_data;
		m_left = rhs.m_left;
		m_right = rhs.m_right;
	}

	return *this;
}


template<typename T>
T & TreeNode<T>::Data()
{
	return m_data;
}

template<typename T>
const T & TreeNode<T>::Data() const
{
	return m_data;
}


template<typename T>
TreeNode<T> *& TreeNode<T>::Left()
{
	return m_left;
}

template<typename T>
const TreeNode<T> * TreeNode<T>::Left() const
{
	return m_left;
}


template<typename T>
TreeNode<T> *& TreeNode<T>::Right()
{
	return m_right;
}

template<typename T>
const TreeNode<T> * TreeNode<T>::Right() const
{
	return m_right;
}

#endif // TREENODE_H
