/*
@Author: Garrett Fleischer
@Date:	 10/18/15
*/

#ifndef LINKEDLIST_H
#define LINKEDLIST_H


template<typename DT>
struct Node
{
public:
	Node() : data(nullptr), next(nullptr), previous(nullptr) {}
	Node(DT * _data) : data(_data), next(nullptr), previous(nullptr) {}
	~Node() { delete data; }

public:
	DT * data;
	Node<DT> * next;
	Node<DT> * previous;
};


enum STATUS { NORMAL, EMPTY_LIST, KEY_NOT_FOUND };


/************************************************************************
* Class: LinkedList<T, KT>
*
* Purpose: This class stores multiple instances of type T in a memory efficient manner
*
* Manager functions:
* 	LinkedList ()
*
*	~LinkedList()
*
* Methods:
*	Public:
*		Insert(_item : T *) : void
*		Delete(const string & _key);
*		Delete(const Node<T> * const _node);
*		Traverse(int start_index, int end_index, void(*Visit)(T * _item));
*		Find(const string & _key);
*		FindMatches(const string & _key);
*		Size();
*	Private:
*		N/A
*
*************************************************************************/
template<typename T, typename KT>
class LinkedList
{
public:
	

public:
	LinkedList();
	virtual ~LinkedList();

public:
	virtual void Insert(T * _data);

	virtual STATUS Delete(const KT & _key);

	virtual void Traverse(void(*Visit)(T * _nodeData));

	virtual T * const Find(const KT & _key, int & _foundIndex);

	virtual int Size() { return m_size; }

	virtual const Node<T> * const Head() const { return m_head; }
	virtual const Node<T> * const Tail() const { return m_tail; }

protected:
	int m_size;
	Node<T> * m_head;
	Node<T> * m_tail;

	virtual void Insert(Node<T> * _node);
	Node<T> * const FindNode(KT _key, int & _foundIndex);

protected:

};



/////////////////////////////////////////////////////////
//	C'tor and D'tor
//////////
template<typename T, typename KT>
LinkedList<T, KT>::LinkedList()
	: m_size(0), m_head(nullptr), m_tail(nullptr)
{}


template<typename T, typename KT>
LinkedList<T, KT>::~LinkedList()
{
	Node<T> * trail = nullptr;

	while (m_head != nullptr)
	{
		trail = m_head;
		m_head = m_head->next;

		delete trail;
		--m_size;
	}
}

//////////
// END C'tor and D'tor
/////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////
//	PUBLIC METHODS
//////////

/**********************************************************************
* Purpose: This function finds the correct index in which to insert the _item
*			adds the item to a new Node and inserts it
*
* Precondition:
*		_item = the item to insert into this list
*
* Postcondition:
*		Returns N/A
*		Can Modify m_head or m_tail
*
************************************************************************/
template<typename T, typename KT>
void LinkedList<T, KT>::Insert(T * _item)
{
	Insert(new Node<T>(_item));
}

template<typename T, typename KT>
void LinkedList<T, KT>::Insert(Node<T> * _node)
{
	if (m_head == nullptr || (*(_node->data) <= *(m_head->data)))
	{
		_node->next = m_head;
		m_head = _node;

		if (m_head->next != nullptr)
			m_head->next->previous = m_head;

		if (m_tail == nullptr)
			m_tail = m_head->next;

		++m_size;
	}
	else
	{
		Node<T> * travel = m_head;
		Node<T> * trail = nullptr;

		while (travel != nullptr && (*(_node->data) > *(travel->data)))
		{
			trail = travel;
			travel = travel->next;
		}

		if (trail != nullptr)
		{
			trail->next = _node;
			_node->next = travel;

			_node->previous = trail;
			if (travel != nullptr)
				travel->previous = _node;

			if (travel == nullptr)
				m_tail = _node;

			++m_size;
		}
	}
}


/**********************************************************************
* Purpose: This function finds the item matching _key
*			and deletes the Node from the list
*
* Precondition:
*		_key = the string to match the item with
*
* Postcondition:
*		Returns a STATUS indicating successful deletion of item
*		Can Modify m_head or m_tail
*
************************************************************************/
template<typename T, typename KT>
STATUS LinkedList<T, KT>::Delete(const KT & _key)
{
	STATUS status = NORMAL;

	if (m_head == nullptr)
	{
		status = EMPTY_LIST;
	}
	else
	{
		int index;
		Node<T> * const node = FindNode(_key, index);

		if (!node)
			status = KEY_NOT_FOUND;
		else
		{
			if (node == m_head)
			{
				m_head = m_head->next;
				if (m_head)
					m_head->previous = nullptr;
			}

			else if (node == m_tail)
			{
				m_tail = m_tail->previous;
				m_tail->next = nullptr;
			}

			else
			{
				node->previous->next = node->next;
				node->next->previous = node->previous;
			}

			if (m_tail == m_head)
				m_tail = nullptr;

			delete node;
			--m_size;
		}
	}

	return status;
}


/**********************************************************************
* Purpose: This function loops through all Nodes in the list
*			calling "Visit" on the Node's data
*
* Precondition:
*		Visit = the function to perform on each item in the list
*
* Postcondition:
*		Returns N/A
*
************************************************************************/
template<typename T, typename KT>
void LinkedList<T, KT>::Traverse(void(*Visit)(T * _nodeData))
{
	Node<T> * travel = m_head;

	while (travel != nullptr)
	{
		Visit(travel->data);
		travel = travel->next;
	}
}


/**********************************************************************
* Purpose: This function finds the item matching _key
*			returns a pointer to it.
*
* Precondition:
*		_key = the type to match the item with
*
* Postcondition:
*		Returns a pointer to the item matching _key
*		_foundIndex	holds the index the item was found at
*
************************************************************************/
template<typename T, typename KT>
T * const LinkedList<T, KT>::Find(const KT & _key, int & _foundIndex)
{
	Node<T> * node = FindNode(_key, _foundIndex);
	return (node ? node->data : nullptr);
}


template<typename T, typename KT>
inline Node<T>* const LinkedList<T, KT>::FindNode(KT _key, int & _foundIndex)
{
	Node<T> * travel = m_head;
	Node<T> * found = nullptr;

	int index = -1;
	while (travel != nullptr && found == nullptr)
	{
		++index;
		if (*(travel->data) == _key)
			found = travel;

		travel = travel->next;
	}

	_foundIndex = (found ? index : -1);

	return found;
}

//////////
// END PUBLIC METHODS
/////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////
//	PRIVATE METHODS
//////////

//////////
// END PRIVATE METHODS
/////////////////////////////////////////////////////////

#endif //LINKEDLIST_H