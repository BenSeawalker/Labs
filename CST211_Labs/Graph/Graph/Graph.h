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

namespace NSGraph
{
	/************************************************************************
	* Struct: VertexCopy
	*
	* Purpose: This struct stores pointers to original and copied Vertices
				for use in DeepCopy(). (To update copied Arc destinations)
	*
	* Manager functions:
	* 	VertexCopy(original : const Vertex<V, E> *, copy : Vertex<V, E> *)
	*
	* Methods:
	*
	*	Original() : const Vertex<V, E> *
	*
	*	Copy() : Vertex<V, E> *
	*
	*************************************************************************/
	template<typename V, typename E>
	struct VertexCopy
	{
	public:
		VertexCopy<V, E>(const Vertex<V, E> * original, Vertex<V, E> * copy)
			: m_original(original), m_copy(copy)
		{}

		const Vertex<V, E> * Original() const
		{
			return m_original;
		}

		Vertex<V, E> * Copy() const
		{
			return m_copy;
		}

	private:
		const Vertex<V, E> * m_original;
		Vertex<V, E> * m_copy;
	};


	/************************************************************************
	* Class: Graph
	*
	* Purpose: This class implements a multi-list Graph ADT for storing Vertices
	*
	* Manager functions:
	* 	Graph()
	*
	*	Graph(const Graph & copy)
	*	operator = (const Graph & copy)
	*
	*	~Graph()
	*
	* Methods:
	*
	*	InsertVertex(data : const V &) : void
	*	DeleteVertex(data : const V &) : bool
	*
	*	InsertArc(from : const V &, to : const V &, data : const E &, weight : int) : void
	*	DeleteArc(from : const V &, to : const V &, data : const E &) : bool
	*
	*	BreadthFirst(visit : Visit_t) : void
	*	DepthFirst(visit : Visit_t) : void
	*
	*	IsEmpty() : bool const
	*
	*	Purge() : void
	*
	*************************************************************************/
	template<typename V, typename E>
	class Graph
	{
	public:
		// TYPEDEFS
		typedef void(*Visit_t)(V & data);
		//typedef list<Vertex<V, E>> vertices_t;
		typedef list<Arc<V, E>> arcs_t;

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

		// No const versions as "processed" needs to be toggled
		void BreadthFirst(Visit_t visit);
		void DepthFirst(Visit_t visit);

		const list<Vertex<V, E>> & Vertices() const;
		const Vertex<V, E> * FindVertex(const V & data) const;
		const Arc<V, E> * FindArc(const V & from, const V & to) const;

		void ProcessVertices(bool processed) const;

		bool Contains(const V & data);

		bool IsEmpty() const;

		void Purge();

	private:
		// METHODS
		Vertex<V, E> * FindVertex(const V & data);
		Arc<V, E> * FindArc(Vertex<V, E> * v_from, Vertex<V, E> * v_to, const E & data);

		

		void DeepCopy(const Graph<V, E> & copy);
		const VertexCopy<V, E> * FindVertexCopy(const list<VertexCopy<V, E>> & copy_list, const Vertex<V, E> * original);

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
	{
		DeepCopy(copy);
	}

	template<typename V, typename E>
	Graph<V, E>::~Graph()
	{}

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
			m_vertices.clear();
			DeepCopy(rhs);
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

	/************************************************************************
	* Purpose: Allow the consumer to insert a vertex
	*
	* Precondition:
	*	@data : data to copy into the new Vertex
	*
	* Postcondition:
	*		Modifies:	m_vertices
	*		Throws:		N/A
	*		Returns:	N/A
	*************************************************************************/
	template<typename V, typename E>
	void Graph<V, E>::InsertVertex(const V & data)
	{
		m_vertices.push_back(Vertex<V, E>(data));
	}


