#ifndef VERTEX_H
#define VERTEX_H

#include <list>
#include "Arc.h"


template<typename V, typename E>
class Vertex
{
	template<typename, typename>
	friend class Graph;

public:
	Vertex(const V & data);
	Vertex(const Vertex & copy);

	~Vertex();

	Vertex & operator=(const Vertex & rhs);

private:
	list<Arc<V, E>> m_edges;
	V m_data;
	bool m_processed;
}

#endif // VERTEX_H
