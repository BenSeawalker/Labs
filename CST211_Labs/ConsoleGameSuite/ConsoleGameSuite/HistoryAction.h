#ifndef UNDO_H
#define UNDO_H

class HistoryAction
{
public:
	virtual void Undo() = 0;
	virtual void Redo() = 0;
private:

};

#endif // UNDO_H
