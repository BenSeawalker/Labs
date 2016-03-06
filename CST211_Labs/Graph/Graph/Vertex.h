/************************************************************************
* Author:		Garrett Fleischer
* Filename:		Vertex.h
* Date Created:	2/27/16
* Modifications:
*************************************************************************/
#ifndef VERTEX_H
#define VERTEX_H

#include <list>
using std::list;

// FORWARD CLASS DECLARATION
template<typename V, typename E> class Arc;


/************************************************************************
* Class: Vertex
*
* Purpose: This class stores data and Arcs for use in a Graph
*
* Manager functions:
* 	Vertex()
*
*	Vertex(const Vertex & copy)
*	operator = (const Vertex & copy)
*
*	~Vertex()
*
* Methods:
*
*	Data() : V &
*	
*	Processed() : bool &
*	
*	Arcs() : list<Arc<V, E>> &
*
*************************************************************************/
template<typename V, typename E>
class Vertex
{
public:
	// CTORS & DTOR
	Vertex(const V & data);
	Vertex(const Vertex<V, E> & copy);

	~Vertex();

	// OPERATORS
	Vertex<V, E> & operator=(const Vertex<V, E> & rhs);
	bool operator==(const Vertex<V, E> & rhs) const;

	// GETTERS
	V & Data();
	const V & Data() const;

	bool & Processed();
	const bool & Processed() const;

	list<Arc<V, E>> & Arcs();
	const list<Arc<V, E>> & Arcs() const;

private:
	list<Arc<V, E>> m_arcs;
	V m_data;
	bool m_processed;
};


///////////////////////////////////////////////////////////////
//	C'TORS & D'TOR
//////

template<typename V, typename E>
Vertex<V, E>::Vertex(const V & data)
	: m_data(data), m_processed(false)
{}

template<typename V, typename E>
Vertex<V, E>::Vertex(const Vertex<V, E> & copy)
	: m_arcs(copy.m_arcs), m_data(copy.m_data), m_processed(copy.m_processed)
{}

template<typename V, typename E>
Vertex<V, E>::~Vertex()
{
	m_processed = false;
}

//////
//	END C'TORS & D'TOR
///////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////
//	OPERATORS
//////

template<typename V, typename E>
Vertex<V, E> & Vertex<V, E>::operator=(const Vertex<V, E> & rhs)
{
	if (this != &rhs)
	{
		m_arcs = rhs.m_arcs;
		m_data = rhs.m_data;
		m_processed = rhs.m_processed;
	}

	return *this;
}

template<typename V, typename E>
bool Vertex<V, E>::operator==(const Vertex<V, E> & rhs) const
{
	return (m_arcs == rhs.m_arcs && m_data == rhs.m_data && m_processed == rhs.m_processed);
}

//////
//	END OPERATORS
///////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////
//	GETTERS
//////

template<typename V, typename E>
V & Vertex<V, E>::Data()
{
	return m_data;
}

template<typename V, typename E>
const V & Vertex<V, E>::Data() const
{
	return m_data;
}

template<typename V, typename E>
bool & Vertex<V, E>::Processed()
{
	return m_processed;
}

template<typename V, typename E>
const bool & Vertex<V, E>::Processed() const
{
	return m_processed;
}

template<typename V, typename E>
list<Arc<V, E>> & Vertex<V, E>::Arcs()
{
	return m_arcs;
}

template<typename V, typename E>
const list<Arc<V, E>> & Vertex<V, E>::Arcs() const
{
	return m_arcs;
}

//////
//	END GETTERS
///////////////////////////////////////////////////////////////

#endif // VERTEX_H