#include "HistoryManager.h"

///////////////////////////////////////////////////////////////
//	INITIALIZE SINGLETON
//////

HistoryManager HistoryManager::m_instance = HistoryManager();

//////
//	END INITIALIZE SINGLETON
///////////////////////////////////////////////////////////////

HistoryManager::HistoryManager()
{}

HistoryManager::HistoryManager(const HistoryManager & copy)
{}

HistoryManager::~HistoryManager()
{
	while (!m_undos.isEmpty())
		delete m_undos.Pop();

	while (!m_redos.isEmpty())
		delete m_redos.Pop();
}

HistoryManager & HistoryManager::operator=(const HistoryManager & rhs)
{
	return *this;
}

void HistoryManager::AddAction(HistoryAction * undo)
{
	// Clean out redo cache
	while (!m_instance.m_redos.isEmpty())
		delete m_instance.m_redos.Pop();

	m_instance.m_undos.Push(undo);
}

void HistoryManager::RemoveActions(void * me)
{
	LStack<HistoryAction *> temp;

	while (!m_instance.m_undos.isEmpty())
		temp.Push(m_instance.m_undos.Pop());

	while (!temp.isEmpty())
	{
		if (temp.Peek()->Contains(me))
			delete temp.Pop();
		else
			m_instance.m_undos.Push(temp.Pop());
	}

	while (!m_instance.m_redos.isEmpty())
		temp.Push(m_instance.m_redos.Pop());

	while (!temp.isEmpty())
	{
		if (temp.Peek()->Contains(me))
			delete temp.Pop();
		else
			m_instance.m_redos.Push(temp.Pop());
	}
}

void HistoryManager::Undo()
{
	if (!m_instance.m_undos.isEmpty())
	{
		HistoryAction * action = m_instance.m_undos.Pop();
		action->Undo();

		m_instance.m_redos.Push(action);
		m_instance.m_undid = true;
	}
}

void HistoryManager::Redo()
{
	if (!m_instance.m_redos.isEmpty())
	{
		HistoryAction * action = m_instance.m_redos.Pop();
		action->Redo();

		m_instance.m_undos.Push(action);
		m_instance.m_redid = true;
	}
}

void HistoryManager::Update()
{
	m_instance.m_undid = false;
	m_instance.m_redid = false;

	if (Keyboard::KeyDown(VK_CONTROL))
	{
		if (Keyboard::KeyPressed('Z'))
			Undo();
		else if (Keyboard::KeyPressed('Y'))
			Redo();
	}
}

void HistoryManager::ClearCache()
{
	while (!m_instance.m_undos.isEmpty())
		delete m_instance.m_undos.Pop();

	while (!m_instance.m_redos.isEmpty())
		delete m_instance.m_redos.Pop();
}

bool HistoryManager::DidUndo()
{
	return m_instance.m_undid;
}

bool HistoryManager::DidRedo()
{
	return m_instance.m_redid;
}

bool HistoryManager::DidChange()
{
	return (DidUndo() || DidChange());
}
