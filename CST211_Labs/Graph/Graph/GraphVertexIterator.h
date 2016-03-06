//#ifndef GRAPHVERTEXITERATOR_H
//#define GRAPHVERTEXITERATOR_H
//
//#include "AbstractIterator.h"
//#include "Graph.h"
//#include "Vertex.h"
//#include "Exception.h"
//
//template<typename V, typename E>
//class GraphVertexIterator : AbstractIterator<Vertex<V, E>>
//{
//public:
//	// CTORS & DTOR
//	GraphVertexIterator(Graph<V, E> & graph);
//	GraphVertexIterator(const GraphVertexIterator<V, E> & copy);
//
//	~GraphVertexIterator();
//
//	// OPERATORS
//	GraphVertexIterator<V, E> & operator=(const GraphVertexIterator<V, E> & rhs);
//
//	// METHODS
//	virtual void Reset();
//
//	virtual void MoveNext();
//
//	virtual Vertex<V, E> & GetCurrent();
//
//	virtual bool IsDone() const;
//
//private:
//	Graph<V, E> * m_graph;
//	typename list<Vertex<V, E>>::iterator m_vector;
//};
//
//
//template<typename V, typename E>
//GraphVertexIterator<V, E>::GraphVertexIterator(Graph<V, E> & graph)
//	: m_graph(&graph)
//{}
//
//template<typename V, typename E>
//GraphVertexIterator<V, E>::GraphVertexIterator(const GraphVertexIterator<V, E> & copy)
//	: m_graph(copy.m_graph), m_vector(copy.m_vector)
//{}
//
//template<typename V, typename E>
//GraphVertexIterator<V, E>::~GraphVertexIterator()
//{
//	m_vector = m_graph->m_vertices.end();
//	m_graph = nullptr;
//}
//
//template<typename V, typename E>
//GraphVertexIterator<V, E> & GraphVertexIterator<V, E>::operator=(const GraphVertexIterator<V, E> & rhs)
//{
//	if (this != &rhs)
//	{
//		m_graph = rhs.m_graph;
//		m_vector = rhs.m_vector;
//	}
//
//	return *this;
//}
//
//template<typename V, typename E>
//void GraphVertexIterator<V, E>::Reset()
//{
//	m_vector = m_graph->m_vertices.begin();
//}
//
//template<typename V, typename E>
//void GraphVertexIterator<V, E>::MoveNext()
//{
//	if (IsDone())
//		throw Exception("Cannot access next element! Iterator is done...");
//
//	++m_vector;
//}
//
//template<typename V, typename E>
//Vertex<V, E> & GraphVertexIterator<V, E>::GetCurrent()
//{
//	if (IsDone())
//		throw Exception("Cannot access current element! Iterator is done...");
//
//	return (*m_vector);
//}
//
//template<typename V, typename E>
//bool GraphVertexIterator<V, E>::IsDone() const
//{
//	return (m_vector == m_graph->m_vertices.end());
//}
//
//#endif // GRAPHVERTEXITERATOR_H
//
