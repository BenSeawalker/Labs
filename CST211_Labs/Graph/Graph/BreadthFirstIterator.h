///************************************************************************
//* Author:		Garrett Fleischer
//* Filename:		BreadthFirstIterator.h
//* Date Created:	2/20/16
//* Modifications:
//*	N/A
//*************************************************************************/
//#ifndef BREADTHFIRSTITERATOR_H
//#define BREADTHFIRSTITERATOR_H
//
//#include "GraphIterator.h"
//
///************************************************************************
//* Class: BreadthFirstIterator
//*
//* Purpose:
//*
//* Manager functions:
//* 	BreadthFirstIterator ( )
//*	BreadthFirstIterator (const BreadthFirstIterator & copy)
//*	operator = (const BreadthFirstIterator & rhs)
//*
//*	~BreadthFirstIterator()
//*
//* Methods:
//*	PRIVATE
//*		BuildQueue(root : Vertex<V, E> *) : void
//*
//*************************************************************************/
//template<typename V, typename E>
//class BreadthFirstIterator : public GraphIterator<V, E>
//{
//public:
//	// CTORS & DTOR
//	BreadthFirstIterator(Graph<V, E> * graph);
//	BreadthFirstIterator(const BreadthFirstIterator<V, E> & copy);
//
//	virtual ~BreadthFirstIterator();
//
//	// OPERATORS
//	BreadthFirstIterator<V, E> & operator=(const BreadthFirstIterator<V, E> & rhs);
//
//protected:
//	// METHODS
//	virtual void BuildQueue(Vertex<V, E> * root);
//};
//
//
/////////////////////////////////////////////////////////////////
//// C'TORS & D'TOR
////////
//
//template<typename V, typename E>
//BreadthFirstIterator<V, E>::BreadthFirstIterator(Graph<V, E> * graph)
//	: GraphIterator(graph)
//{}
//
//template<typename V, typename E>
//BreadthFirstIterator<V, E>::BreadthFirstIterator(const BreadthFirstIterator<V, E> & copy)
//	: GraphIterator(copy)
//{}
//
//template<typename V, typename E>
//BreadthFirstIterator<V, E>::~BreadthFirstIterator()
//{}
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
//BreadthFirstIterator<V, E>& BreadthFirstIterator<V, E>::operator=(const BreadthFirstIterator<V, E> & rhs)
//{
//	if (this != &rhs)
//	{
//		GraphIterator::operator=(rhs);
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
//// PRIVATE METHODS
////////
//
///************************************************************************
//* Purpose: To iteratively build @m_queue with the breadth-first algorithm
//*
//* Precondition:
//*
//* Postcondition:
//*		Modifies:	@m_queue
//*		Throws:		N/A
//*		Returns:	N/A
//*************************************************************************/
//template<typename V, typename E>
//void BreadthFirstIterator<V, E>::BuildQueue(Vertex<V, E> * root)
//{
//	queue<Vertex<V, E> *> v_queue;
//	v_queue.push(&m_vertices.front());
//	m_vertices.front().Processed() = true;
//
//	while (v_queue.size() > 0)
//	{
//		Vertex<V, E> * vertex = v_queue.front();
//		v_queue.pop();
//		m_queue.push(vertex);
//
//		// Add connected destinations to queue, and mark them as processed
//		list<Arc<V, E>>::iterator arc;
//		for (arc = vertex->Arcs().begin(); arc != vertex->Arcs().end(); ++arc)
//		{
//			if (!arc->Destination()->Processed())
//			{
//				v_queue.push(arc->Destination());
//				arc->Destination()->Processed() = true;
//			}
//		}
//	}
//
//	// Mark all vertices as unprocessed
//	ProcessVertices(false);
//}
//
////////
//// END PRIVATE METHODS
/////////////////////////////////////////////////////////////////
//
//#endif // BREADTHFIRSTITERATOR_H