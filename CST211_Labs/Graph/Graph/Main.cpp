/*****************************************************************************************
Author:			Garrett Fleischer
Filename:		Main.cpp
Date Created:	2/27/16
Modifications:

Lab/Assignment: Lab 5

Overview: Test of Dijkstra's algorithm with Graph class

NOTE:	My Dijkstra's algorithm puts precedence on shortest travel time.
		So, if it chooses I-5 more often than yours, that is the reason.
	
		Vertex::m_processed has been made mutable so it can be modified in a const Vertex object.
		In many instances the users of a graph will need direct access to the Vertex and Arc classes,
		however we don't want them to change destination pointers or directly add/remove Arc's to the vertices.
		Furthermore, m_processed is used in many algorithms. As such, in this case, I deem it a clean and
		viable solution to mark it as mutable, so that my Graph can return const Arcs and Vertices, while still allowing
		m_processed to be toggled.

Input: Input is retrieved from the user and consists of a start and destination city

Output: The output for this program is to the console window and consists of error statements and the shortest path
between the given cities.

The output will have the following form:

------------------------------------------------------------------------------------------

Directions from ... to ... # miles
Travel time: # hour(s) # minute(s)

    city -> road - # miles
	    ...
	destination

*****************************************************************************************/

#include "crtdbg_new.h"

#include <windows.h>

#include <climits>
#include <cfloat>
#include <string>
using std::string;
#include <fstream>
using std::ifstream;
#include <iostream>
using std::ostream;
using std::cin;
using std::cout;
using std::endl;
#include <list>
using std::list;
#include <vector>
using std::vector;

#include "Exception.h"

#include "Graph.h"
#include "Vertex.h"
#include "Arc.h"
using namespace NSGraph;
#define Arc NSGraph::Arc // To avoid collision with windows.h::Arc

#define BUFFER_SIZE 1024
#define CITY_SIZE 256
#define VERBOSE 1

#define CDF		8	// default color
#define CERR	12	// Error color
#define CHDR	10	// header color
#define CTY		2	// city color
#define CRD		4	// road color
#define CDIST	6	// miles color
#define CTM		3	// time color

/************************************************************************
* Purpose: Allow changing console text color within cout 
*
* Example: cout << col(10) << "hello world" << col(7);
*		Prints "hello world" with the foreground color "lime", then resets it to "white"
*
* Postcondition:
*		Modifies:	Console text color
*************************************************************************/
struct col
{
	col(WORD color)
		: m_color(color)
	{}

	friend ostream & operator<<(ostream & os, col & c)
	{
		SetConsoleTextAttribute(c.handle, c.m_color);
		return os;
	}

private:
	static HANDLE handle;
	WORD m_color;
};
HANDLE col::handle = GetStdHandle(STD_OUTPUT_HANDLE); // static HANDLE not initializable in class/struct


/************************************************************************
* Purpose: Contain all necessary data for Dijkstra's algorithm
*************************************************************************/
struct PathNode
{
	PathNode(const string & _name, const Vertex<string, string> * _vertex = nullptr, int _distance = -1)
		: name(_name), vertex(_vertex), distance(_distance), previous(-1), time(0.0f)
	{}

	string name;
	const Vertex<string, string> * vertex;
	int distance;
	int previous;
	float time;
};

struct Path
{
	Path() : miles(0), hours(0)	{}

	vector<PathNode> nodes;
	vector<PathNode> shortest;
	int miles;
	float hours;
};


// FUNCTION DEFINITIONS
void LoadFile(const string & filename, Graph<string, string> & graph);

void BuildMatrix(const Graph<string, string> & graph, Path & path, const string & from);
float GetSpeed(const string & road);

void FindPath(const Graph<string, string> & graph, Path & path, const string & from, const string & to);

int FindIndex(const Path & path, const string & data);
int FindLowestIndex(const Path & path);

void DisplayVerbosePath(const Path & path);
void DisplayConcisePath(const Path & path);


