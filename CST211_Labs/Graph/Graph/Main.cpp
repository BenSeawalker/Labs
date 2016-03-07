/*****************************************************************************************
Author:			Garrett Fleischer
Filename:		Main.cpp
Date Created:	2/27/16
Modifications:

Lab/Assignment: Lab 5

Overview: Test of Dijkstra's algorithm with Graph class

Input: Input is retrieved from the user and consists of a start and destination city

Output: The output for this program is to the console window and consists of error statements or the shortest path
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
HANDLE col::handle = GetStdHandle(STD_OUTPUT_HANDLE); // can't initialize it in struct...


// FUNCTION DEFINITIONS
void LoadFile(const string & filename, Graph<string, string> & graph);

void BuildMatrix(const Graph<string, string> & graph, vector<const Vertex<string, string> *> & vertices,
	vector<int> & distance, vector<float> & time, vector<int> & previous, const string & from);

void FindPath(const Graph<string, string> & graph, vector<string> & path, vector<int> & distance,
	int & miles, float & hours, const string & from, const string & to);

int FindIndex(const vector<const Vertex<string, string> *> & vertices, const string & data);
int FindLowestIndex(const vector<const Vertex<string, string> *> & vertices, const vector<int> & distance, const vector<float> & time);

void DisplayVerbosePath(const vector<string> & path, const vector<int> & path_dist, int miles, float hours);
void DisplayConcisePath(const vector<string> & path, const vector<int> & path_dist, int miles, float hours);


// PROGRAM START
int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	Graph<string, string> oregon;
	LoadFile("Oregon.txt", oregon);

	vector<string> path;
	vector<int> path_dist;
	int miles;
	float hours;
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
		cout << "Enter start location: " << col(2);
		cin.getline(start, CITY_SIZE);
		done = !strlen(start);

		if (!done)
		{
			cout << col(CDF) << "Enter destination: " << col(2);
			cin.getline(destination, CITY_SIZE);
			done = !strlen(destination);
			
			cout << endl;
			if (!done)
			{
				path.clear();
				path_dist.clear();
				try
				{
					FindPath(oregon, path, path_dist, miles, hours, start, destination);
					if(output_type == VERBOSE)
						DisplayVerbosePath(path, path_dist, miles, hours);
					else
						DisplayConcisePath(path, path_dist, miles, hours);
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
void BuildMatrix(const Graph<string, string> & graph, vector<const Vertex<string, string> *> & vertices, vector<int> & distance, vector<float> & time, vector<int> & previous, const string & from)
{
	// Initialize distance, time, and previous vectors with -1's
	distance.resize(graph.Vertices().size(), -1);
	time.resize(graph.Vertices().size(), -1);
	previous.resize(graph.Vertices().size(), -1);

	// Convert the graph vertices list to a vector so we can use the [] operator
	list<Vertex<string, string>>::const_iterator vertex;
	for (vertex = graph.Vertices().begin(); vertex != graph.Vertices().end(); ++vertex)
		vertices.push_back(&(*vertex));

	// Initialize the starting index and handle not found error
	int start = FindIndex(vertices, from);
	if (start == -1)
	{
		string error = "Error! `" + from + "\' does not exist...";
		throw Exception(error.c_str());
	}

	// Initialize the start distance and time
	distance[start] = 0;
	time[start] = 0;

	// Start at the beginning...
	int current = start;
	for (size_t i = 0; i < vertices.size() - 1; ++i)
	{
		// Loop through all the Arcs of the "current" vertex  
		list<Arc<string, string>>::const_iterator arc;
		for (arc = vertices[current]->Arcs().begin(); arc != vertices[current]->Arcs().end(); ++arc)
		{
			// If we haven't already processed the vertex, update its distance
			if (!arc->Destination()->Processed())
			{
				// dest is guaranteed to exist (barring thread data races)
				int dest = FindIndex(vertices, arc->Destination()->Data());
				int dist = (distance[current] + arc->Weight());
				float t = (float(arc->Weight()) / ((arc->Data() == "I-5") ? 65.0f : 55.0f));

				// If we haven't calculated a distance, or this route is shorter, or it takes less time...
				if (distance[dest] == -1 || dist < distance[dest] || t < time[dest])
				{
					distance[dest] = dist;
					previous[dest] = current;
					time[dest] = t;
				}
			}
		}

		// Set the processed state to true for this vertex
		// And set "current" to the next lowest vertex
		vertices[current]->Processed() = true;
		current = FindLowestIndex(vertices, distance, time);
		if(current == -1)
			throw Exception("Error! Destination unreachable...");
	}

	// reset processed values...
	graph.ProcessVertices(false);
	/*for (size_t i = 0; i < vertices.size(); ++i)
		vertices[i]->Processed() = false;*/
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
void FindPath(const Graph<string, string> & graph, vector<string> & path, vector<int> & path_dist, int & miles, float & hours, const string & from, const string & to)
{
	vector<const Vertex<string, string> *> vertices;
	vector<float> time;
	vector<int> distance;
	vector<int> previous;

	// CALCULATE TIMES AND DISTANCES
	BuildMatrix(graph, vertices, distance, time, previous, from);
	
	// BUILD PATH
	// Get start and destination indexes
	int start = FindIndex(vertices, from);
	int destination = FindIndex(vertices, to);

	// Handle errors (start == -1 already dealt with in BuildMatrix()
	if (destination == -1)
	{
		string error = "Error! `" + to + "\' does not exist...";
		throw Exception(error.c_str());
	}

	// Push the cities and roads onto path while pushing distances onto path_dist
	miles = distance[destination];
	hours = 0;
	while (destination != start)
	{
		// get the road between prev and dest
		string prev = vertices[previous[destination]]->Data();
		string dest = vertices[destination]->Data();
		const Arc<string, string> * road = graph.FindArc(prev, dest);
		
		// add the current destination
		path.push_back(dest);
		path_dist.push_back(0); // dummy data so index's align

		// add road
		path.push_back(road->Data());
		path_dist.push_back(road->Weight());

		// update time
		hours += time[destination];

		// Set the destination to the next closest vertex to the start
		destination = previous[destination];
	}
	// Add the start point to the path
	path.push_back(vertices[start]->Data());
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
int FindIndex(const vector<const Vertex<string, string>*> & vertices, const string & data)
{
	int index = -1;

	for (size_t i = 0; index < 0 && i < vertices.size(); ++i)
	{
		if (vertices[i]->Data() == data)
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
int FindLowestIndex(const vector<const Vertex<string, string> *> & vertices, const vector<int> & distance, const vector<float> & time)
{
	int index = -1;
	int lowest = INT_MAX;
	float lowest_t = FLT_MAX;

	for (size_t i = 0; i < distance.size(); ++i)
	{
		if (distance[i] > 0 && !vertices[i]->Processed() && (distance[i] < lowest || time[i] < lowest_t))
		{
			index = i;
			lowest = distance[i];
			lowest_t = time[i];
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
void DisplayVerbosePath(const vector<string> & path, const vector<int> & path_dist, int miles, float hours)
{


	// Calculate hours and minutes
	int minutes = int(hours * 60.0f) % 60;
	hours = floor(hours); // truncate numbers after decimal point

	// Display header with plural or singular nouns for hours and minutes
	// Directions from city to city - # mile(s)
	cout << "Directions from " << col(CTY) << path.back() << col(CDF) << " to " << col(CTY) << path.front()
		<< col(CDIST) << " - " << miles << (miles == 1 ? " mile" : " miles") << col(CDF) << endl;
	// Travel time: # hour(s) # minute(s)
	cout << "Travel time: " << col(CTM) << hours << ((hours == 1) ? " hour " : " hours ")
		<< minutes << ((minutes == 1) ? " minute " : " minutes ") << col(CDF) << endl << endl;

	string indent = "    ";
	string from, road, to, next_road;
	int dist;
	bool same_road = false;

	// Path follows format: city, road
	for (int i = path.size() - 1; i >= 0; --i)
	{
		if (i > 3)
		{
			from = path[i];
			road = path[--i];
			dist = path_dist[i];
			to = path[--i];
			next_road = path[--i];
			same_road = (road == next_road);

			// From city take road to city - # mile(s)
			cout << indent << "From " << col(CTY) << from << col(CDF) << " take " << col(CRD) << road << col(CDF) << " to " << col(CTY) << to
				<< col(CDIST) << " - " << dist << (dist == 1 ? " mile" : " miles") << col(CDF) << endl;
			// Continue/Merge onto road
			cout << indent << (same_road ? "Continue on " : "Merge onto ") << col(CRD) << next_road << col(CDIST) << " - " << path_dist[i] << " miles" << col(CDF);
		}
		else if(i > 1)
		{
			from = path[i];
			road = path[--i];
			dist = path_dist[i];
			to = path[--i];

			// From city take road to your destination city - # mile(s)
			cout << indent << "From " << col(CTY) << from << col(CDF) << " take " << col(CRD) << road
				<< col(CDF) << " to your destination " << col(CTY) << to
				<< col(CDIST) << " - " << dist << (dist == 1 ? " mile" : " miles") << col(CDF) << endl;
		}
		else if (i == 0)
		{
			cout << indent << "You will arrive at your destination " << col(CTY) << path[i] << col(CDF);
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
void DisplayConcisePath(const vector<string> & path, const vector<int> & path_dist, int miles, float hours)
{
	// Calculate hours and minutes
	int minutes = int(hours * 60.0f) % 60;
	hours = floor(hours); // truncate numbers after decimal point

	// Display header with plural or singular nouns for hours and minutes
	// Directions from city to city - # mile(s)
	cout << "Directions from " << col(CTY) << path.back() << col(CDF) << " to " << col(CTY) << path.front()
		<< col(CDIST) << " - " << miles << (miles == 1 ? " mile" : " miles") << col(CDF) << endl;
	// Travel time: # hour(s) # minute(s)
	cout << "Travel time: " << col(CTM) << hours << ((hours == 1) ? " hour " : " hours ")
		<< minutes << ((minutes == 1) ? " minute " : " minutes ") << col(CDF) << endl << endl;

	// Path follows format: city, road
	for (int i = path.size() - 1; i >= 0; --i)
	{
		// display "city -> road" unless at destination
		cout << "    " << col(CTY) << path[i] << col(CDF);
		if (i > 0)
			cout << " -> " << col(CRD) << path[--i] << col(CDIST) << " - " << path_dist[i] << " miles" << col(CDF);

		cout << endl << endl;
	}

	cout << endl;
}