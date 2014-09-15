/*
This program implements the Dijkstra's shortest part algoirthm on an undirected weighted graph in C++ 
ip format
adjacency list representation
*/

#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<stdlib.h>
#include<algorithm>
#include<math.h>
#include<set>

using namespace std;
const int NUM_NODES = 200;
const int MAX_DIST = 1000000;


struct edge
{
	int tail;
	int head;
	int weight;
};

struct node
{
	int nodeID;
	vector<edge> adjList;
	int shortestDistance;
	node()
	{
		shortestDistance = MAX_DIST;
	}

};

void PrintGraph(vector<node> & graph, vector<edge> &edges);
void ReadInputFile(vector<node> & graph, vector<edge> &edges, string filename);
void CalculateShortestPaths(vector<node> & graph, vector<edge> & edges);

int main()
{
	vector<node> graph(NUM_NODES + 1);
	vector<edge> edges; //keep track of the edges in a separate vector
	ReadInputFile(graph, edges, "graph.txt");
	CalculateShortestPaths(graph, edges);
	PrintGraph(graph, edges);
	system("pause");
}

/**********************************************************************************************
Function: ReadInputFile
Description: Reads the given input file and stores the graphs as a vector of nodes,
each having an adjacency list of edges and their corresponding weights
Parameters: vector<node> & graph: The graph where the data is stored
filename: name of the file to input from
return : void
**********************************************************************************************/
void ReadInputFile(vector<node> & graph, vector<edge> &edges, string filename)
{
	ifstream input(filename);
	string currentLine;
	char charStream[500];
	char * charToken;
	int nodeCount = 1; //current node , initialzied to 1 as nodes are initialized to 1
	node currentNode;
	edge currentEdge;
	while (getline(input, currentLine))
	{
		int i;
		//Convert from string to char* for tokening purposes
		for (i = 0; i < currentLine.length(); i++)
		{
			charStream[i] = currentLine[i];
		}
		charStream[i] = '\0';
		charToken = strtok(charStream, "\t \0,\n");
		currentNode.nodeID = atoi(charToken);
		charToken = strtok(NULL, "\t, \0,\n"); // Get the first tail
		while (charToken != NULL)
		{
			currentEdge.tail = atoi(charToken);
			charToken = strtok(NULL, " \t,\0\n"); //an edge is always followed by the weight
			currentEdge.weight = atoi(charToken);
			currentNode.adjList.push_back(currentEdge);
			currentEdge.head = currentNode.nodeID;
			charToken = strtok(NULL, " ,\0\n\t");
			edges.push_back(currentEdge);
		}
		
		graph[currentNode.nodeID] = currentNode;
		currentNode.adjList.clear();
	}
}

/**********************************************************************************************
Function: PrintGraph
Description: Reads the given graph and prints the nodes, their edges and corresponding weights
Parameters: vector<node> & graph: The graph where the data is stored
return : void
**********************************************************************************************/
void PrintGraph(vector<node> & graph, vector<edge> & edges)
{
	node currentNode;
	cout << "Nodes\n";
	for (int i = 1; i < graph.size(); i++)
	{
		cout << "Node " << graph[i].nodeID << ", shortestDistance " << graph[i].shortestDistance << endl;
	}
}

/**********************************************************************************************
Function: CalculateShortestPaths
Description: Calculate the shortes paths form the root node i.e node 1 to all other nodes of a
weighted graph.
Parameters: vector<node> & graph: The graph where the data is stored
return : void
**********************************************************************************************/
void CalculateShortestPaths(vector<node> & graph, vector<edge> & edges)
{
	set<int> processedNodes; // keep track of nodes in set X
	graph[1].shortestDistance = 0; //root node
	processedNodes.insert(1);
	int edgeWeight;
	int currentMinNode;
	int currentShortestDistance = MAX_DIST;
	int tailNode,headNode;

	for (int i = 0; i <= NUM_NODES; i++) //every iteration adds one node to set X
	{

		currentShortestDistance = MAX_DIST;
		for (int j = 0; j < edges.size(); j++)
		{
			
			//check if head of the edge is in the set and tail isn't
			if ( (processedNodes.find(edges[j].head) != processedNodes.end()) && (processedNodes.find(edges[j].tail) == processedNodes.end()) )
			{
				edgeWeight = edges[j].weight;
				tailNode = edges[j].tail;
				headNode = edges[j].head;
				if (graph[tailNode].shortestDistance >(graph[headNode].shortestDistance + edgeWeight))
				{
					graph[tailNode].shortestDistance = graph[headNode].shortestDistance + edgeWeight;
				}
				if (graph[tailNode].shortestDistance < currentShortestDistance)
				{
					currentShortestDistance = graph[tailNode].shortestDistance;
					currentMinNode = tailNode;
				}
			}
		}
		processedNodes.insert(currentMinNode);
	//	PrintGraph(graph, edges);
	}

}