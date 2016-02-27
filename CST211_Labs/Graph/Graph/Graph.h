/************************************************************************
* Author:		Garrett Fleischer
* Filename:		Graph.h
* Date Created:	2/27/16
* Modifications:
*************************************************************************/
#ifndef GRAPH_H
#define GRAPH_H

#include <list>
#include "Vertex.h"
#include "Arc.h"


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
	Graph & operator=(const Graph<V, E> & rhs);

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
	Arc<V, E> * FindArc(const V & from, const V & to, const E & edge);

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
Graph & Graph<V, E>::operator=(const Graph<V, E> & rhs)
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
		m_vertices.remove(*found);

	return (found != nullptr);
}

// * ARCS * //
template<typename V, typename E>
void Graph<V, E>::InsertArc(const V & from, const V & to, const E & data, int weight)
{
	Vertex<V, E> * v_from = FindVertex(from);
	Vertex<V, E> * v_to = FindVertex(to);

	v_from->m_arcs.push_back(Arc<V, E>(data, weight, v_to));
}

template<typename V, typename E>
bool Graph<V, E>::DeleteArc(const V & from, const V & to, const E & data)
{
	Vertex<V, E> * v_from = FindVertex(from);
	Arc<V, E> * found = FindArc(v_from, to, data);

	if (found)
		v_from->m_arcs.remove(*found);

	return (found != nullptr);
}

// * SEARCHES * //
template<typename V, typename E>
void Graph<V, E>::BreadthFirst(Visit_t visit)
{
}

template<typename V, typename E>
void Graph<V, E>::DepthFirst(Visit_t visit)
{
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
Vertex<V, E>* Graph<V, E>::FindVertex(const V & data)
{
	return NULL;
}

template<typename V, typename E>
Arc<V, E>* Graph<V, E>::FindArc(const Vertex<V, E> * from, const V & to, const E & edge)
{
	return NULL;
}

//////
//	END PRIVATE METHODS
///////////////////////////////////////////////////////////////

#endif // GRAPH_H