// PROGRAM START
int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	Graph<string, string> oregon;
	LoadFile("Oregon.txt", oregon);

	Path path;
	char start[CITY_SIZE] = { '\0' };
	char destination[CITY_SIZE] = { '\0' };
	bool done = false;
	int output_type = VERBOSE;

	// Display program header in CHDR color
	cout << col(CHDR) << "\tOregon Pathfinder\n\n" << "Enter city names or press enter to quit\n" << col(CDF) << endl;
	// Let the user choose verbose or concise output. (defaults to verbose)
	cout << "1) Verbose output\n2) Concise output\nInput: ";
	cin >> output_type;
	cin.clear();
	cin.ignore(cin.rdbuf()->in_avail()); // cleanup any errors and extra characters
	cout << endl;

	while (!done)
	{
		cout << "\n-----------------------------------------------------------" << endl;
		cout << "Enter start location: " << col(CTY);
		cin.getline(start, CITY_SIZE);
		done = !strlen(start);

		if (!done)
		{
			cout << col(CDF) << "Enter destination: " << col(CTY);
			cin.getline(destination, CITY_SIZE);
			done = !strlen(destination);
			
			cout << col(CDF) << endl;
			if (!done)
			{
				// reset path
				path = Path();
				try
				{
					FindPath(oregon, path, start, destination);
					if(output_type == VERBOSE)
						DisplayVerbosePath(path);
					else
						DisplayConcisePath(path);
				}
				catch (const Exception & exc)
				{
					cout << "\n" << col(CERR) << exc << col(CDF) << endl;
				}
			}
		}
	}

	cout << col(CHDR) << "\nGoodbye!\n" << col(CDF) << endl;

	return 0;
}


/************************************************************************
* Purpose: Open the given file, and load it's data into the given graph
*
* Precondition:
*
* Postcondition:
*		Modifies:	@graph
*		Throws:		N/A
*		Returns:	N/A
*************************************************************************/
void LoadFile(const string & filename, Graph<string, string> & graph)
{
	ifstream file(filename);

	if (file.is_open())
	{
		char line[BUFFER_SIZE] = { '\0' };
		file.getline(line, BUFFER_SIZE);
		while (!file.eof())
		{
			string from = strtok(line, ",");
			string to = strtok(nullptr, ",");
			string path = strtok(nullptr, ",");
			string miles = strtok(nullptr, "");

			if (!graph.Contains(from))
				graph.InsertVertex(from);
			if (!graph.Contains(to))
				graph.InsertVertex(to);

			graph.InsertArc(from, to, path, atoi(miles.c_str()));

			file.getline(line, BUFFER_SIZE);
		}
	}

}


/************************************************************************
* Purpose: Use Dijkstra's algorithm to build the given vectors starting at the vertex matching @from
*
* Precondition:
*	@vertices : Convert graph.Vertices() to a vector for the [] operator
*	@distance : Shortest distance between this vertex and matching @previous index 
*	@time	  : Time between this vertex and matching previous index
*	@previous : The next vertex closest to the starting position
*
* Postcondition:
*		Modifies:	@vertices, @distance, @time, @previous
*		Throws:		Exception("Error! '@from' does not exist...")
*					Exception("Error! Destination unreachable...")
*		Returns:	N/A
*************************************************************************/
void BuildMatrix(const Graph<string, string> & graph, Path & path, const string & from)
{
	// Convert the graph vertices list to PathNodes
	list<Vertex<string, string>>::const_iterator vertex;
	for (vertex = graph.Vertices().begin(); vertex != graph.Vertices().end(); ++vertex)
		path.nodes.push_back(PathNode(vertex->Data(), &(*vertex)));

	// Initialize the starting index and handle not found error
	int start = FindIndex(path, from);
	if (start == -1)
		throw Exception((string("Error! `") + from + "\' does not exist...").c_str());

	// Initialize the start distance and time
	path.nodes[start].distance = 0;
	path.nodes[start].time = 0;

	// Start at the beginning...
	int current = start;
	for (size_t i = 0; i < path.nodes.size() - 1; ++i)
	{
		// Loop through all the Arcs of the "current" vertex  
		list<Arc<string, string>>::const_iterator arc;
		for (arc = path.nodes[current].vertex->Arcs().begin(); arc != path.nodes[current].vertex->Arcs().end(); ++arc)
		{
			// If we haven't already processed the vertex, update its distance
			if (!arc->Destination()->Processed())
			{
				// dest is guaranteed to exist (barring thread data races)
				int dest = FindIndex(path, arc->Destination()->Data());
				int dist = (path.nodes[current].distance + arc->Weight());
				float time = (path.nodes[current].time + (float(arc->Weight()) / GetSpeed(arc->Data())));

				// If we haven't calculated a distance, or this route is shorter, or it takes less time...
				if (path.nodes[dest].distance == -1 || dist < path.nodes[dest].distance || time < path.nodes[dest].time)
				{
					path.nodes[dest].distance = dist;
					path.nodes[dest].previous = current;
					path.nodes[dest].time = time;
				}
			}
		}

		// Set the processed state to true for this vertex
		// And set "current" to the next lowest vertex
		path.nodes[current].vertex->Processed() = true; // Vertex::m_processed is mutable
		current = FindLowestIndex(path);
		if(current == -1)
			throw Exception("Error! Destination unreachable...");
	}

	// reset processed values...
	graph.ProcessVertices(false);
}

