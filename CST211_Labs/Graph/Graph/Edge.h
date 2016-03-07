/************************************************************************
* Author:		Garrett Fleischer
* Filename:		Arc.h
* Date Created:	2/27/16
* Modifications:
*************************************************************************/
#ifndef ARC_H
#define ARC_H

// FORWARD CLASS DECLARATION
template<typename V, typename E> class Vertex;


/************************************************************************
* Class: Arc
*
* Purpose: This class stores data, weight, and a Vertex destination for use in a Graph
*
* Manager functions:
* 	Arc()
*
*	Arc(const Arc & copy)
*	operator = (const Arc & copy)
*
*	~Arc()
*
* Methods:
*
*	Data() : E &
*
*	Weight() : int &
*
*	Destination() : Vertex<V, E> *&
*
*************************************************************************/
template<typename V, typename E>
class Edge
{
public:
	// CTORS & DTOR
	Edge(const E & data, int weight, Vertex<V, E> * dest);
	Edge(const Edge<V, E> & copy);

	~Edge();

	// OPERATORS
	Edge<V, E> & operator=(const Edge<V, E> & rhs);
	bool operator==(const Edge<V, E> & rhs) const;

	// GETTERS
	E & Data();
	const E & Data() const;
	
	int & Weight();
	const int & Weight() const;

	Vertex<V, E> *& Destination();
	const Vertex<V, E> * Destination() const;

private:
	E m_data;
	int m_weight;
	Vertex<V, E> * m_dest;
};


///////////////////////////////////////////////////////////////
//	C'TORS & D'TOR
//////

template<typename V, typename E>
Edge<V, E>::Edge(const E & data, int weight, Vertex<V, E> * dest)
	: m_data(data), m_weight(weight), m_dest(dest)
{}

template<typename V, typename E>
Edge<V, E>::Edge(const Edge<V, E> & copy)
	: m_data(copy.m_data), m_weight(copy.m_weight), m_dest(copy.m_dest)
{}

template<typename V, typename E>
Edge<V, E>::~Edge()
{
	m_dest = nullptr;
}

//////
//	END C'TORS & D'TOR
///////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////
//	OPERATORS
//////

template<typename V, typename E>
Edge<V, E> & Edge<V, E>::operator=(const Edge<V, E> & rhs)
{
	if (this != &rhs)
	{
		m_data = rhs.m_data;
		m_weight = rhs.m_weight;
		m_dest = rhs.m_dest;
	}

	return *this;
}

template<typename V, typename E>
bool Edge<V, E>::operator==(const Edge<V, E> & rhs) const
{
	return (m_data == rhs.m_data && m_weight == rhs.m_weight && m_dest == rhs.m_dest);
}

//////
//	END OPERATORS
///////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////
//	GETTERS
//////

template<typename V, typename E>
E & Edge<V, E>::Data()
{
	return m_data;
}

template<typename V, typename E>
const E & Edge<V, E>::Data() const
{
	return m_data;
}

template<typename V, typename E>
int & Edge<V, E>::Weight()
{
	return m_weight;
}

template<typename V, typename E>
const int & Edge<V, E>::Weight() const
{
	return m_weight;
}

template<typename V, typename E>
Vertex<V, E>*& Edge<V, E>::Destination()
{
	return m_dest;
}

template<typename V, typename E>
const Vertex<V, E>* Edge<V, E>::Destination() const
{
	return m_dest;
}

//////
//	END GETTERS
///////////////////////////////////////////////////////////////

#endif // ARC_H


