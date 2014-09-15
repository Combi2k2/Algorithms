/*
This program implements the Karger's Minimum Cut Algorithm in C++
It uses a randomized contraction algorithm graph_nodes^2 times and outputs the minimum value
ip format is adjacency list
[adjacent_node1] [adjacent_node2] ...
.
.
.
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

int FindMinCut(vector<vector<int>>& graph);
vector<int> MergeNodes(vector<int> node1, vector<int> node2, int node1Index, int node2Index);
void UpdateGraph(vector<vector<int>>& graph, int node1Index, int node2Index);

/***************************************************************************************************************************
Function: PrintGraph
Description: This function prints the graph, used mainly for de-bugging
Parameters:vector<vector<int>>& graph, a reference to the 2-D graph, 1st index represents the node, the second represents the edges in each node
Return type: void
****************************************************************************************************************************/
void PrintGraph(vector<vector<int>>& graph)
{
	for (int i = 0; i < graph.size(); i++)
	{
		cout << "Node:" << i + 1 << " size: " << graph[i].size() << " => ";
		for (int j = 0; j < graph[i].size(); j++)
		{
			cout << graph[i][j] << "\t";
		}
		cout << endl;
	}
}

void main(){
	vector<vector<int>> graph(200);
	ifstream input("IntegerArray.txt");
	string line;
	int currentNodeNum = 0;
	char * str;
	char * temp;
	str = new char[5000];
	int tempNum;
	if (input.is_open()){
		while (input.good()){
			getline(input, line);
			//convert string to char * to pass as a parameter to strtok
			int i;
			for (i = 0; i < line.length(); i++)
			{
				str[i] = line[i];
			}
			str[i] = '\0';
			//Tokenize node number
			temp = strtok(str, "\t\0");
			//create a new node with incremental index
			currentNodeNum = atoi(temp);
			//Tokenize adjacency list
			while (temp != NULL)
			{
				temp = strtok(NULL, "\t\0");
				if (temp == NULL) break;
				tempNum = atoi(temp);
				if (tempNum != 0)
				{
					graph[currentNodeNum - 1].push_back(tempNum);
				}


			}

		}


	}
	//PrintGraph(graph);
	int minCutVal = 10000;
	//run the min-cut n^2 times
	int iterations = (graph.size() * graph.size());
	for (int i = 0; i < iterations; i++)
	{
		srand(time(NULL));
		minCutVal = min(FindMinCut(graph), minCutVal);
	}
	cout << minCutVal << endl;
	//PrintGraph(graph);
	system("pause");
}

/***************************************************************************************************************************
Function: FindMinCut
Description: This function finds the MinCut of the graph by choosing nodes at random and merging them into single nodes
Parameters:vector<vector<int>>& graph, a reference to the 2-D graph, 1st index represents the node, the second represents the edges in each node
Return type: int The number of edges crossing the min-cut in the current iteration is returned
****************************************************************************************************************************/
int FindMinCut(vector<vector<int>>& graph)
{

	int randInt1 = 0, randInt2 = 0, randadjcent = 0;
	vector<int> node1;
	vector<int> node2;
	vector<int> mergedNode;
	int pass = 1;
	int maxNode, minNode;
	while (graph.size() > 2)
	{
		//random int from 0 to size of graph-1
		randInt1 = rand() % graph.size();
		node1 = graph[randInt1];

		//Find randon adjacent node 0 to size of graph[randInt1]-1
		randadjcent = rand() % (graph[randInt1].size());
		//1 is subtracted because x on the adjacent list is x -1 in the array
		randInt2 = graph[randInt1][randadjcent] - 1;
		node2 = graph[randInt2];
		maxNode = max(randInt1, randInt2);
		minNode = min(randInt1, randInt2);
		graph.erase(graph.begin() + maxNode);
		graph.erase(graph.begin() + minNode);
		//merge and add to the graph
		mergedNode = MergeNodes(node1, node2, randInt1, randInt2);
		graph.push_back(mergedNode);
		//rename the adjacency list elements
		graph = UpdateGraph(graph, randInt1, randInt2);

	}

	return graph[0].size();
}

/***************************************************************************************************************************
Function: MergeNodes
Description: This function merges the two nodes into a single node with the edges of the two combining nodes, except for
the edges that cause self loops
Parameters: vector<int> node1 , vector<int> node2 : The two nodes to be merged
node1Index, node2Index : The node index's are passed to check and remove self-loops
Return type: vector<int> The merged node is returned
****************************************************************************************************************************/
vector<int> MergeNodes(vector<int> node1, vector<int> node2, int node1Index, int node2Index)
{
	//remove self loops
	for (int i = 0; i < node1.size(); i++)
	{
		if (node1[i] == node2Index + 1)
		{
			node1.erase(node1.begin() + i);
			//update the counter
			i--;
		}
	}

	for (int i = 0; i < node2.size(); i++)
	{
		if (node2[i] == node1Index + 1)
		{
			node2.erase(node2.begin() + i);
			//update the counter
			i--;
		}
	}

	vector<int> mergedNode(node1.size() + node2.size() + 1);
	mergedNode.clear();
	//add adjacent list values
	for (int i = 0; i < node1.size(); i++)
	{
		mergedNode.push_back(node1[i]);
	}
	for (int i = 0; i < node2.size(); i++){
		mergedNode.push_back(node2[i]);
	}

	return mergedNode;
}

/***************************************************************************************************************************
Function: UpdateGraph
Description: This function updates the value of each node after the merge has been done,
the newly created merged node is added to the end, other nodes are decremented by 1 if their value is between to two merged
nodes, or decremented by 2 if their values is greater than both the merged nodes
Parameters: vector<vector<int>>& graph, a reference to the graph int node1Index, int node2Index
Return type: void
****************************************************************************************************************************/
void UpdateGraph(vector<vector<int>>& graph, int node1Index, int node2Index)
{

	for (int i = 0; i < graph.size(); i++)
	{

		for (int j = 0; j < graph[i].size(); j++)
		{
			//node is the one of the merged nodes
			if (graph[i][j] == node1Index + 1 || graph[i][j] == node2Index + 1)
			{
				graph[i][j] = graph.size();
			}
			//node is between the chosen two, decrement by 1
			else if ((graph[i][j] > node1Index + 1 && graph[i][j] < node2Index + 1) || (graph[i][j] > node2Index + 1 && graph[i][j] < node1Index + 1))
			{
				graph[i][j] --;
			}
			//node is after chosen two, decrement by 2
			else if (graph[i][j] > node1Index + 1 && graph[i][j] > node2Index + 1)
			{
				graph[i][j] = graph[i][j] - 2;
			}
		}
	}

}