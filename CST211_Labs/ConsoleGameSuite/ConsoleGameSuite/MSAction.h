#ifndef MSACTION_H
#define MSACTION_H

#include "HistoryAction.h"
#include "MSBoard.h"

class MSAction : public HistoryAction
{
public:
	MSAction(MSBoard old_board, MSBoard new_board, MSBoard & board)
		: m_old(old_board), m_new(new_board), m_board(board)
	{}

private:
	virtual void Undo()
	{
		m_board = m_old;
	}

	virtual void Redo()
	{
		m_board = m_new;
	}

	MSBoard m_old;
	MSBoard m_new;
	MSBoard & m_board;
};

#endif // MSACTION_H
