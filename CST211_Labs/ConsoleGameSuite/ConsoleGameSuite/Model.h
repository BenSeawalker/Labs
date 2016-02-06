#ifndef MODEL_H
#define MODEL_H


#include "DoubleLinkedList.h"

class View;

class Model
{
public:
	void Register(View & view);
	void Remove(View & view);
	void Notify();

private:
	Model();

	DoubleLinkedList<View *> m_views;
};

#endif // MODEL_H
