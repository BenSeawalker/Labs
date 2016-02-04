#ifndef UNDO_H
#define UNDO_H

class HistoryAction
{
	friend class HistoryManager;

private:
	virtual void Undo() = 0;
	virtual void Redo() = 0;
};

#endif // UNDO_H
