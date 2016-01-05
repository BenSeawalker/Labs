#include <iostream>

#include "StringController.h"

int main()
{
	try
	{
		StringController Controller; // Instantiate the controller

		Controller.GetNames();		 // Read in names from the user
		
		Controller.Display();		 // Display input to the screen and .txt file

	}
	// catch user errors
	catch(const char * ex)
	{
		cout << "ERROR! " << ex;
	}
	// catch system errors
	catch (const std::exception &ex)
	{
		cout << "ERROR!\n" << ex.what();
	}

	return 0;
}