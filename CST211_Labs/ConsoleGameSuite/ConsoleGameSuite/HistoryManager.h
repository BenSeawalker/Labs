#ifndef UNDOMANAGER_H
#define UNDOMANAGER_H

#include "LStack.h"
#include "HistoryAction.h"
#include "Keyboard.h"

class HistoryManager
{
public:
	// DTOR
	~HistoryManager();

	// METHODS
	static void AddAction(HistoryAction * undo);
	static void RemoveActions(void * me);

	static void Undo();
	static void Redo();

	static void Update();
	static void ClearCache();

	static bool DidUndo();
	static bool DidRedo();
	static bool DidChange();

private:
	// CTORS
	HistoryManager();
	HistoryManager(const HistoryManager & copy);
	
	// OPERATOR
	HistoryManager & operator=(const HistoryManager & rhs);

	// SINGLETON INSTANCE FOR MEMORY MANAGEMENT
	static HistoryManager m_instance;

	// MEMBERS
	LStack<HistoryAction *> m_undos;
	LStack<HistoryAction *> m_redos;
	bool m_undid;
	bool m_redid;
};

#endif // UNDOMANAGER_H
