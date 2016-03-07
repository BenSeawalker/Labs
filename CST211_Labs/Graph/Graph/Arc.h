/************************************************************************
* Author:		Garrett Fleischer
* Filename:		Arc.h
* Date Created:	2/27/16
* Modifications:
*************************************************************************/
#ifndef ARC_H
#define ARC_H

namespace NSGraph
{
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
	class Arc
	{
	public:
		// CTORS & DTOR
		Arc(const E & data, int weight, Vertex<V, E> * dest);
		Arc(const Arc<V, E> & copy);

		~Arc();

		// OPERATORS
		Arc<V, E> & operator=(const Arc<V, E> & rhs);
		bool operator==(const Arc<V, E> & rhs) const;

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
	Arc<V, E>::Arc(const E & data, int weight, Vertex<V, E> * dest)
		: m_data(data), m_weight(weight), m_dest(dest)
	{}

	template<typename V, typename E>
	Arc<V, E>::Arc(const Arc<V, E> & copy)
		: m_data(copy.m_data), m_weight(copy.m_weight), m_dest(copy.m_dest)
	{}

	template<typename V, typename E>
	Arc<V, E>::~Arc()
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
	Arc<V, E> & Arc<V, E>::operator=(const Arc<V, E> & rhs)
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
	bool Arc<V, E>::operator==(const Arc<V, E> & rhs) const
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
	E & Arc<V, E>::Data()
	{
		return m_data;
	}

	template<typename V, typename E>
	const E & Arc<V, E>::Data() const
	{
		return m_data;
	}

	template<typename V, typename E>
	int & Arc<V, E>::Weight()
	{
		return m_weight;
	}

	template<typename V, typename E>
	const int & Arc<V, E>::Weight() const
	{
		return m_weight;
	}

	template<typename V, typename E>
	Vertex<V, E>*& Arc<V, E>::Destination()
	{
		return m_dest;
	}

	template<typename V, typename E>
	const Vertex<V, E>* Arc<V, E>::Destination() const
	{
		return m_dest;
	}

	//////
	//	END GETTERS
	///////////////////////////////////////////////////////////////

}

#endif // ARC_H