/************************************************************************
* Purpose: Return the speed limit for the given road
*
* Precondition:
*
* Postcondition:
*		Modifies:	N/A
*		Throws:		N/A
*		Returns:	Speed limit of @road
*************************************************************************/
float GetSpeed(const string & road)
{
	return ((road == "I-5") ? 65.0f : 55.0f);
}


/************************************************************************
* Purpose: Build the matrix, and use it to find the shortest path between @from and @to
*
* Precondition:
*	@path		: Filled with data in the order: city, data, ...
*	@path_dist	: Filled with the distances for the roads in @path
*	@miles		: Total distance between @from and @to
*	@hours		: Total travel time between @from and @to
*
* Postcondition:
*		Modifies:	@path, @path_dist, @miles, @hours
*		Throws:		Exception("Error! '@to' does not exist...")
*		Returns:	N/A
*************************************************************************/
void FindPath(const Graph<string, string> & graph, Path & path, const string & from, const string & to)
{
	// CALCULATE TIMES AND DISTANCES
	BuildMatrix(graph, path, from);
	
	// BUILD PATH
	// Get start and destination indexes
	int start = FindIndex(path, from);
	int destination = FindIndex(path, to);

	// Handle errors (start == -1 already dealt with in BuildMatrix()
	if (destination == -1)
		throw Exception((string("Error! `") + to + "\' does not exist...").c_str());

	path.miles = path.nodes[destination].distance;	// set miles to the total distance between from & to
	path.hours = path.nodes[destination].time;		// set hours to the total travel time between from & to

	// Push the cities and roads onto path.shortest
	while (destination != start)
	{
		// get the road between dest and prev
		int prev_ind = path.nodes[destination].previous;
		string prev = path.nodes[prev_ind].name;
		string dest = path.nodes[destination].name;
		const Arc<string, string> * road = graph.FindArc(dest, prev);
		
		// add the current destination
		path.shortest.push_back(path.nodes[destination]);

		// add road
		path.shortest.push_back(PathNode(road->Data(), nullptr, road->Weight()));

		// Set the destination to the next closest vertex to the start
		destination = prev_ind;
	}
	// Add the start point to the path
	path.shortest.push_back(PathNode(path.nodes[start].vertex->Data()));
}


/************************************************************************
* Purpose: Return the index of the vertex matching @data
*
* Precondition:
*
* Postcondition:
*		Modifies:	N/A
*		Throws:		N/A
*		Returns:	Found index, or -1 if not found
*************************************************************************/
int FindIndex(const Path & path, const string & data)
{
	int index = -1;

	for (size_t i = 0; index < 0 && i < path.nodes.size(); ++i)
	{
		if (path.nodes[i].name == data)
			index = i;
	}

	return index;
}


/************************************************************************
* Purpose: Return the index of the first unprocessed vertex with the least distance
*
* Precondition:
*
* Postcondition:
*		Modifies:	N/A
*		Throws:		N/A
*		Returns:	Found index, or -1 if not found
*************************************************************************/
int FindLowestIndex(const Path & path)
{
	int index = -1;
	int lowest = INT_MAX;
	float lowest_t = FLT_MAX;

	for (size_t i = 0; i < path.nodes.size(); ++i)
	{
		if (!path.nodes[i].vertex->Processed() && path.nodes[i].distance > -1 && (path.nodes[i].distance < lowest || path.nodes[i].time < lowest_t))
		{
			index = i;
			lowest = path.nodes[i].distance;
			lowest_t = path.nodes[i].time;
		}
	}

	return index;
}


