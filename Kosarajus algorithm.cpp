/* 
This programs finds the size of the strongly connected components of a directed graph in C++
The input is read from a text file and stored in a 2D vector and PerformDFS is computed using the Kosaraju two pass linear algorithm
The size of the vector is hard coded for convenience
To arrays are used to track f(i) and explored/unexplored values
*/

#define _CRT_SECURE_NO_WARNINGS

#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<stdlib.h>
#include<time.h>
#include<algorithm>

using namespace std;

const int NUMOFNODES = 875714;

void printGraph(vector<vector<int>>& graph);
void ReadInputFile(string filename, vector<vector<int>> & graph, vector<vector<int>> & graphRev);
void FindTimes(vector<vector<int>>& graph);
void PerformDFS(int node, vector<vector<int>>& graph);
void PerformDFS2(int node, vector<vector<int>>& graph);
void FindSCCs(vector<vector<int>>& graph);

//Global variables
vector<int> SCCsize(NUMOFNODES); //max num of SCCs is number of nodes
int currentTime; // Time the node search ends
int parentNode;
int numberofSCCs;
int currentSCCNum = 0;

vector<bool> visited(NUMOFNODES + 1);
vector<int> TofNode(NUMOFNODES + 1); // Nodes sorted in increasing  time value

void main(){
	currentTime = 1;
	parentNode = -1;
	vector<vector<int>> graph(NUMOFNODES + 1); // index 0 is empty
	vector<vector<int>> graphRev(NUMOFNODES + 1);
	ReadInputFile("SCC.txt", graph,graphRev); //Read reversed graph
	FindTimes(graphRev);
	FindSCCs(graph);
	//printGraph(graph);
	sort(begin(SCCsize), end(SCCsize));
	int j = 5;
	for (int i = (SCCsize.size() - 1); j > 0; j--)
	{
		cout << SCCsize[i] << '\t';
		i--;
	}
	cout << endl;
	std::system("pause");
}

/***************************************************************************************************************************
Function: ReadInputFile
Description: This function reads the input file and stores the values into a two dimentional vector consisting of nodes and
their adjacent lists, returns the reversed or straight graph depending on the graphOrder
Parameters: string filename : name of the textfile to read
int graphOrder : 0 is straight graph.
1 is the reversed graph
Return type: vector<vector<int>> two dimensional vector representing the graph, reversed or straight depending on graphOrder
****************************************************************************************************************************/
void ReadInputFile(string filename, vector<vector<int>> & graph, vector<vector<int>> & graphRev)
{
	ifstream input(filename);
	int currentNodeNum = 0;
	int currentEdge = 0;
		while (input >> currentNodeNum) {
			input >> currentEdge;
			graph[currentNodeNum].push_back(currentEdge);
			graphRev[currentEdge].push_back(currentNodeNum);
		}

}

/***************************************************************************************************************************
Function: printGraph
Description: This function reads the 2D vector and prints each node and its corresponding adjacent list.
The 0 index is empty for convenience
Parameters: vector<vector<int>> two dimensional vector representing the graph
Return type: void
****************************************************************************************************************************/
void printGraph(vector<vector<int>>& graph)
{
	for (int i = 1; i < graph.size(); i++)
	{
		cout << endl << "Node" << i << ":\t";
		for (int j = 0; j < graph[i].size(); j++)
		{
			cout << graph[i][j] << ' ';
		}
	}
}



/***************************************************************************************************************************
Function: FindTimes
Description: This function reads the 2D vector and finds the time of finish for each node through the depth first search
The 0 index is empty for convenience
Parameters: vector<vector<int>> two dimensional vector representing the graph
Return type: void
****************************************************************************************************************************/
void FindTimes(vector<vector<int>>& graph)
{
	for (int i = NUMOFNODES; i > 0; i--)
	{
		if (visited[i] == false)
		{
			visited[i] = true;
			PerformDFS(i, graph);
		}
	}
}


/***************************************************************************************************************************
Function: PerformDFS
Description: T
Parameters: vector<vector<int>> two dimensional vector representing the graph
int node : node to perform PerformDFS on
Return type: null
****************************************************************************************************************************/
void PerformDFS(int node, vector<vector<int>>& graph)
{
	int currentNode;
	for (int i = 0; i < graph[node].size(); i++)
	{
		currentNode = graph[node][i];
		if (visited[currentNode] == false)
		{
			visited[currentNode] = true;
			PerformDFS(currentNode, graph);
		}
	}
	TofNode[currentTime++] = node;
}

/***************************************************************************************************************************
Function: FindSCCs
Description:
Parameters: vector<vector<int>> two dimensional vector representing the graph
int node : node to perform PerformDFS on
Return type: null
****************************************************************************************************************************/
void FindSCCs(vector<vector<int>>& graph)
{

	//Reset visited
	for (int i = 0; i<NUMOFNODES; i++)
	{
		visited[i + 1] = false;
		SCCsize[i] = 0;
	}

	int currentNode;
	currentSCCNum = 0;
	for (int i = NUMOFNODES; i > 0; i--)
	{
		currentNode = TofNode[i];
		if (visited[currentNode] == false)
		{
			visited[currentNode] = true;
			PerformDFS2(currentNode, graph);
			currentSCCNum++;
		}

	}
}

/***************************************************************************************************************************
Function: PerformDFS2
Description: A second DFS , almost identical to DFS is used to keep the TofNode values and the SCCsize values separated
Parameters: vector<vector<int>> two dimensional vector representing the graph
int node : node to perform PerformDFS on
Return type: null
****************************************************************************************************************************/
void PerformDFS2(int node, vector<vector<int>>& graph)
{
	int currentNode;
	int i;
	for (i = 0; i < graph[node].size(); i++)
	{
		currentNode = graph[node][i];
		if (visited[currentNode] == false)
		{
			visited[currentNode] = true;
			PerformDFS2(currentNode, graph);
		}
	}
	if (i>0)
	{
		SCCsize[currentSCCNum] ++;
	}

}