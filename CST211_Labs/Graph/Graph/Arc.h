/************************************************************************
* Author:		Garrett Fleischer
* Filename:		Arc.h
* Date Created:	2/27/16
* Modifications:
*************************************************************************/
#ifndef ARC_H
#define ARC_H

// FORWARD CLASS DECLARATION
template<typename K, typename V, typename E> class Vertex;


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
*	Destination() : Vertex<K, V, E> *&
*
*************************************************************************/
template<typename K, typename V, typename E>
class Arc
{
public:
	// CTORS & DTOR
	Arc(const K & key, const E & data, int weight, Vertex<K, V, E> * dest);
	Arc(const Arc<K, V, E> & copy);

	~Arc();

	// OPERATORS
	Arc<K, V, E> & operator=(const Arc<K, V, E> & rhs);
	bool operator==(const Arc<K, V, E> & rhs) const;

	// GETTERS
	K & Key();
	const K & Key() const;

	E & Data();
	const E & Data() const;
	
	int & Weight();
	const int & Weight() const;

	Vertex<K, V, E> *& Destination();
	const Vertex<K, V, E> * Destination() const;

private:
	K m_key;
	E m_data;
	int m_weight;
	Vertex<K, V, E> * m_dest;
};


///////////////////////////////////////////////////////////////
//	C'TORS & D'TOR
//////

template<typename K, typename V, typename E>
Arc<K, V, E>::Arc(const K & key, const E & data, int weight, Vertex<K, V, E> * dest)
	: m_key(key), m_data(data), m_weight(weight), m_dest(dest)
{}

template<typename K, typename V, typename E>
Arc<K, V, E>::Arc(const Arc<K, V, E> & copy)
	: m_key(copy.m_key), m_data(copy.m_data), m_weight(copy.m_weight), m_dest(copy.m_dest)
{}

template<typename K, typename V, typename E>
Arc<K, V, E>::~Arc()
{
	m_dest = nullptr;
}

//////
//	END C'TORS & D'TOR
///////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////
//	OPERATORS
//////

template<typename K, typename V, typename E>
Arc<K, V, E> & Arc<K, V, E>::operator=(const Arc<K, V, E> & rhs)
{
	if (this != &rhs)
	{
		m_key = rhs.m_key;
		m_data = rhs.m_data;
		m_weight = rhs.m_weight;
		m_dest = rhs.m_dest;
	}

	return *this;
}

template<typename K, typename V, typename E>
bool Arc<K, V, E>::operator==(const Arc<K, V, E> & rhs) const
{
	return (m_key == rhs.m_key && m_dest == rhs.m_dest && m_weight == rhs.m_weight && m_data == rhs.m_data);
}

template<typename K, typename V, typename E>
K & Arc<K, V, E>::Key()
{
	return m_key;
}

template<typename K, typename V, typename E>
const K & Arc<K, V, E>::Key() const
{
	return m_key;
}

//////
//	END OPERATORS
///////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////
//	GETTERS
//////

template<typename K, typename V, typename E>
E & Arc<K, V, E>::Data()
{
	return m_data;
}

template<typename K, typename V, typename E>
const E & Arc<K, V, E>::Data() const
{
	return m_data;
}

template<typename K, typename V, typename E>
int & Arc<K, V, E>::Weight()
{
	return m_weight;
}

template<typename K, typename V, typename E>
const int & Arc<K, V, E>::Weight() const
{
	return m_weight;
}

template<typename K, typename V, typename E>
Vertex<K, V, E>*& Arc<K, V, E>::Destination()
{
	return m_dest;
}

template<typename K, typename V, typename E>
const Vertex<K, V, E>* Arc<K, V, E>::Destination() const
{
	return m_dest;
}

//////
//	END GETTERS
///////////////////////////////////////////////////////////////

#endif // ARC_H


