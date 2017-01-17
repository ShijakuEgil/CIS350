/*
Egil Shijaku
Program 1
CIS 350
Prof. Bruce Elenbogen
*/

/*
DESCRIPTION:
The purpose of this program is to permute the different locations of pokemons given by the user 
and give back the smallest distance traveled together with the path to follow in order to 
achieve that distance. The user input will consist of only integers for the locations and 
strings for the pokemon names. The first input will be an integer n (0 < n < 11) that will 
determine the amount of locations that pokemons are located nearby. Each of the next n inputs 
will consist of 2 integers separated by a space that will represent the number or blocks, first 
integer representing North - South direction and the other East - West direction. Separated by 
a space will be the next input that willconsist of the name of the pokemon located at that 
location. This will be all af the data required for one from the n inputs. 
The output will consist of integers that will represent the order of locations visited. If any 
locations have the same pokemon only the location with the shortest path to the starting 
location will be calculated. The last integer will represent the number of blocks traveled 
following the path displayed from the previous integers. 
*/

#include<iostream>
#include<algorithm>
#include<vector>
#include<string>
using namespace std;

struct Location
{//REASON: used for storing the coordinates of each pokemon together with their names.
	int N_S;
	int E_W;
	string pokemon;
	Location(int x = 0, int y = 0, string nm = "")// default construction created for easy coding
	{
		N_S = x;
		E_W = y;
		pokemon= nm;
	}
};
class Path
{
	vector<Location> blocks;
	vector<int> nr;
public:
	Path(vector<Location> loc)
	{
		blocks = loc;
	}
	void deleteSamePokemon()
	{
		for (int i = 0; i < blocks.size(); i++)
		{
			for (int j = i + 1; j < blocks.size(); j++)
			{
				if (blocks[i].pokemon == blocks[j].pokemon)
				{
					if (blocks[i].pokemon == blocks[j].pokemon && (blocks[i].N_S + blocks[i].E_W) > (blocks[j].N_S + blocks[j].E_W))
					{
						blocks.erase(blocks.begin() + i);
					}
					if (blocks[i].pokemon == blocks[j].pokemon && (blocks[i].N_S + blocks[i].E_W) <= (blocks[j].N_S + blocks[j].E_W))
					{
						blocks.erase(blocks.begin() + j);
					}
				}
			}
		}
		for (auto i : blocks)
		{
			cout << i.N_S << i.E_W << i.pokemon << " ";
		}
		cout << endl;
	}
	void permute()
	{
		vector<vector<int>> shortestPerm;
		vector<int> allPaths;
 		int shortestPath;
		int path;

		for (int i = 0; i < blocks.size(); i++)
		{
			nr.push_back(i);
		}
		
		do {
			for (int i = 0; i < nr.size(); i++)
			{
				if (i == 0)
				{
					path = abs(blocks[nr[i]].N_S + blocks[nr[i]].E_W);
				}
				if (i > 0)
				{
					path = path + abs(blocks[nr[i - 1]].N_S - blocks[nr[i]].N_S) +
						abs(blocks[nr[i - 1]].E_W - blocks[nr[i]].E_W);
				}
			}
			path = path + abs(blocks[nr[nr.size() - 1]].N_S + blocks[nr[nr.size() - 1 ]].E_W);
			allPaths.push_back(path);
			shortestPerm.push_back(nr);
		} while (next_permutation(nr.begin(), nr.end()));

		for (auto i : shortestPerm)
		{
			cout << i << " ";
		}
		shortestPath = *min_element(allPaths.begin(), allPaths.end());

		cout <<  shortestPath << endl;
	}
};
int main()
{
	int nrOfPokemon;
	int x;
	int y;
	string name;
	vector<Location> blocks;

	cin >> nrOfPokemon;
	while (nrOfPokemon <= 0 || nrOfPokemon >= 11)
	{
		cin >> nrOfPokemon;
	}
	for (int i = 0; i < nrOfPokemon; i++)
	{
		cin >> x >> y>> name;
		Location location(x,y,name);
		blocks.push_back(location);
	}
	Path shortPath(blocks);
	shortPath.deleteSamePokemon();
	shortPath.permute();
	return 0;
}
