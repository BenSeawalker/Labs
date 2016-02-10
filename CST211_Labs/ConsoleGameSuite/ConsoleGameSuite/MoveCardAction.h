#ifndef MSACTION_H
#define MSACTION_H

#include "HistoryAction.h"
#include "FCBoard.h"

class MoveCardAction : public HistoryAction
{
public:
	MoveCardAction(FCBoard & board, FCBoard::AREA from, FCBoard::AREA to, int src, int dest, int depth);

private:
	virtual void Undo();
	virtual void Redo();

	virtual bool Contains(void * item);

	FCBoard & m_board;
	FCBoard::AREA m_from;
	FCBoard::AREA m_to;
	int m_src;
	int m_dest;
	int m_depth;
};

#endif // MSACTION_H

