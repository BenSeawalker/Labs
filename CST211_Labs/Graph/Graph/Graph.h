/************************************************************************
* Author:		Garrett Fleischer
* Filename:		Graph.h
* Date Created:	2/27/16
* Modifications:
*************************************************************************/
#ifndef GRAPH_H
#define GRAPH_H

#include <list>
using std::list;
#include <stack>
using std::stack;
#include <queue>
using std::queue;

#include "Vertex.h"
#include "Arc.h"
#include "Exception.h"


/************************************************************************
* Class: Graph
*
* Purpose: This class creates a dynamic one-dimensional array that can be
* started at any base.
*
* Manager functions:
* 	Array()
*
*	Array(const Array & copy)
*	operator = (const Array & copy)
*
*	~Array()
*
* Methods:
*
*
*
*
*
*
*
*
*
*
*
*
*
*
*
*
*
*
*
*
*************************************************************************/
template<typename V, typename E>
class Graph
{
public:
	// TYPEDEFS
	typedef void(*Visit_t)(V & data);

	// CTORS & DTOR
	Graph();
	Graph(const Graph<V, E> & copy);

	~Graph();

	// OPERATORS
	Graph<V, E> & operator=(const Graph<V, E> & rhs);

	// METHODS
	void InsertVertex(const V & data);
	bool DeleteVertex(const V & data);

	void InsertArc(const V & from, const V & to, const E & data, int weight = 0);
	bool DeleteArc(const V & from, const V & to, const E & data);

	void BreadthFirst(Visit_t visit);
	void DepthFirst(Visit_t visit);

	bool IsEmpty();

private:
	// METHODS
	Vertex<V, E> * FindVertex(const V & data);
	Arc<V, E> * FindArc(Vertex<V, E> * from, Vertex<V, E> * v_to, const E & data);

	void ProcessVertices(bool processed);

	// MEMBERS
	list<Vertex<V, E>> m_vertices;
};


///////////////////////////////////////////////////////////////
//	C'TORS & D'TOR
//////

template<typename V, typename E>
Graph<V, E>::Graph()
{}

template<typename V, typename E>
Graph<V, E>::Graph(const Graph<V, E> & copy)
	: m_vertices(copy.m_vertices)
{}

template<typename V, typename E>
Graph<V, E>::~Graph()
{
}

//////
//	END C'TORS & D'TOR
///////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////
//	OPERATORS
//////

template<typename V, typename E>
Graph<V, E> & Graph<V, E>::operator=(const Graph<V, E> & rhs)
{
	if (this != &rhs)
	{
		m_vertices = rhs.m_vertices;
	}

	return *this;
}

//////
//	END OPERATORS
///////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////
//	PUBLIC METHODS
//////

// * VERTICES * //
template<typename V, typename E>
void Graph<V, E>::InsertVertex(const V & data)
{
	m_vertices.push_back(Vertex<V, E>(data));
}

template<typename V, typename E>
bool Graph<V, E>::DeleteVertex(const V & data)
{
	Vertex<V, E> * found = FindVertex(data);

	if (found)
	{
		// Remove all arcs with found vertex as their destination
		list<Arc<V, E>>::iterator iter;
		for (iter = found->Arcs().begin(); iter != found->Arcs().end(); ++iter)
		{
			Arc<V, E> * reverse_arc = FindArc(iter->Destination(), found, iter->Data());
			iter->Destination()->Arcs().remove(*reverse_arc);
		}

		// Remove found vertex
		m_vertices.remove(*found);
	}

	return (found != nullptr);
}

// * ARCS * //
template<typename V, typename E>
void Graph<V, E>::InsertArc(const V & from, const V & to, const E & data, int weight)
{
	Vertex<V, E> * v_from = FindVertex(from);
	Vertex<V, E> * v_to = FindVertex(to);

	if (!v_from || !v_to)
		throw Exception("Error inserting Arc! Vertex not found.");

	// Add forward and reverse arcs between from and to vertices
	v_from->Arcs().push_back(Arc<V, E>(data, weight, v_to));
	v_to->Arcs().push_back(Arc<V, E>(data, weight, v_from));
}

