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
	pre:	thre integers required
	post:	an object that hold pipe data created*/
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
class Pipes2BUpgraded
{
	int * pickedPipes;
	int * treeHeight;
	int junctions;
public:
	Pipes2BUpgraded(int jct)
	{
		/*
		pre:	number of juctions is required
		post:	two array depending on number of jcts are created*/
		junctions = jct;
		pickedPipes = new int[jct + 1];
		treeHeight = new int[jct + 1];
		for (int i = 0; i <= jct; i++)
		{
			pickedPipes[i] = i;
			treeHeight[i] = 1;
		}
	}
	int find(int node)
	{
		/*
		pre:	a node that is include inside the array is required
		post:	value of pickedPipes[Node] that is not the same as node is returned */
		if (pickedPipes[node] != node)
		{
			pickedPipes[node] = find(pickedPipes[node]);
		}
		return pickedPipes[node];
	}
	void merge(int node1, int node2)
	{
		/*
		pre:	two nodes that belong in the range os junctions re needed and that are not in the same set
		post:	those two nodes are merged in one set*/
		int a = find(node1);
		int b = find(node2);

		if (treeHeight[a] > treeHeight[b])
		{
			pickedPipes[b] = a;
			treeHeight[a] += treeHeight[b];
		}
		else
		{
			pickedPipes[a] = b;
		}
		if (treeHeight[a] == treeHeight[b])
		{
			treeHeight[b]++;
		}
	}

	void print()
	{
		for (int i = 0; i <= junctions; i++)
		{
			cout << pickedPipes[i] << treeHeight[i] << endl;
		}
	}
};
class CityPipeLine
{
	int junctions;
	int pipes;
	vector<PipeData> pipeNet;
	int ptr = -1;
public:
	CityPipeLine(int n, int m)
	{
		/*
		pre:	exact nr of pipes and juctions needed
		post:	nr of jct and pipes are added to the graph*/
		junctions = n;
		pipes = m;
	}

	void addPipe(int jct1, int jct2, int flow)
	{
		/*
		pre:	data for one pipe is needed
		post:	an object with pipe data is added to pipeNet vector*/
		PipeData newPipe(jct1, jct2, flow);
		pipeNet.push_back(newPipe);
	}
	int findOptimalFlowSpan()
	{
		/*
		pre:	needs to be called after pipeNet is completed
		post: will return the max - min for the min spann tree*/
		ptr++;
		if (pipeNet.size() - ptr < junctions - 1)
			return -2;
		vector<int> minFlows;
		sort(pipeNet.begin(), pipeNet.end());
		Pipes2BUpgraded span(junctions);

		for (int it = ptr; it < pipeNet.size(); it++)
		{
			if (minFlows.size() == junctions - 1)
				break;
			int x = span.find(pipeNet[it].fstJct);
			int y = span.find(pipeNet[it].secJct);
			if (x != y)
			{
				minFlows.push_back(pipeNet[it].flow);
				span.merge(x, y);
			}
		}
		if (minFlows.size() == 1)
		{
			return minFlows[0];
		}
		if (minFlows.size() > 1)
		{
			return minFlows[minFlows.size() - 1] - minFlows[0];
		}
		return -1;
	}
	void print()
	{
		sort(pipeNet.begin(), pipeNet.end());
		for (auto x : pipeNet)
		{
			cout << x.fstJct << x.secJct << x.flow << endl;
		}
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
		for (int i = 0; i < m; i++)
		{
			cin >> a >> b >> w;
			city.addPipe(a, b, w);
		}
		int min = 1;
		if (m >= n - 1)
		{
			while (min > 0)
			{
				min = city.findOptimalFlowSpan();
				if (min != -2)
				{
					flows.push_back(min);
				}
			}
			sort(flows.begin(), flows.end());
			finalFlows.push_back(flows[0]);
		}
		else if (m < n - 1)
			finalFlows.push_back(-1);
	}
	for (auto x : finalFlows)
	{
		cout << x << endl;
	}

	return 0;
}