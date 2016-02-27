#ifndef ARC_H
#define ARC_H

#include "Vertex.h"

template<typename V, typename E>
class Arc
{
	template<typename, typename>
	friend class Graph;

public:
	Arc(const E & data, int weight, Vertex<V, E> * dest);
	Arc(const Arc & copy);

	~Arc();

	Arc & operator=(const Arc & rhs);

private:
	E m_data;
	int m_weight;
	Vertex<V, E> * m_dest;
}

#endif // ARC_H
