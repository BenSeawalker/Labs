#pragma once

typedef unsigned int UINT;

template<typename T>
class Array
{
public:
	Array(UINT _size = 0);
	~Array();

	UINT Size() { return m_size; };

	void Insert(T * _item);

	T * operator[](UINT _index);

private:
	UINT m_maxSize;
	UINT m_size;
	T ** m_array;
};


template<typename T>
Array<T>::Array(UINT _size)
	: m_maxSize(_size), m_size(0), m_array(nullptr)
{
	if (m_maxSize > 0)
		m_array = new T*[m_maxSize];
}

template<typename T>
Array<T>::~Array()
{
	for (UINT i = 0; i < m_size; i++)
		delete m_array[i];

	delete[] m_array;
}

template<typename T>
void Array<T>::Insert(T * _item)
{
	if (m_size < m_maxSize)
	{
		if (m_size == 0)
			m_array[0] = _item;
		else
		{
			bool found = false;
			for (UINT i = 0; i < m_size && !found; ++i)
			{
				if (*_item < *(m_array[i]))
				{
					for (UINT ii = (m_maxSize - 1); ii > i; --ii)
						m_array[ii] = m_array[ii - 1];

					m_array[i] = _item;
					found = true;
				}
			}
			if (!found)
				m_array[m_size] = _item;
		}

		m_size++;
	}
}

template<typename T>
T * Array<T>::operator[](UINT _index)
{
	return m_array[_index];
}
