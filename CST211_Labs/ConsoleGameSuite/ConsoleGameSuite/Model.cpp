#include "Model.h"
#include "View.h"
#include "ListIterator.h"

void Model::Register(View & view)
{
	m_views.Extract(&view);
	m_views.Append(&view);
}

void Model::Remove(View & view)
{
	m_views.Extract(&view);
}

void Model::Notify()
{
	for (ListIterator<View *> iter(&m_views); !iter.IsDone(); iter.MoveNext())
		iter.GetCurrent()->ModelUpdated();
}
