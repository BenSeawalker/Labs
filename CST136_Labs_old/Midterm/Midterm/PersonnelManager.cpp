#include "PersonnelManager.h"


PersonnelManager::PersonnelManager(String fileName)
{
	m_list = new LinkedList<Personnel>();

	ReadFile(fileName);
}


PersonnelManager::~PersonnelManager()
{
	delete m_list;
}

void PersonnelManager::ReadFile(String _fileName)
{
	ifstream file(_fileName);

	if (file.is_open())
	{
		while (!file.eof())
		{
			string line;

			getline(file, line);

			ProcessCommand(stringstream(line));
		}
	}
}

void PersonnelManager::ProcessCommand(stringstream _args)
{
	char cmd;

	_args >> cmd;

	if (cmd == 'I')
	{
		int workNum;
		char LName[10];

		_args >> workNum;
		_args.getline(LName, 10);

		m_list->Prepend(new Personnel(workNum, LName));
	}
	else if (cmd == 'P')
	{
		m_list->Traverse(&Personnel::DisplayPersonnel);
	}
	else
		cout << "Unknown command: \"" << cmd << "\"" << endl;
}
