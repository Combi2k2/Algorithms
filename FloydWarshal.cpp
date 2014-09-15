/*
This program implements a solution to the all pair shortest path problem
in C++ using the floyd warshal algorithm
ip format
[num vertices] [num edges]
[head] [tail] [length]
..
*/
#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include<algorithm>

const int MAX_DIST = 999999;
using namespace std;
int numVertices;

struct edge
{
	int tail;
	int head;
	int cost;
};

//function headers
void readGraph(vector<edge> &graph);
void printGraph(vector<edge> & graph);
void allPairShortestPath(vector<edge> &graph);


void main()
{
	vector<edge> graph;
	//readgraph
	readGraph(graph);
	//printGraph(graph); //test
	allPairShortestPath(graph);
	system("pause");
}

void printGraph(vector<edge> & graph)
{
	for (int i = 0; i < graph.size(); i++)
	{
		cout << graph[i].head << '\t' << graph[i].tail << '\t' << graph[i].cost << endl;
	}
}

void readGraph(vector<edge> &graph)
{
	edge newEdge;
	ifstream input("test.txt");
	int numEdges;
	input >> numVertices;
	input >> numEdges;
	for (int i = 0; i < numEdges; i++)
	{
		input >> newEdge.tail;
		input >> newEdge.head;
		input >> newEdge.cost;
		graph.push_back(newEdge);
	}
}

void allPairShortestPath(vector<edge> &graph)
{
	vector<vector<int>> currentArray; //k
	vector<vector<int>> previousArray;// k-1
	currentArray.resize(numVertices + 1);
	for (int i = 1; i <= numVertices; i++)
	{
		currentArray[i].resize(numVertices + 1);
		for (int j = 1; j <= numVertices; j++)
		{
			if (i == j)
			{
				currentArray[i][j] = 0;
			}
			else
			{
				currentArray[i][j] = MAX_DIST;
			}
			
		}
	}
	//assign edge weights
	for (int i = 0; i <graph.size();i++)
	{
		currentArray[graph[i].tail][graph[i].head] = graph[i].cost;
	}

	//copy to previous
	previousArray = currentArray;
	for (int k = 1; k <= numVertices; k++)
	{
		for (int i = 1; i <= numVertices; i++)
		{
			for (int j = 1; j <= numVertices; j++)
			{
				currentArray[i][j] = min(previousArray[i][j], previousArray[i][k] + previousArray[k][j]);
			}
			if (currentArray[i][i] < 0)
			{
				cout << "Negative weight\n";
				return;
			}
		}
		
		previousArray = currentArray;
	}

	int minVal = 99999;
	//print final array
	for (int i = 1; i <= numVertices; i++)
	{
		for (int j = 1; j <= numVertices; j++)
		{
			cout<<currentArray[i][j] << '\t';
			minVal = min(minVal, currentArray[i][j]);
		}
		cout << endl;
	}
	cout << "minimum: " << minVal << endl;
}