#ifndef MSACTION_H
#define MSACTION_H

#include "HistoryAction.h"
#include "Cell.h"

class MSAction : HistoryAction
{
public:
	MSAction(Cell old_cell, Cell new_cell, Cell & cell)
		: m_old(old_cell), m_new(new_cell), m_cell(cell)
	{}

	virtual void Undo()
	{
		
	}

	virtual void Redo()
	{
		
	}

private:
	Cell m_old;
	Cell m_new;
	Cell & m_cell;
};

#endif // MSACTION_H
