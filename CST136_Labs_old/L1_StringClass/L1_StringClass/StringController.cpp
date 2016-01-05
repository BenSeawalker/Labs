#include "StringController.h"
#include <Windows.h>  // does not need to be imported everywhere...

const int BUFFER_LEN = String::BUFFER_LEN;

/////////////////////////////////////////////////
// C'TOR / D'TOR
/////////

	StringController::StringController()
		: m_numNames(0), m_namesPerLine(1)
	{}


	StringController::~StringController()
	{}


/////////////////////////////////////////////////
// PUBLIC
/////////

	// Prompt the user for all relevant information
	void StringController::GetNames()
	{
		// reset names / namesPerLine
		m_numNames = 0;
		m_namesPerLine = 0;


		// prompt for number of names
		while (m_numNames <= 0 || m_numNames > NUM_NAMES)
		{
			CleanInput(); // clean up errors

			cout << endl << "Please enter the number of names you wish to enter.\nBetween 1 & " << NUM_NAMES << endl
				<< "Input: ";
			cin >> m_numNames;
		}


		// prompt for number of names per line:
		while (m_namesPerLine <= 0 || m_namesPerLine > NUM_NAMES)
		{
			CleanInput(); // clean up errors

			cout << endl << "Please enter the number of names per line.\nBetween 1 & " << NUM_NAMES << endl
				<< "Input: ";
			cin >> m_namesPerLine;
		}


		//prompt for names
		for (int i = 0; i < m_numNames; ++i)
		{
			CleanInput(); // clean up errors

			cout << endl << "Enter a name: ";

			char buffer[BUFFER_LEN];
			cin.getline(buffer, BUFFER_LEN); // read name into temp buffer

			m_names[i].SetBuffer(buffer); // update String with user input
		}


		// check string length...
		//CheckWidth();


		// aesthetics...
		cout << endl;
	}

	// Display all names to the screen and "Names.txt" in the proper format
	void StringController::Display()
	{
		CONSOLE_SCREEN_BUFFER_INFO csbi;
		if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi))
		{
			int console_width = csbi.srWindow.Right - csbi.srWindow.Left;

			stringstream stream; // to buffer display data

			ofstream file("Names.txt"); // attempt to open file

			// add the display data to the stream
			int names_width = 0;
			int i_check = 0;
			for (int i = 0; i < m_numNames; ++i)
			{
				names_width += m_names[i].StrLen();

				if ((i_check++ % m_namesPerLine == 0)) // insert newlines when namesPerLine is reached
				{
					names_width = m_names[i].StrLen();
					stream << endl;
				}
				else if (names_width >= console_width && i_check > 1) // insert new line if name is too long
				{
					i_check = 1;
					names_width = m_names[i].StrLen();
					stream << endl;
				}

				m_names[i].Display(stream); // "Display" the String to the stream
				stream << " ";
			}

			// Screen
			cout << stream.str() << endl << endl; // Print stream to screen

			// File
			if (file.is_open())
				file << stream.str(); // Print stream to file
			else
				throw "Failed to open file";
		}
		else
			throw "Unable to get console width";
	}


	// GET NamesPerLine
	UINT StringController::NamesPerLine()
	{
		return m_namesPerLine;
	}

	// SET NamesPerLine
	void StringController::NamesPerLine(int _namesPerLine)
	{
		m_namesPerLine = _namesPerLine;

		// Ensure the value is within limits
		if (m_namesPerLine < 1)
			m_namesPerLine = 1;

		if (m_namesPerLine > NUM_NAMES)
			m_namesPerLine = NUM_NAMES;
	}


/////////////////////////////////////////////////
// PRIVATE
/////////

	/*
		This recursively shrinks the names_per_line until all names fit
	*/
	void StringController::CheckWidth(bool _tooWide)
	{
		CONSOLE_SCREEN_BUFFER_INFO csbi;
		if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi))
		{
			int width = csbi.srWindow.Right - csbi.srWindow.Left;

			bool is_too_wide = false;
			int names_width = 0;
			for (UINT i = 0; i < NUM_NAMES && !is_too_wide; ++i)
			{
				if (i % m_namesPerLine == 0)
					names_width = 0;

				names_width += m_names[i].StrLen();

				is_too_wide = (names_width >= width);
			}

			if (is_too_wide && m_namesPerLine > 1)
			{
				m_namesPerLine -= 1;

				CheckWidth(is_too_wide);
			}
			else if(_tooWide)
				cout << "\nNames to wide for console, decreasing Names Per Line to: " << m_namesPerLine << endl;

		}
		else
			throw "Unable to get console width";
	}

	// clear errors and clean out the console input buffer
	void StringController::CleanInput()
	{
		cin.clear();
		cin.ignore(cin.rdbuf()->in_avail());
	}


