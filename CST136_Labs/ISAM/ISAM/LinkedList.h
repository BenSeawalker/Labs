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

template<typename NodeType>
struct Node
{
	Node() : data(nullptr), next(nullptr), previous(nullptr) {};
	Node(NodeType * _data) : data(_data), next(nullptr), previous(nullptr) {};

	NodeType * data;
	Node<NodeType> * next;
	Node<NodeType> * previous;

	~Node()
	{
		delete data;
	}
};


template<class T>
class LinkedList
{
public:
	LinkedList(int(*compare_type)(const T * _t1, const T * _t2), bool(*compare_key)(const T * _t, const string & _key));
	~LinkedList();

	void Insert(T * _data);
	STATUS Delete(const string & _key);
	T * const Find(const string & _key, int & _foundIndex);
	LinkedList<T> * FindMatches(const string & _key);

	void Traverse(void(*visit)(const T * _nodeData));

	void Write(ofstream & _file);
	void Read(ifstream & _file);

	int Size() { return m_size; }

	const Node<T> * const Head() const { return m_head; }
	const Node<T> * const Tail() const { return m_tail; }

	void Delete(const Node<T> * const _node);


private:
	int m_size;
	Node<T> * m_head;
	Node<T> * m_tail;

	int(*CompareType)(const T * _t1, const T * _t2);
	bool(*CompareKey)(const T * _t, const string & _key);


	void WriteNode(T * _node, ofstream & _file);
	void ReadNode(T * _node, ifstream & _file);
};



template<class T>
LinkedList<T>::LinkedList(int(*compare_type)(const T *_t1, const T *_t2), bool(*compare_key)(const T *_t, const string &_key))
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

template<class T>
void LinkedList<T>::Insert(T * _data)
{
	Node<T> * node = new Node<T>(_data);

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
	else if (CompareKey(m_head->data, _key))
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
		while (travel != nullptr && !CompareKey(travel->data, _key))
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

template<class T>
T * const LinkedList<T>::Find(const string & _key, int & _foundIndex)
{
	Node<T> * travel = m_head;
	T * item = nullptr;

	int index = -1;
	while (travel != nullptr && item == nullptr)
	{
		++index;
		if (travel != nullptr && CompareKey(travel->data, _key))
			item = travel->data;

		travel = travel->next;
	}

	_foundIndex = (item ? index : -1);

	return item;
}

template<class T>
LinkedList<T> * LinkedList<T>::FindMatches(const string & _key)
{
	Node<T> * travel = m_head;
	LinkedList<T> * lst = new LinkedList<T>(CompareType, CompareKey);

	while (travel != nullptr)
	{
		if (travel != nullptr && CompareKey(travel->data, _key))
		{
			//T * data_copy = new T(*(travel->data));
			lst->Insert(new T(*(travel->data)));
		}

		travel = travel->next;
	}

	return lst;
}

template<class T>
void LinkedList<T>::Traverse(void(*visit)(const T * _nodeData))
{
	Node<T> * travel = m_head;

	while (travel != nullptr)
	{
		visit(travel->data);
		travel = travel->next;
	}
}

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

template<class T>
void LinkedList<T>::WriteNode(T * _nodeData, ofstream & _file)
{
	_file.write(reinterpret_cast<char *>(&_nodeData), sizeof(T));
}

template<class T>
void LinkedList<T>::ReadNode(T * _nodeData, ifstream & _file)
{
	_file.read(reinterpret_cast<char *>(&_nodeData), sizeof(T));
}


#endif