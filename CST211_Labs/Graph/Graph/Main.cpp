/*****************************************************************************************
Author:			Garrett Fleischer
Filename:		Main.cpp
Date Created:	2/27/16
Modifications:

Lab/Assignment: A11

Overview: Test of Graph class

Input: Input is hardcoded directly into Main.cpp and consists of debug testing statements

Output: The output for this program is to the console window and consists of debugging
text and data stored in the Graph. The output will have the following form:

-------------------------- Test <function> --------------------------

Inserting: *, ...
Deleting: *, ...

<test type>: <test result>

*****************************************************************************************/

#include "crtdbg_new.h"

#include <climits>
#include <string>
using std::string;
#include <fstream>
using std::ifstream;
#include <iostream>
using std::cin;
using std::cout;
using std::endl;
#include <list>
using std::list;
#include <vector>
using std::vector;

#include "Graph.h"
#include "Vertex.h"
#include "GraphVertexIterator.h"

#define BUFFER_SIZE 1024

void LoadFile(const string & filename, Graph<string, string> & graph);
void BuildMatrix(const Graph<string, string> & graph, vector<const Vertex<string, string> *> & vertices, vector<int> & distance, vector<float> & time, vector<int> & previous, const string & from);
void FindPath(const Graph<string, string> & graph, vector<string> & path, int & miles, float & hours, const string & from, const string & to);
int FindIndex(const vector<const Vertex<string, string> *> & vertices, const string & data);
int FindLowestIndex(const vector<const Vertex<string, string> *> & vertices, const vector<int> & distance);

void DisplayPath(const vector<string> & path, int miles, float hours);


int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	Graph<string, string> oregon;

	LoadFile("Oregon.txt", oregon);

	vector<string> path;
	int miles;
	float hours;

	FindPath(oregon, path, miles, hours, "Klamath Falls", "Reedsport");
	DisplayPath(path, miles, hours);
	path.clear();

	FindPath(oregon, path, miles, hours, "Bend", "Ashland");
	DisplayPath(path, miles, hours);
	path.clear();

	return 0;
}


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

void BuildMatrix(const Graph<string, string> & graph, vector<const Vertex<string, string> *> & vertices, vector<int> & distance, vector<float> & time, vector<int> & previous, const string & from)
{
	distance.resize(graph.Vertices().size(), -1);
	time.resize(graph.Vertices().size(), -1);
	previous.resize(graph.Vertices().size(), -1);

	list<Vertex<string, string>>::const_iterator vertex;
	for (vertex = graph.Vertices().begin(); vertex != graph.Vertices().end(); ++vertex)
		vertices.push_back(&(*vertex));

	int start = FindIndex(vertices, from);
	distance[start] = 0;
	time[start] = 0;

	int current = start;
	for (int i = 0; i < vertices.size() - 1; ++i)
	{
		list<Arc<string, string>>::const_iterator arc;
		for (arc = vertices[current]->Arcs().begin(); arc != vertices[current]->Arcs().end(); ++arc)
		{
			if (!arc->Destination()->Processed())
			{
				int dest = FindIndex(vertices, arc->Destination()->Data());
				int dist = (distance[current] + arc->Weight());

				if (distance[dest] < 0 || dist < distance[dest])
				{
					distance[dest] = dist;
					previous[dest] = current;
					time[dest] = (float(arc->Weight()) / ((arc->Data() == "I-5") ? 65.0f : 55.0f));
				}
			}
		}

		const_cast<Vertex<string, string> *>(vertices[current])->Processed() = true;
		current = FindLowestIndex(vertices, distance);
	}

	// reset processed values...
	for (int i = 0; i < vertices.size(); ++i)
		const_cast<Vertex<string, string> *>(vertices[i])->Processed() = false;
}

void FindPath(const Graph<string, string> & graph, vector<string> & path, int & miles, float & hours, const string & from, const string & to)
{
	vector<const Vertex<string, string> *> vertices;
	vector<int> distance;
	vector<float> time;
	vector<int> previous;

	// Calculate times and distances
	BuildMatrix(graph, vertices, distance, time, previous, from);
	
	// Build path
	int start = FindIndex(vertices, from);
	int destination = FindIndex(vertices, to);

	miles = distance[destination];
	hours = 0;
	while (destination != start)
	{
		string prev = vertices[previous[destination]]->Data();
		string dest = vertices[destination]->Data();
		const Arc<string, string> * road = graph.FindArc(prev, dest);

		hours += time[destination];
		path.push_back(dest);
		path.push_back(road->Data());
		destination = previous[destination];
	}
	path.push_back(vertices[start]->Data());
}

int FindIndex(const vector<const Vertex<string, string>*>& vertices, const string & data)
{
	int index = -1;

	for (int i = 0; index < 0 && i < vertices.size(); ++i)
	{
		if (vertices[i]->Data() == data)
			index = i;
	}

	return index;
}

int FindLowestIndex(const vector<const Vertex<string, string> *> & vertices, const vector<int>& distance)
{
	int index = -1;
	int lowest = INT_MAX;

	for (int i = 0; i < distance.size(); ++i)
	{
		if (distance[i] > 0 && !vertices[i]->Processed() && distance[i] < lowest)
		{
			index = i;
			lowest = distance[i];
		}
	}

	return index;
}

void DisplayPath(const vector<string>& path, int miles, float hours)
{
	int minutes = int(hours * 60.0f) % 60;

	cout << "Directions from " << path.back() << " to " << path.front() << " " << miles << " miles " << endl;
	cout << "Travel time: " << int(hours) << ((int(hours) == 1) ? " hour " : " hours ")
		<< minutes << ((minutes == 1) ? " minute " : " minutes ") << endl << endl;

	for (int i = path.size() - 1; i >= 0; --i)
	{
		cout << "    " << path[i];
		if (i > 0)
			cout << " -> " << path[--i];

		cout << endl << endl;
	}

	cout << endl;
}