/*
@Author: Garrett Fleischer
@Date:	 10/18/15
*/

#ifndef ISAM_Block_h
#define ISAM_Block_h

#include "LinkedList.h"

template<class T>
class Block
{
public:
	Block(int(*CompareType)(const T * _t1, const T * _t2), bool(*CompareKey)(const T * _t, const string & _key));
	~Block();

	void Display(const string & _key, void(*Display)(const T * _item));
	void DisplayAll(void(*Display)(const T * _item));

	T * const Find(const string & _key, int & _foundIndex);

	void Insert(T * _data);

	STATUS Delete(const string & _key);

	int Size() { return m_list->Size(); }

	void MoveTailNode(Block & _to);
	void MoveHeadNode(Block & _to);

	const T * const FirstItem() { return (m_list->Head() ? m_list->Head()->data : nullptr); }
	const T * const LastItem() { return (m_list->Tail() ? m_list->Tail()->data : nullptr); }

private:
	LinkedList<T> * m_list;
};

template<class T>
Block<T>::Block(int(*CompareType)(const T * _t1, const T * _t2), bool(*CompareKey)(const T * _t, const string & _key))
{
	m_list = new LinkedList<T>(CompareType, CompareKey);
}

template<class T>
Block<T>::~Block()
{
	delete m_list;
}

template<class T>
T * const Block<T>::Find(const string & _key, int & _foundIndex)
{
	return m_list->Find(_key, _foundIndex);
}

template<class T>
void Block<T>::Insert(T * _data)
{
	m_list->Insert(_data);
}

template<class T>
STATUS Block<T>::Delete(const string & _key)
{
	return m_list->Delete(_key);
}

template<class T>
void Block<T>::MoveTailNode(Block & _to)
{
	_to.Insert(new T(*(m_list->Tail()->data)));
	m_list->Delete(m_list->Tail());
}

template<class T>
void Block<T>::MoveHeadNode(Block & _to)
{
	_to.Insert(new T(*(m_list->Head()->data)));
	m_list->Delete(m_list->Head());
}


template<class T>
void Block<T>::Display(const string & _key, void(*Display)(const T * _item))
{
	Display(m_list->Find(_key));
}


template<class T>
void Block<T>::DisplayAll(void(*Display)(const T * _item))
{
	m_list->Traverse(Display);
}


#endif // ISAM_Block_h