/************************************************************************
* Purpose: Display the given path in a verbose manner
*
* Precondition:
*
* Postcondition:
*		Modifies:	N/A
*		Throws:		N/A
*		Returns:	N/A
*************************************************************************/
void DisplayVerbosePath(const Path & path)
{
	// Calculate hours and minutes
	int hours = int(path.hours); // truncate numbers after decimal point
	int minutes = int(path.hours * 60.0f) % 60;

	// Directions from city to city - # mile(s)
	cout << "Directions from " << col(CTY) << path.shortest.back().name << col(CDF) << " to " << col(CTY) << path.shortest.front().name
		<< col(CDIST) << " - " << path.miles << (path.miles == 1 ? " mile" : " miles") << col(CDF) << endl;
	// Travel time: # hour(s) # minute(s)
	cout << "Travel time: " << col(CTM) << hours << ((hours == 1) ? " hour " : " hours ")
		<< minutes << ((minutes == 1) ? " minute " : " minutes ") << col(CDF) << endl << endl;

	string indent = "    ";
	string from, road, to, next_road;
	int dist;
	bool same_road = false;

	// Path follows format: city, road
	for (int i = path.shortest.size() - 1; i >= 0; --i)
	{
		if (i > 3)
		{
			from = path.shortest[i].name;
			road = path.shortest[--i].name;
			dist = path.shortest[i].distance;
			to = path.shortest[--i].name;
			next_road = path.shortest[--i].name;
			same_road = (road == next_road);

			// From city take road to city - # mile(s)
			cout << indent << "From " << col(CTY) << from << col(CDF) << " take " << col(CRD) << road << col(CDF) << " to " << col(CTY) << to
				<< col(CDIST) << " - " << dist << (dist == 1 ? " mile" : " miles") << col(CDF) << endl;
			// Continue/Merge onto road - # mile(s)
			cout << indent << (same_road ? "Continue on " : "Merge onto ") << col(CRD) << next_road << col(CDIST) << " - "
				<< path.shortest[i].distance << " miles" << col(CDF);
		}
		else if(i > 1)
		{
			from = path.shortest[i].name;
			road = path.shortest[--i].name;
			dist = path.shortest[i].distance;
			to = path.shortest[--i].name;

			// From city take road to your destination city - # mile(s)
			cout << indent << "From " << col(CTY) << from << col(CDF) << " take " << col(CRD) << road
				<< col(CDF) << " to your destination " << col(CTY) << to
				<< col(CDIST) << " - " << dist << (dist == 1 ? " mile" : " miles") << col(CDF) << endl;
		}
		else if (i == 0)
		{
			cout << indent << "You will arrive at your destination " << col(CTY) << path.shortest[i].name << col(CDF);
		}

		cout << endl << endl;
	}

	cout << endl;
}


/************************************************************************
* Purpose: Display the given path in a concise manner
*
* Precondition:
*
* Postcondition:
*		Modifies:	N/A
*		Throws:		N/A
*		Returns:	N/A
*************************************************************************/
void DisplayConcisePath(const Path & path)
{
	// Calculate hours and minutes
	int hours = int(path.hours); // truncate numbers after decimal point
	int minutes = int(path.hours * 60.0f) % 60;

	// Directions from city to city - # mile(s)
	cout << "Directions from " << col(CTY) << path.shortest.back().name << col(CDF) << " to " << col(CTY) << path.shortest.front().name
		<< col(CDIST) << " - " << path.miles << (path.miles == 1 ? " mile" : " miles") << col(CDF) << endl;
	// Travel time: # hour(s) # minute(s)
	cout << "Travel time: " << col(CTM) << hours << ((hours == 1) ? " hour " : " hours ")
		<< minutes << ((minutes == 1) ? " minute " : " minutes ") << col(CDF) << endl << endl;

	// Path follows format: city, road
	for (int i = path.shortest.size() - 1; i >= 0; --i)
	{
		// display "city -> road - # miles" unless at destination
		cout << "    " << col(CTY) << path.shortest[i].name << col(CDF);
		if (i > 0)
			cout << " -> " << col(CRD) << path.shortest[--i].name << col(CDIST) << " - " << path.shortest[i].distance << " miles" << col(CDF);

		cout << endl << endl;
	}

	cout << endl;
}