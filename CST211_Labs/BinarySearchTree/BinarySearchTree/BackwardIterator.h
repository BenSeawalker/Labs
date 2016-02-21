//#ifndef BACKWARDITERATOR_H
//#define BACKWARDITERATOR_H
//
//#include "ListIterator.h"
//
//template<typename T>
//class BackwardIterator : public ListIterator<T>
//{
//public:
//	// CTORS & DTOR
//	BackwardIterator(DoubleLinkedList<T> * list);
//	BackwardIterator(const BackwardIterator<T> & copy);
//
//	virtual ~BackwardIterator();
//
//	// OPERATORS
//	BackwardIterator<T> & operator=(const BackwardIterator<T> & rhs);
//
//	// METHODS
//	virtual void Reset();
//
//	virtual void MoveNext();
//};
//
//
//template<typename T>
//BackwardIterator<T>::BackwardIterator(DoubleLinkedList<T> * list)
//	: ListIterator(list)
//{}
//
//template<typename T>
//BackwardIterator<T>::BackwardIterator(const BackwardIterator<T> & copy)
//	: ListIterator(copy)
//{}
//
//template<typename T>
//BackwardIterator<T>::~BackwardIterator()
//{}
//
//template<typename T>
//BackwardIterator<T>& BackwardIterator<T>::operator=(const BackwardIterator<T> & rhs)
//{
//	if (this != &rhs)
//	{
//		ListIterator::operator=(rhs);
//	}
//
//	return *this;
//}
//
//template<typename T>
//void BackwardIterator<T>::Reset()
//{
//	if (!m_list)
//		throw Exception("Error accessing non-existent list!");
//
//	m_current = m_list->m_tail;
//}
//
//template<typename T>
//void BackwardIterator<T>::MoveNext()
//{
//	if (IsDone())
//		throw Exception("Cannot access current element! Iterator is done.");
//
//	m_current = m_current->Prev();
//}
//
//#endif // BACKWARDITERATOR_H