template<typename V, typename E>
bool Graph<V, E>::DeleteArc(const V & from, const V & to, const E & data)
{
	Vertex<V, E> * v_from = FindVertex(from);
	Vertex<V, E> * v_to = FindVertex(to);

	if (!v_from || !v_to)
		throw Exception("Error deleting Arc! Vertex not found.");

	// Remove forward and reverse arcs between from and to vertices 
	Arc<V, E> * arc_from = FindArc(v_from, v_to, data);
	Arc<V, E> * arc_to = FindArc(v_to, v_from, data);
	v_from->Arcs().remove(*arc_from);
	v_to->Arcs().remove(*arc_to);

	return (arc_from && arc_to);
}

// * SEARCHES * //
template<typename V, typename E>
void Graph<V, E>::BreadthFirst(Visit_t visit)
{
	queue<Vertex<V, E> *> v_queue;
	v_queue.push(&m_vertices.front());
	m_vertices.front().Processed() = true;

	while (v_queue.size() > 0)
	{
		Vertex<V, E> * vert = v_queue.front();
		v_queue.pop();
		visit(vert->Data());

		// Add connected destinations to queue, and mark them as processed
		list<Arc<V, E>>::iterator iter;
		for (iter = vert->Arcs().begin(); iter != vert->Arcs().end(); ++iter)
		{
			if (!iter->Destination()->Processed())
			{
				v_queue.push(iter->Destination());
				iter->Destination()->Processed() = true;
			}
		}
	}

	// Mark all vertices as unprocessed
	ProcessVertices(false);
}

template<typename V, typename E>
void Graph<V, E>::DepthFirst(Visit_t visit)
{
	stack<Vertex<V, E> *> v_stack;
	v_stack.push(&m_vertices.front());
	m_vertices.front().Processed() = true;

	while (v_stack.size() > 0)
	{
		Vertex<V, E> * vert = v_stack.top();
		v_stack.pop();
		visit(vert->Data());

		// Add connected destinations to stack, and mark them as processed
		list<Arc<V, E>>::iterator iter;
		for (iter = vert->Arcs().begin(); iter != vert->Arcs().end(); ++iter)
		{
			if (!iter->Destination()->Processed())
			{
				v_stack.push(iter->Destination());
				iter->Destination()->Processed() = true;
			}
		}
	}

	// Mark all vertices as unprocessed
	ProcessVertices(false);
}

// * CONDITIONS * //
template<typename V, typename E>
bool Graph<V, E>::IsEmpty()
{
	return (list.size() == 0);
}

//////
//	END PUBLIC METHODS
///////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////
//	PRIVATE METHODS
//////

template<typename V, typename E>
Vertex<V, E> * Graph<V, E>::FindVertex(const V & data)
{
	Vertex<V, E> * found = nullptr;

	list<Vertex<V, E>>::iterator iter;
	for (iter = m_vertices.begin(); iter != m_vertices.end() && !found; ++iter)
	{
		if (iter->Data() == data)
			found = &(*iter);
	}

	return found;
}

template<typename V, typename E>
Arc<V, E> * Graph<V, E>::FindArc(Vertex<V, E> * v_from, Vertex<V, E> * v_to, const E & data)
{
	Arc<V, E> * found = nullptr;

	list<Arc<V, E>>::iterator iter;
	for (iter = v_from->Arcs().begin(); iter != v_from->Arcs().end() && !found; ++iter)
	{
		if (iter->Destination() == v_to && iter->Data() == data)
			found = &(*iter);
	}

	return found;
}

template<typename V, typename E>
void Graph<V, E>::ProcessVertices(bool proccessed)
{
	list<Vertex<V, E>>::iterator iter;
	for (iter = m_vertices.begin(); iter != m_vertices.end(); ++iter)
		iter->Processed() = proccessed;
}

//////
//	END PRIVATE METHODS
///////////////////////////////////////////////////////////////


#endif // GRAPH_H


