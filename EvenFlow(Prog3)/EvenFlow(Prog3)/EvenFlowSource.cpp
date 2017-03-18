/*
Egil Shijaku
CIS 350
Prof. Bruce Elenbogen 
Program 3 (EvenFlow)

Description:
			This program will search through the data that is inputed by the user and pick only 
			*/

#include <iostream>
#include <string>
#include <vector>
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
};

struct CityPipeLine
{
	int junctions, pipes; // will total nr of vertices and edges
	vector<PipeData> allPipes;
	
	CityPipeLine(int n, int m)
		//constructor sets the amount of juctions and pipes in the city pipe line
	{
		junctions = n;
		pipes = m;
	}
	void addPipe(int fstJct, int secJct, int capFlow)
	{
		PipeData newPipe(fstJct, secJct, capFlow);
		allPipes.push_back(newPipe);
	}
};
struct PipesUpgraded
{
	int * pickedPipes;
	int junctions;

	PipesUpgraded(int jct)
	{
		junctions = jct;
		pickedPipes = new int[jct];
	}
};

int main()
{
	bool checkLoop = true;
	while (checkLoop)
	{
		int n, m; // will represent nr of junctions and nr of pipes 
		int completeGraph = (n*(n - 1)) / 2;// will represent the nr of pipes if 
											// all junctions were to be connected
		cin >> n >> m;
		if (n != 0 && m != 0)
		{
			CityPipeLine city(n, m);
			int firstJunct, secJunct, pipeFlow;
			for (int i = 0; i < m; i++)
			{
				city.addPipe(firstJunct, secJunct, pipeFlow);
			}
			if (m = completeGraph)
			{

			}
			if (m < completeGraph)
			{

			}

		}
		else
			checkLoop = false;
	}
	return 0;
}