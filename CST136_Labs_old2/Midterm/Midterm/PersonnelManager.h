#ifndef PersonnelManager_h__
#define PersonnelManager_h__

#include <string>
using std::string;

#include <fstream>
using std::ifstream;

#include <sstream>
using std::stringstream;


#include "Personnel.h"
#include "LinkedList.h"


class PersonnelManager
{
public:
	typedef const string & String;

	PersonnelManager(String _fileName);
	~PersonnelManager();

private:
	LinkedList<Personnel> * m_list;


	void ReadFile(String _fileName);

	void ProcessCommand(stringstream _args);
};


#endif // PersonnelManager_h__