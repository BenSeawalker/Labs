#ifndef MODEL_H
#define MODEL_H

#include "DoubleLinkedList.h"

class View;

class Model
{
public:
	virtual ~Model();

	void Register(View & view);
	void Remove(View & view);
	
protected:
	Model();
	Model(const Model & copy);

	Model & operator=(const Model & rhs);

	void Notify();

private:
	DoubleLinkedList<View *> m_views;
};

#endif // MODEL_H
