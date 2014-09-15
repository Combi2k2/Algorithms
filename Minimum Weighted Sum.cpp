/*

This program runs the greedy algorithm that
schedules jobs in decreasing order of the difference (weight - length) and the weight (weight/height)
ip format
[number_of_jobs]
[job_1_weight] [job_1_length]
[job_2_weight] [job_2_length]
...
*/

#include <iostream>
#include <vector>
#include<fstream>
#include<algorithm>

using namespace std;


struct job
{
	double length;//all values to double in order to calculate the ratios accurately
	double weight;
	double ratio;
	double diff;

};

//return job with higher difference 
bool jobSorterDiff(job const& lhs, job const& rhs)
{
	if (lhs.diff != rhs.diff)
	{
		return (lhs.diff > rhs.diff);
	}
	if (lhs.weight != rhs.weight)
	{
		return (lhs.weight > rhs.weight);
	}
	return false;
}

//return job with higher ratio 
bool jobSorterRatio(job const& lhs, job const& rhs)
{
	return (lhs.ratio > rhs.ratio);
}

void readFile(vector<job> &jobs, string fileName)
{
	ifstream input(fileName);
	int size;
	input >> size;
	jobs.resize(size); //set job size
	for (int i = 0; i < size; i++)
	{
		input >> jobs[i].weight;
		input >> jobs[i].length;
		jobs[i].diff = jobs[i].weight - jobs[i].length;
		jobs[i].ratio = jobs[i].weight / jobs[i].length;
	}
}

double calculateWeightedSum(vector<job> &jobs)
{
	double sum = 0,completionTime=0;
	for(int i = 0; i < jobs.size(); i++)
	{
		completionTime += jobs[i].length;
		sum += (completionTime*jobs[i].weight);
	}
	return sum;
}

/*
For debugging
*/
void printJobs(vector<job> &jobs)
{
	for (int i = 0; i < jobs.size(); i++)
	{
		cout << "job :" << i << " length:" << jobs[i].length << " weight:" << jobs[i].weight << endl;
	}
}
void main()
{
	vector<job> jobs;
	string fileName = "test.txt";
	readFile(jobs, fileName);
	sort(jobs.begin(), jobs.end(), &jobSorterDiff);
	//printJobs(jobs);
	cout << "Weighted sum of differences is: " << (long long int)calculateWeightedSum(jobs)<<endl;
	sort(jobs.begin(), jobs.end(), &jobSorterRatio);
	//printJobs(jobs);
	cout << "Weighted sum of ratios is " << (long long int)calculateWeightedSum(jobs) << endl;
	system("pause");
}
