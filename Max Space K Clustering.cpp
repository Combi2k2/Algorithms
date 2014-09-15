/*
Nodes are represented as bits and the hamming distance between any pair of nodes is the number of bits different in them
This program find how many clusters are needed to ensure that no pair of nodes with all but 2 bits in common get split into different clusters
It finds the largest value of k such that there is a k-clustering with spacing at least 3
ip format
[number_of_nodes]
[edge 1 node 1] [edge 1 node 2] [edge 1 cost]
[edge 2 node 1] [edge 2 node 2] [edge 2 cost]
*/
#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>

using namespace std;

struct edge{
	int node1;
	int node2;
	int cost;
};

struct rankedNodes{
	int nodeID;
	int rank;
	int parent;

};

vector<rankedNodes> nodes;
vector<edge> weightEdges;

//function headers
void readFile(vector<rankedNodes> &nodes, vector<edge> &weightEdges, string fileName);
void printEdges(vector<edge> &weightEdges);

bool compareEdges(edge A, edge B)
{
	return (A.cost < B.cost);
}

int Find(int currentNode)
{
	while (nodes[currentNode].parent != currentNode)
	{
		currentNode = nodes[currentNode].parent;
	}
	return currentNode;
}

void Union(int node1, int node2)
{
	int parent1 = Find(node1);
	int parent2 = Find(node2);
	if (nodes[parent1].rank == nodes[parent2].rank) //set node1 as parent
	{
		nodes[parent2].parent = parent1;
		nodes[parent1].rank++;
	}
	else if (nodes[parent1].rank > nodes[parent2].rank)
	{
		nodes[parent2].parent = parent1;
	}
	else
	{
		nodes[parent1].parent = parent2;
	}
}

void main(){
	//read edges
	readFile(nodes, weightEdges, "test.txt");
	//sort edges in increasing order of edges
	sort(weightEdges.begin(), weightEdges.end(), compareEdges);
	int uniqueClusters = nodes.size()-1; //initially every node is its own cluster
	int edgeIndex = 0;
	int node1, node2;
	while (uniqueClusters > 4)
	{
		node1 = weightEdges[edgeIndex].node1;
		node2 = weightEdges[edgeIndex].node2;
		if (Find(node1) != Find(node2))
		{
			Union(node1, node2);
			uniqueClusters--;
		}
		edgeIndex++;
	}
	//first of the remaining edges not inside a cluster is the maximum spacing
	node1 = weightEdges[edgeIndex].node1;
	node2 = weightEdges[edgeIndex].node2;
	while (Find(node1) == Find(node2) && edgeIndex < weightEdges.size())
	{
		edgeIndex++;
		node1 = weightEdges[edgeIndex].node1;
		node2 = weightEdges[edgeIndex].node2;
	}
	cout << "Maximum clustering: " << weightEdges[edgeIndex].cost << endl;
	//printEdges(weightEdges); //testing
	system("pause");
}

void printEdges(vector<edge> &weightEdges){
	for (int i = 0; i < weightEdges.size(); i++){
		cout << weightEdges[i].node1 << "\t" << weightEdges[i].node2 << "\t" << weightEdges[i].cost << endl;
	}
}

void readFile(vector<rankedNodes> &nodes, vector<edge> &weightEdges, string fileName)
{
	ifstream input(fileName);
	int size;
	input >> size;
	nodes.resize(size+1); //set node size
	//initialize nodes
	for (int i = 1; i <= size; i++){
		nodes[i].nodeID = i;
		nodes[i].rank = 1;
		nodes[i].parent = i;
	}
	int node1;
	int i = 0;
	edge currentEdge;
	while (input >> node1)
	{
		currentEdge.node1 = node1;
		input >> currentEdge.node2;
		input >> currentEdge.cost;
		weightEdges.push_back(currentEdge);
		i++;
	}
}