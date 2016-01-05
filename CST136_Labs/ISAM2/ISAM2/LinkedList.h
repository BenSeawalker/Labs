/*
@Author: Garrett Fleischer
@Date:	 10/18/15
*/

#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#define _CRT_SECURE_NO_WARNINGS

#include <fstream>
using std::ifstream;
using std::ofstream;

#include <iostream>
using std::ios;

#include <string.h>
using std::string;

enum STATUS { NORMAL, EMPTY_LIST, KEY_NOT_FOUND };

template<typename DT>
struct Node
{
	Node() : data(nullptr), next(nullptr), previous(nullptr) {};
	Node(DT * _data) : data(_data), next(nullptr), previous(nullptr) {};

	DT * data;
	Node<DT> * next;
	Node<DT> * previous;

	~Node()
	{
		delete data;
	}
};



/************************************************************************
* Class: LinkedList<T>
*
* Purpose: This class stores multiple instances of type T in a memory efficient manner
*
* Manager functions:
* 	LinkedList (int(*compare_type)(T *, T *), bool(*compare_key)(T *, string &))
*		compare_type = how to compare two T pointers
*		compare_key = how to compare a T pointer with a string
*
*	~LinkedList()
*
* Methods:
*	Public:
*		Insert(T * _item);
*		Delete(const string & _key);
*		Delete(const Node<T> * const _node);
*		Traverse(int start_index, int end_index, void(*Visit)(T * _item));
*		Find(const string & _key);
*		FindMatches(const string & _key);
*		Size();
*		Write(ofstream & _file);
*		Read(ifstream & _file);
*	Private:
*		WriteNode(T * _node, ofstream & _file);
*		ReadNode(T * _node, ifstream & _file);
*
*************************************************************************/
template<class T>
class LinkedList
{
public:
	LinkedList(int(*compare_type)(const T * _t1, const T * _t2), int(*compare_key)(const T * _t, const string & _key));
	~LinkedList();

	void Insert(T * _data);

	STATUS Delete(const string & _key);
	void Delete(const Node<T> * const _node);

	void Traverse(void(*Visit)(T * _nodeData));

	T * const Find(const string & _key, int & _foundIndex);

	LinkedList<T> * FindMatches(const string & _key);

	int Size() { return m_size; }

	void Write(ofstream & _file);
	void Read(ifstream & _file);

	const Node<T> * const Head() const { return m_head; }
	const Node<T> * const Tail() const { return m_tail; }

private:
	int m_size;
	Node<T> * m_head;
	Node<T> * m_tail;

	int(*CompareType)(const T * _t1, const T * _t2);
	int(*CompareKey)(const T * _t, const string & _key);


	void WriteNode(T * _node, ofstream & _file);
	void ReadNode(T * _node, ifstream & _file);
};



