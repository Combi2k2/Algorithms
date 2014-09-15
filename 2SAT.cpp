/* 
This programs finds the satisfiablity of a 2 SAT instantance by representing the variables as nodes and conjunction as edges
and computing the strongly connected components by performing a reverse DFS for ordering and a forward DFS for the SCCs*/

#define _CRT_SECURE_NO_WARNINGS

#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<set>
#include<stdlib.h>
#include<time.h>
#include<algorithm>

using namespace std;

struct node
{
	vector<int> neighbour;
};


vector<node> graph;
vector<node> reverseGraph;
vector<int> ordering;
vector<bool> visited;
vector<int> TofNode;
set<int> currentSCCNodes;

int numNodes;
int currentTime = 1;

//function declarations
void printNodes(vector<node>& graph);
void readInput();
int modified(int nodeNumber);
void findOrdering();
void performDFS(int nodeNumber);
bool performDFS2(int nodeNumber);
bool findSCCs();
bool hasInverse(int nodeNumber);

void main()
{
	readInput();
	//printNodes(graph);//test
	//cout << "reverse\n";
	//printNodes(reverseGraph);
	findOrdering();
	if (findSCCs())
	{
		cout << "Is sat\n";
	}
	else
	{
		cout << "Not SAT\n";
	}
	system("pause");
}

void printNodes(vector<node>& graph)
{
	for (int i = 1; i <= 2 * numNodes; i++)
	{
		cout << i << '\t';
		for (int j = 0; j < graph[i].neighbour.size(); j++)
		{
			cout << graph[i].neighbour[j] << '\t';
		}
		cout << endl;
	}
}
void readInput()
{
	ifstream input("test.txt");
	input >> numNodes;
	graph.resize(2 * numNodes + 1);
	reverseGraph.resize(2 * numNodes + 1);
	ordering.resize(2 * numNodes + 1);
	TofNode.resize(2 * numNodes + 1);
	visited.resize(2 * numNodes + 1);
	int currentNode1, currentNode2;
	for (int i = 0; i < numNodes; i++)
	{
		input >> currentNode1;
		input >> currentNode2;
		//node 1 is negated
		graph[modified(-currentNode1)].neighbour.push_back(modified(currentNode2));
		graph[modified(-currentNode2)].neighbour.push_back(modified(currentNode1));
		reverseGraph[modified(currentNode2)].neighbour.push_back(modified(-currentNode1));
		reverseGraph[modified(currentNode1)].neighbour.push_back(modified(-currentNode2));
	}
}

//return numNodes + index for negative node values
int modified(int nodeNumber)
{
	if (nodeNumber >= 0)
	{
		return nodeNumber;
	}
	else
	{
		return numNodes + abs(nodeNumber);
	}
}

//dfs on the reversed graph
void findOrdering()
{
	for (int i = 2 * numNodes; i > 0; i--)
	{
		if (visited[i] == false)
		{
			visited[i] = true;
			performDFS(i);
		}
	}
}

void performDFS(int nodeNumber)
{
	int currentNode;
	for (int i = 0; i < reverseGraph[nodeNumber].neighbour.size(); i++)
	{
		currentNode = reverseGraph[nodeNumber].neighbour[i];
		if (visited[currentNode] == false)
		{
			visited[currentNode] = true;
			performDFS(currentNode);
		}
	}
	TofNode[currentTime++] = nodeNumber;
}

bool findSCCs()
{
	//reset visited
	for (int i = 0; i < visited.size(); i++)
	{
		visited[i] = false;
	}

	int currentNode;
	for (int i = 2 * numNodes; i>0; i--)
	{
		currentSCCNodes.clear();
		currentNode = TofNode[i];
		if (visited[currentNode] == false)
		{
			currentSCCNodes.insert(currentNode);
			visited[currentNode] = true;
			if (!performDFS2(currentNode))
			{
				return false;
			}
		}
	}
	return true;

}

bool performDFS2(int nodeNumber)
{
	int currentNode;
	for (int i = 0; i < graph[nodeNumber].neighbour.size(); i++)
	{
		currentNode = graph[nodeNumber].neighbour[i];
		if (visited[currentNode] == false)
		{
			if (hasInverse(currentNode))
			{
				return false;
			}
			visited[currentNode] = true;
			if (!performDFS2(currentNode))
			{
				return false;
			}
		}
	}
	return true;
}

bool hasInverse(int nodeNumber)
{
	if (nodeNumber <= numNodes)
	{
		if (currentSCCNodes.find(numNodes + nodeNumber) != currentSCCNodes.end())
		{
			return true;
		}
	}
	else
	{
		if (currentSCCNodes.find(nodeNumber - numNodes) != currentSCCNodes.end())
		{
			return true;
		}
	}
	return false;
}