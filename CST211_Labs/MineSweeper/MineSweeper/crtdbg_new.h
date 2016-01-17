#ifndef CRTDBG_NEW_H
#define CRTDBG_NEW_H

#include <crtdbg.h> 

#ifdef _DEBUG
	#define _CRTDBG_MAP_ALLOC
	#define new new( _CLIENT_BLOCK, __FILE__, __LINE__)
#endif // _DEBUG

#endif // CRTDBG_NEW_H