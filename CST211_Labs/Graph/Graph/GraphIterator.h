///************************************************************************
//* Author:		Garrett Fleischer
//* Filename:		GraphIterator.h
//* Date Created:	2/20/16
//* Modifications:
//*	N/A
//*************************************************************************/
//#ifndef BSTITERATOR_H
//#define BSTITERATOR_H
//
//#include <list>
//using std::list;
//#include <queue>
//using std::queue;
//
//#include "AbstractIterator.h"
//#include "Graph.h"
//#include "Vertex.h"
//
//
///************************************************************************
//* Class: GraphIterator
//*
//* Purpose: To provide base functionality for iterating over all elements in a Tree
//*			Default functionality is to BuildQueue() and move through all its elements
//*
//* Manager functions:
//* 	GraphIterator ( )
//*	GraphIterator (const GraphIterator & copy)
//*	operator = (const GraphIterator & rhs)
//*
//*	~GraphIterator()
//*
//* Methods:
//*	PUBLIC
//*		Reset()			: void
//*		MoveNext()		: void
//*		GetCurrent()	: V &
//*		IsDone()		: void
//*
//*	PRIVATE
//*		BuildQueue(root : V *) : void
//*
//*************************************************************************/
//template<typename V, typename E>
//class GraphIterator : public AbstractIterator<V>
//{
//public:
//	// DTOR
//	virtual ~GraphIterator();
//
//	// METHODS
//	virtual void Reset();
//	
//	virtual void MoveNext();
//
//	virtual V & GetCurrent();
//
//	virtual bool IsDone() const;
//
//protected:
//	// CTORS
//	GraphIterator(Graph<V, E> * graph);
//	GraphIterator(const Graph<V, E> * graph);
//	GraphIterator(const GraphIterator & copy);
//
//	// OPERATORS
//	GraphIterator<V, E> & operator=(const GraphIterator & rhs);
//
//	// METHODS
//	virtual void BuildQueue(V * root) = 0;
//
//	// MEMBERS
//	Graph<V, E> * m_graph;
//	Vertex<V, E> * m_current;
//	queue<Vertex<V, E> *> m_queue;
//};
//
//
/////////////////////////////////////////////////////////////////
//// C'TORS & D'TOR
////////
//
//template<typename V, typename E>
//GraphIterator<V, E>::GraphIterator(Graph<V, E> * graph)
//	: m_graph(graph), m_current(nullptr)
//{}
//
//template<typename V, typename E>
//GraphIterator<V, E>::GraphIterator(const GraphIterator & copy)
//	: m_graph(copy.m_graph), m_current(copy.m_current)
//{}
//
//template<typename V, typename E>
//GraphIterator<V, E>::~GraphIterator()
//{
//	m_graph = nullptr;
//	m_current = nullptr;
//	m_queue = queue<Vertex<V, E> *>();
//}
//
////////
//// END C'TORS & D'TOR
/////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////
//// OPERATORS
////////
//
//template<typename V, typename E>
//GraphIterator<V, E>& GraphIterator<V, E>::operator=(const GraphIterator & rhs)
//{
//	if (this != &rhs)
//	{
//		m_graph = rhs.m_graph;
//		m_current = rhs.m_current;
//	}
//
//	return *this;
//}
//
////////
//// END OPERATORS
/////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////
//// PUBLIC METHODS
////////
//
///************************************************************************
//* Purpose: To rebuild @m_queue and set m_current to the first item in it
//*
//* Precondition:
//*		@m_list : cannot be nullptr
//*
//* Postcondition:
//*		Modifies:	@m_current, @m_queue
//*		Throws:		Exception("Error accessing non-existent list!")
//*		Returns:	N/A
//*************************************************************************/
//template<typename V, typename E>
//void GraphIterator<V, E>::Reset()
//{
//	if (!m_graph)
//		throw Exception("Error accessing non-existent list!");
//
//	m_queue = queue<Vertex<V, E> *>();
//	BuildQueue(&(m_graph->m_vertices.front()));
//	MoveNext();
//}
//
///************************************************************************
//* Purpose: To move @m_current to the "next" item in @m_queue
//*
//* Precondition:
//*		IsDone() must return false
//*
//* Postcondition:
//*		Modifies:	@m_current
//*		Throws:		Exception("Cannot access next element! Iterator is done.")
//*		Returns:	N/A
//*************************************************************************/
//template<typename V, typename E>
//void GraphIterator<V, E>::MoveNext()
//{
//	m_current = ((m_queue.empty()) ? nullptr : m_queue.front());
//	m_queue.pop();
//
//	if (IsDone())
//		Exception("Cannot access next element! Iterator is done.");
//}
//
///************************************************************************
//* Purpose: To get the data stored at the current element
//*
//* Precondition:
//*		IsDone() must return false
//*
//* Postcondition:
//*		Modifies:	N/A
//*		Throws:		Exception("Cannot access current element! Iterator is done.")
//*		Returns:	N/A
//*************************************************************************/
//template<typename V, typename E>
//V & GraphIterator<V, E>::GetCurrent()
//{
//	if (IsDone())
//		throw Exception("Cannot access current element! Iterator is done.");
//
//	return m_current->Data();
//}
//
///************************************************************************
//* Purpose: To check if all the elements have been iterated over
//*
//* Precondition:
//*		@m_current is equivalent to nullptr
//*
//* Postcondition:
//*		Modifies:	N/A
//*		Throws:		N/A
//*		Returns:	TRUE if the iterator has finished
//*************************************************************************/
//template<typename V, typename E>
//bool GraphIterator<V, E>::IsDone() const
//{
//	return m_current == nullptr;
//}
//
////////
//// END PUBLIC METHODS
/////////////////////////////////////////////////////////////////
//
//#endif // BSTITERATOR_H