/////////////////////////////////////////////////////////
//	C'tor and D'tor
//////////
	template<class T>
	LinkedList<T>::LinkedList(int(*compare_type)(const T *_t1, const T *_t2), int(*compare_key)(const T *_t, const string &_key))
		: m_size(0), m_head(nullptr), m_tail(nullptr), CompareType(compare_type), CompareKey(compare_key)
	{}


	template<class T>
	LinkedList<T>::~LinkedList()
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
	template<class T>
	void LinkedList<T>::Insert(T * _item)
	{
		Node<T> * node = new Node<T>(_item);

		if (m_head == nullptr || CompareType(node->data, m_head->data) <= 0)
		{
			node->next = m_head;
			m_head = node;

			if(m_head->next != nullptr)
				m_head->next->previous = m_head;

			if (m_tail == nullptr)
				m_tail = m_head->next;

			++m_size;
		}
		else
		{
			Node<T> * travel = m_head;
			Node<T> * trail = nullptr;

			while (travel != nullptr && CompareType(node->data, travel->data) > 0)
			{
				trail = travel;
				travel = travel->next;
			}

			if (trail != nullptr)
			{
				trail->next = node;
				node->next = travel;

				node->previous = trail;
				if (travel != nullptr)
					travel->previous = node;

				if (travel == nullptr)
					m_tail = node;

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
	template<class T>
	STATUS LinkedList<T>::Delete(const string & _key)
	{
		Node<T> * travel = m_head;
		Node<T> * trail = nullptr;
		STATUS status = NORMAL;

		if (m_head == nullptr)
		{
			status = EMPTY_LIST;
		}
		else if (CompareKey(m_head->data, _key) == 0)
		{
			trail = m_head;
			m_head = m_head->next;

			if (m_head != nullptr)
			{
				m_head->previous = nullptr;

				if (m_head->next == nullptr)
					m_tail = nullptr;
			}
			else
				m_tail = nullptr;

			delete trail;
			--m_size;
		}
		else
		{
			while (travel != nullptr && (CompareKey(travel->data, _key) != 0))
			{
				trail = travel;
				travel = travel->next;
			}

			if (travel == nullptr)
			{
				status = KEY_NOT_FOUND;
			}
			else
			{
				trail->next = travel->next;

				if(trail->next != nullptr)
					trail->next->previous = trail;

				if (trail->next == nullptr)
					m_tail = trail;

				delete travel;
				--m_size;
			}
		}

		return status;
	}


	/**********************************************************************
	* Purpose: This function deletes the given Node from the list
	*
	* Precondition:
	*		_node = the node to delete
	*
	* Postcondition:
	*		Returns N/A
	*		Can Modify m_head or m_tail
	*
	************************************************************************/
	template<class T>
	void LinkedList<T>::Delete(const Node<T> * const _node)
	{
		Node<T> * travel = m_head;
		Node<T> * trail = nullptr;

		if (m_head == _node)
		{
			trail = m_head;
			m_head = m_head->next;

			m_head->previous = nullptr;

			if (m_head->next == nullptr)
				m_tail = nullptr;

			delete trail;
			--m_size;
		}
		else
		{
			while (travel != nullptr && travel != _node)
			{
				trail = travel;
				travel = travel->next;
			}

			if (travel != nullptr)
			{
				trail->next = travel->next;

				if (trail->next != nullptr)
					trail->next->previous = trail;

				if (trail->next == nullptr)
					m_tail = trail;

				delete travel;
				--m_size;
			}
		}
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
	template<class T>
	void LinkedList<T>::Traverse(void(*Visit)(T * _nodeData))
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
	*		_key = the string to match the item with
	*
	* Postcondition:
	*		Returns a pointer to the item matching _key
	*		_foundIndex	holds the index the item was found at
	*
	************************************************************************/
	template<class T>
	T * const LinkedList<T>::Find(const string & _key, int & _foundIndex)
	{
		Node<T> * travel = m_head;
		T * item = nullptr;

		int index = -1;
		while (travel != nullptr && item == nullptr)
		{
			++index;
			if (travel != nullptr && (CompareKey(travel->data, _key) == 0))
				item = travel->data;

			travel = travel->next;
		}

		_foundIndex = (item ? index : -1);

		return item;
	}


	/**********************************************************************
	* Purpose: This function finds all items matching _key
	*			returns a Linked List containing these items
	*
	* Precondition:
	*		_key = the string to match the items with
	*
	* Postcondition:
	*		Returns a LinkedList of items matching _key
	*
	************************************************************************/
	template<class T>
	LinkedList<T> * LinkedList<T>::FindMatches(const string & _key)
	{
		Node<T> * travel = m_head;
		LinkedList<T> * lst = new LinkedList<T>(CompareType, CompareKey);

		while (travel != nullptr)
		{
			if (travel != nullptr && (CompareKey(travel->data, _key) == 0))
			{
				//T * data_copy = new T(*(travel->data));
				lst->Insert(new T(*(travel->data)));
			}

			travel = travel->next;
		}

		return lst;
	}



	/**********************************************************************
	* Purpose: This function serializes the list and writes it to a file
	*
	* Precondition:
	*		_file must exist and be open
	*
	* Postcondition:
	*		Returns N/A
	*		Modifies _file
	*
	************************************************************************/
	template<class T>
	void LinkedList<T>::Write(ofstream & _file)
	{
		Node<T> * travel = m_head;

		while (travel != nullptr)
		{
			WriteNode(travel->data, _file);
			travel = travel->next;
		}
	}


	/**********************************************************************
	* Purpose: This function de-serializes a LinkedList contained in a file
	*
	* Precondition:
	*		_file must exist and be open
	*
	* Postcondition:
	*		Returns N/A
	*		Modifies m_head and m_tail
	*
	************************************************************************/
	template<class T>
	void LinkedList<T>::Read(ifstream & _file)
	{
		while (!_file.eof())
		{
			T * data = new T;
			ReadNode(data, _file);

			if (_file.gcount() < sizeof(T))	//avoid corrupted data
				delete data;
			else
				Insert(data);
		}
	}

//////////
// END PUBLIC METHODS
/////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////
//	PRIVATE METHODS
//////////

	/**********************************************************************
	* Purpose: This function serializes an item and appends it to a file
	*
	* Precondition:
	*		_file must exist and be open
	*
	* Postcondition:
	*		Returns N/A
	*		Modifies _file
	*
	************************************************************************/
	template<class T>
	void LinkedList<T>::WriteNode(T * _nodeData, ofstream & _file)
	{
		_file.write(reinterpret_cast<char *>(&_nodeData), sizeof(T));
	}


	/**********************************************************************
	* Purpose: This function de-serializes an item contained in a file
	*
	* Precondition:
	*		_file must exist and be open
	*
	* Postcondition:
	*		Returns N/A
	*		Modifies _nodeData
	*
	************************************************************************/
	template<class T>
	void LinkedList<T>::ReadNode(T * _nodeData, ifstream & _file)
	{
		_file.read(reinterpret_cast<char *>(&_nodeData), sizeof(T));
	}

//////////
// END PRIVATE METHODS
/////////////////////////////////////////////////////////

#endif //LINKEDLIST_H