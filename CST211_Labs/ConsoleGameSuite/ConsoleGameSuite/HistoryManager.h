#ifndef UNDOMANAGER_H
#define UNDOMANAGER_H

#include "LStack.h"
#include "HistoryAction.h"
#include "Keyboard.h"

class HistoryManager
{
public:
	// SINGLETON
	static HistoryManager & GetInstance();

	// DTOR
	~HistoryManager();

	// METHODS
	void AddUndo(HistoryAction * undo);

	void Undo();
	void Redo();

	void Update();

private:
	// CTORS
	HistoryManager();
	HistoryManager(const HistoryManager & copy);
	
	// OPERATOR
	HistoryManager & operator=(const HistoryManager & rhs);

	// SINGLETON
	static HistoryManager m_instance;

	// MEMBERS
	LStack<HistoryAction *> m_undos;
	LStack<HistoryAction *> m_redos;
};

#endif // UNDOMANAGER_H