	/************************************************************************
	* Purpose: Allow the consumer to delete a matching vertex
	*
	* Precondition:
	*	@data : data that matching vertex must contain
	*
	* Postcondition:
	*		Modifies:	m_vertices
	*		Throws:		N/A
	*		Returns:	TRUE if matching vertex was found
	*************************************************************************/
	template<typename V, typename E>
	bool Graph<V, E>::DeleteVertex(const V & data)
	{
		Vertex<V, E> * found = FindVertex(data);

		if (found)
		{
			// Remove all arcs with found vertex as their destination
			arcs_t::iterator iter;
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

	/************************************************************************
	* Purpose: Allow the consumer to insert an arc
	*
	* Precondition:
	*	@from : matching vertex to start at - matching vertex must exist
	*	@to : matching vertex for destination - matching vertex must exist
	*	@data : data to copy into new Arc
	*
	* Postcondition:
	*		Modifies:	from->m_arcs, to->m_arcs
	*		Throws:		Exception("Error inserting Arc! Vertex not found.")
	*		Returns:	N/A
	*************************************************************************/
	template<typename V, typename E>
	void Graph<V, E>::InsertArc(const V & from, const V & to, const E & data, int weight)
	{
		Vertex<V, E> * v_from = FindVertex(from);
		Vertex<V, E> * v_to = FindVertex(to);

		if (!v_from || !v_to)
			throw Exception("Error inserting Arc! Vertex not found.");

		// Arc must be bi-directional...
		v_from->Arcs().push_back(Arc<V, E>(data, weight, v_to));
		v_to->Arcs().push_back(Arc<V, E>(data, weight, v_from));
	}


	/************************************************************************
	* Purpose: Allow the consumer to delete an arc
	*
	* Precondition:
	*	@from : matching vertex to start at - matching vertex must exist
	*	@to : matching vertex for destination - matching vertex must exist
	*	@data : data that matching arcs must contain
	*
	* Postcondition:
	*		Modifies:	from->m_arcs, to->m_arcs
	*		Throws:		Exception("Error deleting Arc! Vertex not found.")
	*		Returns:	TRUE if matching arcs are found
	*************************************************************************/
	template<typename V, typename E>
	bool Graph<V, E>::DeleteArc(const V & from, const V & to, const E & data)
	{
		Vertex<V, E> * v_from = FindVertex(from);
		Vertex<V, E> * v_to = FindVertex(to);

		if (!v_from || !v_to)
			throw Exception("Error deleting Arc! Vertex not found.");

		// Remove bi-directional arc between from and to vertices 
		Arc<V, E> * arc_from = FindArc(v_from, v_to, data);
		Arc<V, E> * arc_to = FindArc(v_to, v_from, data);
		if (arc_from && arc_to)
		{
			v_from->Arcs().remove(*arc_from);
			v_to->Arcs().remove(*arc_to);
		}

		return (arc_from && arc_to);
	}


	// * TRAVERSALS * //

	/************************************************************************
	* Purpose: Allow the consumer to iterate over the graph in a breadth-first manner
	*
	* Precondition:
	*	@visit : function to be passed the data to
	*	Note: cannot be const as "processed" must be toggled
	*
	* Postcondition:
	*		Modifies:	N/A
	*		Throws:		N/A
	*		Returns:	N/A
	*************************************************************************/
	template<typename V, typename E>
	void Graph<V, E>::BreadthFirst(Visit_t visit)
	{
		queue<Vertex<V, E> *> v_queue;
		v_queue.push(&m_vertices.front());
		m_vertices.front().Processed() = true;

		while (v_queue.size() > 0)
		{
			Vertex<V, E> * vertex = v_queue.front();
			v_queue.pop();
			visit(vertex->Data());

			// Add connected destinations to queue, and mark them as processed
			arcs_t::iterator arc;
			for (arc = vertex->Arcs().begin(); arc != vertex->Arcs().end(); ++arc)
			{
				if (!arc->Destination()->Processed())
				{
					v_queue.push(arc->Destination());
					arc->Destination()->Processed() = true;
				}
			}
		}

		// Mark all vertices as unprocessed
		ProcessVertices(false);
	}

	/************************************************************************
	* Purpose: Allow the consumer to iterate over the graph in a depth-first manner
	*
	* Precondition:
	*	@visit : function to be passed the data to
	*	Note: cannot be const as "processed" must be toggled for each vertex
	*
	* Postcondition:
	*		Modifies:	N/A
	*		Throws:		N/A
	*		Returns:	N/A
	*************************************************************************/
	template<typename V, typename E>
	void Graph<V, E>::DepthFirst(Visit_t visit)
	{
		stack<Vertex<V, E> *> v_stack;
		v_stack.push(&m_vertices.front());
		m_vertices.front().Processed() = true;

		while (v_stack.size() > 0)
		{
			Vertex<V, E> * vertex = v_stack.top();
			v_stack.pop();
			visit(vertex->Data());

			// Add connected destinations to stack, and mark them as processed
			arcs_t::iterator arc;
			for (arc = vertex->Arcs().begin(); arc != vertex->Arcs().end(); ++arc)
			{
				if (!arc->Destination()->Processed())
				{
					v_stack.push(arc->Destination());
					arc->Destination()->Processed() = true;
				}
			}
		}

		// Mark all vertices as unprocessed
		ProcessVertices(false);
	}

	template<typename V, typename E>
	const list<Vertex<V, E>> & Graph<V, E>::Vertices() const
	{
		return m_vertices;
	}

	template<typename V, typename E>
	const Vertex<V, E> * Graph<V, E>::FindVertex(const V & data) const
	{
		const Vertex<V, E> * found = nullptr;

		list<Vertex<V, E>>::const_iterator vertex;
		for (vertex = m_vertices.begin(); !found && vertex != m_vertices.end(); ++vertex)
		{
			if (vertex->Data() == data)
				found = &(*vertex);
		}

		return found;
	}

	template<typename V, typename E>
	const Arc<V, E>* Graph<V, E>::FindArc(const V & from, const V & to) const
	{
		const Arc<V, E> * found = nullptr;
		const Vertex<V, E> * v_from = FindVertex(from);
		const Vertex<V, E> * v_to = FindVertex(to);

		arcs_t::const_iterator arc;
		for (arc = v_from->Arcs().begin(); arc != v_from->Arcs().end() && !found; ++arc)
		{
			if (arc->Destination() == v_to)
				found = &(*arc);
		}

		return found;
	}


	// * MISC * //

	template<typename V, typename E>
	bool Graph<V, E>::Contains(const V & data)
	{
		bool found = false;

		list<Vertex<V, E>>::iterator vertex;
		for (vertex = m_vertices.begin(); !found && vertex != m_vertices.end(); ++vertex)
			found = (vertex->Data() == data);

		return found;
	}

	template<typename V, typename E>
	bool Graph<V, E>::IsEmpty() const
	{
		return (m_vertices.size() == 0);
	}

	template<typename V, typename E>
	void Graph<V, E>::Purge()
	{
		m_vertices.clear();
	}

	//////
	//	END PUBLIC METHODS
	///////////////////////////////////////////////////////////////

	///////////////////////////////////////////////////////////////
	//	PRIVATE METHODS
	//////

	/************************************************************************
	* Purpose: Find and return a vertex containing matching data
	*
	* Precondition:
	*	@data : data that matching vertex must contain
	*
	* Postcondition:
	*		Modifies:	N/A
	*		Throws:		N/A
	*		Returns:	Pointer to found Vertex or nullptr
	*************************************************************************/
	template<typename V, typename E>
	Vertex<V, E> * Graph<V, E>::FindVertex(const V & data)
	{
		Vertex<V, E> * found = nullptr;

		list<Vertex<V, E>>::iterator vertex;
		for (vertex = m_vertices.begin(); vertex != m_vertices.end() && !found; ++vertex)
		{
			if (vertex->Data() == data)
				found = &(*vertex);
		}

		return found;
	}

	/************************************************************************
	* Purpose: Find and return an arc containing matching data
	*
	* Precondition:
	*	@v_from : source vertex
	*	@v_to : destination vertex
	*	@data : data that matching arc must contain
	*
	* Postcondition:
	*		Modifies:	N/A
	*		Throws:		N/A
	*		Returns:	Pointer to found Arc or nullptr
	*************************************************************************/
	template<typename V, typename E>
	Arc<V, E> * Graph<V, E>::FindArc(Vertex<V, E> * v_from, Vertex<V, E> * v_to, const E & data)
	{
		Arc<V, E> * found = nullptr;

		arcs_t::iterator arc;
		for (arc = v_from->Arcs().begin(); arc != v_from->Arcs().end() && !found; ++arc)
		{
			if (arc->Destination() == v_to && arc->Data() == data)
				found = &(*arc);
		}

		return found;
	}

	/************************************************************************
	* Purpose: Set the "processed" status of all vertices
	*
	* Precondition:
	*	@processed : resulting processed state of all vertices
	*
	* Postcondition:
	*		Modifies:	m_processed of all vertices
	*		Throws:		N/A
	*		Returns:	N/A
	*************************************************************************/
	template<typename V, typename E>
	void Graph<V, E>::ProcessVertices(bool processed) const
	{
		list<Vertex<V, E>>::const_iterator vertex;
		for (vertex = m_vertices.begin(); vertex != m_vertices.end(); ++vertex)
			vertex->Processed() = processed;
	}

	/************************************************************************
	* Purpose: Ensure that all copied Arcs point to the copied destination
	*
	* Precondition:
	*	@copy : graph to copy
	*
	* Postcondition:
	*		Modifies:	m_vertices
	*		Throws:		N/A
	*		Returns:	N/A
	*************************************************************************/
	template<typename V, typename E>
	void Graph<V, E>::DeepCopy(const Graph<V, E> & copy)
	{
		list<VertexCopy<V, E>> copy_list;

		// COPY ALL VERTICES INTO THIS LIST
		// PUSH POINTERS TO ORIGINAL AND COPIED VERTEX'S INTO @copy_list
		list<Vertex<V, E>>::const_iterator copy_vertex;
		for (copy_vertex = copy.m_vertices.begin(); copy_vertex != copy.m_vertices.end(); ++copy_vertex)
		{
			m_vertices.push_back(Vertex<V, E>(*copy_vertex));
			copy_list.push_back(VertexCopy<V, E>(&(*copy_vertex), &(m_vertices.back())));
		}

		// UPDATE ALL COPIED ARC'S DESTINATIONS WITH THE CORRESPONDING COPIED VERTEX
		list<Vertex<V, E>>::iterator vertex;
		for (vertex = m_vertices.begin(); vertex != m_vertices.end(); ++vertex)
		{
			arcs_t::iterator arc;
			for (arc = vertex->Arcs().begin(); arc != vertex->Arcs().end(); ++arc)
			{
				const VertexCopy<V, E> * found = FindVertexCopy(copy_list, arc->Destination());
				arc->Destination() = found->Copy();
			}
		}
	}


	/************************************************************************
	* Purpose: Find and return a VertexCopy with matching original pointer
	*
	* Precondition:
	*	@copy_list : list of VertexCopy's to search through
	*	@original : pointer to original vertex
	*
	* Postcondition:
	*		Modifies:	N/A
	*		Throws:		N/A
	*		Returns:	Pointer to found VertexCopy or nullptr
	*************************************************************************/
	template<typename V, typename E>
	const VertexCopy<V, E> * Graph<V, E>::FindVertexCopy(const list<VertexCopy<V, E>> & copy_list, const Vertex<V, E> * original)
	{
		const VertexCopy<V, E> * found = nullptr;

		list<VertexCopy<V, E>>::const_iterator vertex_copy;
		for (vertex_copy = copy_list.begin(); vertex_copy != copy_list.end() && !found; ++vertex_copy)
		{
			if (vertex_copy->Original() == original)
				found = &(*vertex_copy);
		}

		return found;
	}

	//////
	//	END PRIVATE METHODS
	///////////////////////////////////////////////////////////////
}

#endif // GRAPH_H


