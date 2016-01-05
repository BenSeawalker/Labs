#ifndef LinkedList_h__
#define LinkedList_h__

template<typename NT>
struct Node
{
	NT * data;
	Node<NT> * next;

	Node<NT>(NT * _data) : data(_data), next(nullptr) {};
	~Node<NT>() { delete data; };
};

template <class T>
class LinkedList
{
public:
	LinkedList();
	~LinkedList();

	void Prepend(T * _item);

	void Traverse(void(*Visit)(T * _item));

private:
	Node<T> * m_head;
};


template<class T>
LinkedList<T>::LinkedList()
	: m_head(nullptr)
{}

template<class T>
LinkedList<T>::~LinkedList()
{
	Node<T> * travel = m_head;
	Node<T> * trail = nullptr;

	while (travel)
	{
		trail = travel;
		travel = travel->next;
		
		delete trail;
	}
}


template<class T>
void LinkedList<T>::Prepend(T * _item)
{
	Node<T> * new_node = new Node<T>(_item);

	new_node->next = m_head;
	m_head = new_node;
}


template<class T>
void LinkedList<T>::Traverse(void(*Visit)(T *_item))
{
	Node<T> * travel = m_head;

	while (travel)
	{
		Visit(travel->data);
		travel = travel->next;
	}
}



#endif // LinkedList_h__