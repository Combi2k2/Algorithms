/*
This program find how many clusters are needed to ensure that no pair of nodes with all but 2 bits in common get split into different clusters
Nodes are represented as bits and the hamming distance between any pair of nodes is the number of bits different in them
It finds the largest value of k such that there is a k-clustering with spacing at least 3
ip format
[# of nodes] [# of bits for each node's label]
[first bit of node 1] ... [last bit of node 1]
[first bit of node 2] ... [last bit of node 2]
*/

#include <iostream>
#include <fstream>
#include<queue>
#include <cstdio>
#include <ctime>
#include <set>
#include<map>
#include<math.h>

using namespace std;

int size, boolLength;
int numClusters = 0;

set<unsigned long int> nodes;
map<int, string> binDecValues;

//function headers
void readFile();
void printNodes();
bool isHammingLessThan3(int index1, int index2);
int getHamming2Clusters();

void main(){
	std::clock_t start;
	double duration;
	start = std::clock();
	readFile();
	//printNodes(); //test
	cout << getHamming2Clusters() << endl;;
	duration = (std::clock() - start) / (double)CLOCKS_PER_SEC;
	std::cout << "printf: " << duration << '\n';
	system("pause");
}


unsigned long int BinToDec(string number)
{
	unsigned long int result = 0, pow = 1;
	for (int i = number.length() - 1; i >= 0; --i, pow <<= 1)
		result += (number[i] - '0') * pow;

	return result;
}

void printNodes()
{
	for (set<unsigned long int>::iterator it = nodes.begin(); it != nodes.end(); ++it)
	{
		cout << *it << endl;
	}
}

void readFile()
{
	ifstream inputFile("test.txt");
	inputFile >> size;
	inputFile >> boolLength;
	char a;
	string number;
	for (int i = 0; i < size; i++)
	{
		string number = "";
		for (int j = 0; j < boolLength; j++)
		{
			inputFile >> a;
			number += a;
		}
		unsigned long int decimal = BinToDec(number);
		nodes.insert(decimal);
		binDecValues.insert({ decimal, number });
	}
}

string getBinary(int number)
{
	map<int, string>::iterator it = binDecValues.find(number);
	return (it->second);
}

int getHamming2Clusters()
{
	queue<int> nodeQueue;
	unsigned long int currentNumber = 0;
	set<unsigned long int>::iterator it = nodes.begin();
	set<unsigned long int> nodesCopy(nodes);//for deletion and iterator stability
	while (it != nodes.end())
	{
		nodeQueue.push(*it);
		currentNumber = nodeQueue.front();
		if (nodesCopy.find(currentNumber) != nodesCopy.end())
		{
			numClusters++;
			nodesCopy.erase(currentNumber);

			while (!nodeQueue.empty())
			{
				currentNumber = nodeQueue.front();
				nodeQueue.pop();
				//find hamming neighbours
				long int factor1, factor2;
				string booleanNumber = getBinary(currentNumber);
				for (int i = boolLength - 1; i >= 0; i--)
				{
					if (booleanNumber[i] == '0')
					{
						factor1 = currentNumber + pow(2, (boolLength - 1 - i));
					}
					else
					{
						factor1 = currentNumber - pow(2, (boolLength - 1 - i));
					}
					if (factor1 >= 0 && nodesCopy.find(factor1) != nodesCopy.end())
					{
						nodeQueue.push(factor1);
						nodesCopy.erase(factor1);
					}
					for (int j = i - 1; j >= 0; j--)
					{
						if (booleanNumber[j] == '0')
						{
							factor2 = factor1 + pow(2, (boolLength - 1 - j));
						}
						else
						{
							factor2 = factor1 - pow(2, (boolLength - 1 - j));
						}
						if (factor2 >= 0 && nodesCopy.find(factor2) != nodesCopy.end())
						{
							nodeQueue.push(factor2);
							nodesCopy.erase(factor2);
						}
					}
				}
			}
		}
		else
		{
			nodeQueue.pop();
		}
		++it;

	}
	return numClusters;
}