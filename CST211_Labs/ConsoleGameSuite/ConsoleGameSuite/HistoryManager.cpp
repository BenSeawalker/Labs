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

HistoryManager & HistoryManager::GetInstance()
{
	return m_instance;
}

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

void HistoryManager::AddUndo(HistoryAction * undo)
{
	// Clean out redo cache
	while (!m_redos.isEmpty())
		delete m_redos.Pop();

	m_undos.Push(undo);
}

void HistoryManager::Undo()
{
	if (!m_undos.isEmpty())
	{
		HistoryAction * action = m_undos.Pop();
		action->Undo();

		m_redos.Push(action);
	}
}

void HistoryManager::Redo()
{
	if (!m_redos.isEmpty())
	{
		HistoryAction * action = m_redos.Pop();
		action->Redo();

		m_undos.Push(action);
	}
}

void HistoryManager::Update()
{
	if (Keyboard::KeyDown(VK_CONTROL))
	{
		if (Keyboard::KeyPressed('Z'))
			Undo();
		else if (Keyboard::KeyPressed('Y'))
			Redo();
	}
}
