/* 
This program implements the 2-sum algorithm using the build-in set library for lookup in C++ 
Reads the given array and checks how many pairs of distinct numbers exist whose sum is between [-10000,10000] (inclusive)
input is an array of number, one number per line
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
#include<stdlib.h>

using namespace std;

void readInputFile(string filename, set<long long int> & lookUpTable);
void printArray(long int inputArray[]);
long long int checkTwoSum(set<long long int> & lookUpTable);
long long int binSearchLeast(vector<long long> & array, long long int start, long long int end, long long int number);
long long int FindIndex(vector<long long> & array, long long int currentNumber, long long int currentIndex);

long int main()
{
	set<long long int> lookUpTable; //store the array in lookup table for O(1) lookups while finding the 2-sum
	readInputFile("num.txt", lookUpTable);
	cout << "Two sum between [-10000,10000] (inclusive) is: " << checkTwoSum(lookUpTable) << endl;
	//prlong intArray(inputArray);
	system("pause");
}

/**********************************************************************************************
Function: ReadInputFile
Description: Reads the given input file and stores numbers in an array
Parameters:
set<long long int> & lookUpTable The hash table used for O(1) lookups
filename: name of the file to input from
return : void
**********************************************************************************************/
void readInputFile(string filename, set<long long int> & lookUpTable)
{

	ifstream inputFile("num.txt");
	string line;
	long long int num;
	while (getline(inputFile, line))
	{
		num = strtoull(line.c_str(), (char **)NULL, 10);
		lookUpTable.insert(num);
	}

}

/**********************************************************************************************
Function: prlong intArray
Description: Reads the given array and prlong ints is
Parameters: long int inputArray[]
return : void
**********************************************************************************************/
void printArray(set<long long int> & lookUpTable)
{
	set<long long int>::iterator it;
	for (it = lookUpTable.begin(); it != lookUpTable.end(); ++it)
	{
		{
			cout << *it << endl;
		}
	}
}
/**********************************************************************************************
Function: checkTwoSum
Description: Reads the given array and checks how many pairs of distinct numbers exist whose sum is
between [-10000,10000] (inclusive)
set<long long int> & lookUpTable The hash table used for O(1) lookups
return : long int The number of pairs of distinct sums in the required range
**********************************************************************************************/
long long int checkTwoSum(set<long long int> & lookUpTable)
{
	long long int count = 0;
	set<long long>::iterator it;
	long long int startIndex, endIndex, currentNum;
	vector<long long> array;
	set<long long> distinct;
	//store into an array for constant time referencing
	for (it = lookUpTable.begin(); it != lookUpTable.end(); ++it)
	{
		array.push_back(*it);
	}
	for (long long int i = 0; i < array.size(); i++)
	{
		currentNum = array[i];
		startIndex = FindIndex(array, currentNum, i);
		if (startIndex != -1)
		{
			long long int debugNum = array[startIndex++];
			while ((debugNum + currentNum) <= 10000 && distinct.find(debugNum+currentNum) == distinct.end())
			{
				count++;
				distinct.insert(debugNum + currentNum);
				if (startIndex == array.size())
				{
					break;
				}
				debugNum = array[startIndex++];
				
			}
		}
	}
	return count;
}

/*
Name : FindIndex
Description : Find the closest index the sums to the given range
parameters: vector<long long> & array input array
int currentNumber : the value to compare with
int numToCompare : value to find -10000 or 10000
int currentIndex : start search from here
return type: int index value
*/
long long int FindIndex(vector<long long> & array, long long int currentNumber, long long int currentIndex)
{
	long long int numToFind = -10000 - currentNumber;
	long long int debugNum = array[array.size() - 1];
	if (numToFind > debugNum || (currentIndex == array.size()-1))
	{
		return -1;
	}
	return binSearchLeast(array, currentIndex, array.size() - 1, numToFind);
}

/*
Name : binSearchLeast
Description : Find the least number in the array greater than number
parameters: vector<long long> & array input array
int start, end: search areas
int number : number to find
int numToCompare : value to find -10000 or 10000
return type: int index value
*/
long long int binSearchLeast(vector<long long> & array, long long int start, long long int end, long long int number)
{
	long long int mid = (start + end) / 2;
	if ((start == end) || (start + 1 == end))
	{
		return end;//return highest
	}
	if (array[mid] == number)
	{
		return mid;
	}
	if (array[mid] > number)
	{
		return binSearchLeast(array, start, mid, number);
	}
	else
	{
		return binSearchLeast(array, mid, end, number);
	}
}