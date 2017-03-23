/*
Egil Shijaku
CIS 350
Prof. Bruce Elenbogen 
Program 3 (EvenFlow)

Description:
			Even flow program tries to translate in real world scenarios the usage of graphs, sets and also 
			the algorithms to find Minimum and Maximum spanning trees out of these very graphs.
			Even flow will create the representation of a city Pipe line configuration which is composed with 
			junctions and pipes that need to be upgraded. Out of this configuration of pipes and junctions, 
			whom represent edges and vertices, the algorithms in Even Flow program will find the spanning tree 
			with the minimum number of pipes that connect with all junctions given from the configuration plus 
			also this configuration will have the pipes that have the least flow difference

			The input:
			The first line of input will consist of two integers n and m separated by a space, where n is going 
			to be bigger or equal to 2 and m is going to be 0≤m≤n(n-1)/2. 
			n is going to represent the number of junctions in the city pipeline and m is going to represent the 
			total number or pipes in the same pipeline.
			The next m lines of input will represent each pipe and the capacity of the water flow that it can 
			handle. This data will be represented by three integers (a, b, w) that will be separated by a space. 
			a and b will represent the junctions that the pipe is connected by and w will represent the flow 
			capacity of that pipe. This input of three integers will be on a newline for each pipe. There will 
			be no pipes that connect to the same junction, also there will be no pipes that connect to the same 
			two junctions.
			The program will be able to compute multiple pipeline configurations so if the input for one pipeline 
			configuration is done, you can start a new configuration by simply inputting a new n and m. The 
			looping process will start again and the same process as above can be followed.
			To finish the input process and have the program give you an output for the configurations that have 
			been inputted so far, the user will need to enter 0 0 separated by a space to indicate that there 
			isn’t any more data.

			The output:
			The output will consist of one integer that will represent the difference of the biggest flow capacity
			pipe with the smallest flow capacity pipe in the spanning tree found.

			*/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

struct PipeData
{
	int fstJct, secJct, flow;
	PipeData(int fJ, int sJ, int flw)
	{
		fstJct = fJ;
		secJct = sJ;
		flow = flw;
	}
	friend bool operator < (PipeData lhs, PipeData rhs)
	{
		return lhs.flow < rhs.flow;
	}
};

struct CityPipeLine//representing the graph given
{
	int junctions, pipes; // will total nr of vertices and edges
	vector<PipeData> allPipes; //will store all pipes of the graph together with their respective data
	
	CityPipeLine(int n, int m)//constructor sets the amount of juctions and pipes in the city pipe line
	{
		junctions = n;
		pipes = m;
	}
	void addPipe(int fstJct, int secJct, int capFlow)
	{
		PipeData newPipe(fstJct, secJct, capFlow);
		allPipes.push_back(newPipe);
	}

	int kSpanPipeLn()// will find the min spanning tree and max spanning tree and also find 
					//	the difference of biggest and smallest flow on both of those trees and return the smallest
	{
		sort(allPipes.begin(), allPipes.end());
	}
	int pSpanPipeLn()
	{

	}
};

struct Pipes2BUpgraded
{
	int * pickedPipes;
	int junctions;
	vector<int> flows;

	Pipes2BUpgraded(int jct)
	{
		junctions = jct;
		pickedPipes = new int[jct];

		for (int i = 0; i <= jct; i++)
		{
			pickedPipes[i] = -1;
		}
	}
};

int main()
{
	bool checkLoop = true;
	int n, m; // will represent nr of junctions and nr of pipes 
	int completeGraph = (n*(n - 1)) / 2;// will represent the nr of pipes if all n junctions were to be connected(complete graph)
	while (checkLoop)// loop as long as n and m are not 0 0
	{
		cin >> n >> m;
		if (n != 0 && m != 0)
		{
			CityPipeLine city(n, m); // create empty representation of graph with n  vertices and m edges
			int firstJunct, secJunct, pipeFlow;
			for (int i = 0; i < m; i++)
			{
				cin >> firstJunct >> secJunct >> pipeFlow; // get data from user
				city.addPipe(firstJunct, secJunct, pipeFlow); // add  edge with the appropriate data to the graph
			}
			if (m = completeGraph) // if graph given is a complete graph use prim's algorithm for better time 
			{

			}
			if (m < completeGraph) // if graph given is not complete graph use kruskal algorithm for better time
			{

			}
		}
		else
			checkLoop = false;
	}
	return 0;
}