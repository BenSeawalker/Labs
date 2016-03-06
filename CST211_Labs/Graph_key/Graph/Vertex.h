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
template<typename K, typename V, typename E> class Arc;


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
*	Arcs() : list<Arc<K, V, E>> &
*
*************************************************************************/
template<typename K, typename V, typename E>
class Vertex
{
public:
	// CTORS & DTOR
	Vertex(const K & key, const V & data);
	Vertex(const Vertex<K, V, E> & copy);

	~Vertex();

	// OPERATORS
	Vertex<K, V, E> & operator=(const Vertex<K, V, E> & rhs);
	bool operator==(const Vertex<K, V, E> & rhs) const;

	// GETTERS
	K & Key();
	const K & Key() const;

	V & Data();
	const V & Data() const;

	bool & Processed();
	const bool & Processed() const;

	list<Arc<K, V, E>> & Arcs();
	const list<Arc<K, V, E>> & Arcs() const;

private:
	list<Arc<K, V, E>> m_arcs;
	K m_key;
	V m_data;
	bool m_processed;
};


///////////////////////////////////////////////////////////////
//	C'TORS & D'TOR
//////

template<typename K, typename V, typename E>
Vertex<K, V, E>::Vertex(const K & key, const V & data)
	: m_key(key), m_data(data), m_processed(false)
{}

template<typename K, typename V, typename E>
Vertex<K, V, E>::Vertex(const Vertex<K, V, E> & copy)
	: m_arcs(copy.m_arcs), m_key(copy.m_key), m_data(copy.m_data), m_processed(copy.m_processed)
{}

template<typename K, typename V, typename E>
Vertex<K, V, E>::~Vertex()
{
	m_processed = false;
}

//////
//	END C'TORS & D'TOR
///////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////
//	OPERATORS
//////

template<typename K, typename V, typename E>
Vertex<K, V, E> & Vertex<K, V, E>::operator=(const Vertex<K, V, E> & rhs)
{
	if (this != &rhs)
	{
		m_arcs = rhs.m_arcs;
		m_key = rhs.m_key;
		m_data = rhs.m_data;
		m_processed = rhs.m_processed;
	}

	return *this;
}

template<typename K, typename V, typename E>
bool Vertex<K, V, E>::operator==(const Vertex<K, V, E> & rhs) const
{
	return (m_key == rhs.m_key && m_processed == rhs.m_processed && m_data == rhs.m_data && m_arcs == rhs.m_arcs);
}

//////
//	END OPERATORS
///////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////
//	GETTERS
//////

template<typename K, typename V, typename E>
K & Vertex<K, V, E>::Key()
{
	return m_key;
}

template<typename K, typename V, typename E>
const K & Vertex<K, V, E>::Key() const
{
	return m_key;
}

template<typename K, typename V, typename E>
V & Vertex<K, V, E>::Data()
{
	return m_data;
}

template<typename K, typename V, typename E>
const V & Vertex<K, V, E>::Data() const
{
	return m_data;
}

template<typename K, typename V, typename E>
bool & Vertex<K, V, E>::Processed()
{
	return m_processed;
}

template<typename K, typename V, typename E>
const bool & Vertex<K, V, E>::Processed() const
{
	return m_processed;
}

template<typename K, typename V, typename E>
list<Arc<K, V, E>> & Vertex<K, V, E>::Arcs()
{
	return m_arcs;
}

template<typename K, typename V, typename E>
const list<Arc<K, V, E>> & Vertex<K, V, E>::Arcs() const
{
	return m_arcs;
}

//////
//	END GETTERS
///////////////////////////////////////////////////////////////

#endif // VERTEX_H