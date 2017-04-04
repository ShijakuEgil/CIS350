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

#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
using namespace std;
struct PipeData
{
	/*
	Description:	creates an object of PipeData that contains all pipe info
	pre:			thre integers required
	post:			an object that hold pipe data created*/
	int fstJct, secJct, flow;
	PipeData(int fJ, int sJ, int flw)
	{
		fstJct = fJ;
		secJct = sJ;
		flow = flw;
	}
	friend bool operator < (PipeData lhs, PipeData rhs)
	{
		return lhs.flow < rhs.flow; // sorting the vector containing pipedata
	}
};
class Pipes2BUpgraded
{
	int * pickedPipes;
	int * treeHeight;
	int junctions;
public:
	Pipes2BUpgraded(int jct)
	{
		/*
		Description:	creates an array with the size of the junctions
						The corrensponding value will be the junction pointed
		pre:			number of juctions is required
		post:			two array depending on number of jcts are created*/
		junctions = jct;
		pickedPipes = new int[jct + 1];
		for (int i = 0; i <= jct; i++)
		{
			pickedPipes[i] = i;
		}
	}

	int find(int node)
	{
		/*
		Description:	returns the root of the node in the subtree
		pre:			a node that is include inside the array is required
		post:			value of pickedPipes[Node] that is not the same as node is returned */
		if (pickedPipes[node] != node)
		{
			pickedPipes[node] = find(pickedPipes[node]);
		}
		return pickedPipes[node];
	}
	void merge(int node1, int node2)
	{
		/*
		Description:	merge = union function... merges two nodes together.
		pre:			two nodes that belong in the range os junctions re needed and that are not in the same set
		post:			those two nodes are merged in one set*/
		int a = find(node1);
		int b = find(node2);

		if (pickedPipes[a] < pickedPipes[b])
		{
			pickedPipes[b] = a;
		}
		else
		{
			pickedPipes[a] = b;
		}
	}
};
class CityPipeLine
{
	int junctions;
	int pipes;
	vector<PipeData> pipeNet;
public:
	CityPipeLine(int n, int m)
	{
		/*
		Description:	creates a graph with only vertices no edges
		pre:			exact nr of pipes and juctions needed
		post:			nr of jct and pipes are added to the graph*/
		junctions = n;
		pipes = m;
	}

	void addPipe(int jct1, int jct2, int flow)
	{
		/*
		Description:	adds an edge to the graph 
		pre:			data for one pipe is needed
		post:			an object with pipe data is added to pipeNet vector*/
		PipeData newPipe(jct1, jct2, flow);
		pipeNet.push_back(newPipe);
	}
	int findOptimalFlowSpan()
	{
		/*
		Description:	find the spanning tree with the minimal flow difference 
						between max and min flow values
		pre:			needs to be called after pipeNet is completed a full 
		post:			will return the max - min for the min spann tree*/
		int minFlow = -2; 
		bool check = false;
		sort(pipeNet.begin(), pipeNet.end());

		while ((minFlow != 0 && minFlow != -1) && check == false)
		{ 
			Pipes2BUpgraded span(junctions);
			vector<int> minFlows;

			for (int i = 0; i < pipeNet.size(); i++)
			{
				int x = span.find(pipeNet[i].fstJct);
				int y = span.find(pipeNet[i].secJct);
				if (x != y)
				{
					minFlows.push_back(pipeNet[i].flow);
					span.merge(x, y);
				}
			}
			if (minFlows.size() < junctions - 1)
			{
				check = true;
			}
			if (minFlow == -2 && minFlows.size() < junctions - 1)
			{
				minFlow = -1;
				check = true;
			}
			if (minFlow == -2)
			{
				minFlow = minFlows[minFlows.size() - 1] - minFlows[0];
			}
			if(minFlow != -2 && check == false)
			{
				if (minFlow > minFlows[minFlows.size() - 1] - minFlows[0])
				{
					minFlow = minFlows[minFlows.size() - 1] - minFlows[0];
				}
			}
			pipeNet.erase(pipeNet.begin());
		}
		return minFlow;
	}
};
int main()
{
	vector<int> finalFlows;
	int n, m, a, b, w;
	while (cin >> n >> m && (n != 0 || m != 0))
	{
		vector<int> flows;
		CityPipeLine city(n, m);
		if (m > 0 && n >= 2)
		{
			for (int i = 0; i < m; i++)
			{

				cin >> a >> b >> w;
				city.addPipe(a, b, w);
			}
		}
		if (n != 0 && (m <= 1 || m > (n*(n - 1) / 2)))
		{
			finalFlows.push_back(-1);
		}
		else
		{
			int min = city.findOptimalFlowSpan();
			finalFlows.push_back(min);
		}
	}
	for (auto x : finalFlows)
	{
		cout << x << endl;
	}
	return 0;
}