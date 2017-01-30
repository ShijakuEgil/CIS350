/*******************************
Egil Shijaku
Program 1 (Pokemon GO GO)
CIS 350 (online)
Prof. Bruce Elenbogen
*******************************/

/*************************************************************************************
DESCRIPTION:
The purpose of this program is to permute the different locations of Pokemon given 
by the user and give back the shortest distance traveled together with the path to 
follow in order to achieve that distance. 
The user input will consist of only integers for the locations and strings for the 
Pokemon names. The first input will be an integer n (0 < n < 11) that will determine 
the amount of locations of Pokemon to be permuted by the program. Each of the next 
inputs will consist of 2 integers separated by a space that will represent the number 
of blocks North- South or East - West respectively.Next input required after the two 
integers will be the name of the Pokemon located at that location. This data will 
determine the location for one Pokemon and will be repeated n times. 
The output will consist of one line of integers that will represent the order of 
locations visited together with the number of blocks traveled that will represented 
by the last integer in the line of output. The program will also make sure that only 
unique Pokemon locations are calculated because nobody needs to catch the same 
Pokemon twice. If two or more locations have the same Pokemon than only the location
that produces the shortest path together with the other locations will be shown in 
line of output.
*************************************************************************************/

#include<iostream>
#include<algorithm>
#include<vector>
#include<string>
using namespace std;

struct Locations 
{/***********************************************
	 Purpose :  Contains the informations needed 
				for each location entered.
 ***********************************************/
	int x;
	int y;
	string name;
	int pos;
	Locations(int px, int py, string nm, int p) {
		x = px;
		y = py;
		name = nm;
		pos = p;
	}
	friend bool operator < (const Locations & lhs, const Locations & rhs) 
	{
		return lhs.pos < rhs.pos;
	}
     friend bool operator > (const Locations & lhs, const Locations & rhs)
     {
          return lhs.pos > rhs.pos;
     }
};
class FindShortPath 
{
     int k = 0;
	vector<Locations> duplicatePokemonLocations;
	vector<Locations> uniquePokemonLocations;
	vector<vector<Locations>> uniquePaths;
	vector<Locations> winnerPath;
	int shortestPath;
     bool check = false;
public:
	FindShortPath(vector<Locations> loc) 
	{/***********************************************
	 Purpose :  Constructor for FindShortPath class.
				Divides the vector of Locations into 
				a vector of only locations that are 
				unique, and vector of duplicate 
				locations.
	 Pre	:	vector<Locations> needed to create class.
	 Post	:	two vectors created that are stored 
				in the private parameters of class.
	 ***********************************************/
		for (int i = 0; i < loc.size(); i++) 
		{
			uniquePokemonLocations.push_back(loc[i]);
			for (int j = i + 1; j < loc.size(); j++) 
			{
				if (loc[j].name == loc[i].name) 
				{
					duplicatePokemonLocations.push_back(loc[j]);
					loc.erase(loc.begin() + j);
					j = i;// if the j-th locations is deleted than the size 
						  // of the duplicate vector has changed therefore j 
						  // will not point at the right index.
				}
			}
		}
	}

	vector<Locations> getDuplicatePokemon()
	{/************************************
	 Purpose :  Returns a vector with all the 
				duplicate locations entered.
	 ************************************/
		return duplicatePokemonLocations;
	}
	vector<Locations> getUniquePokemon() 
	{/************************************
	 Purpose :  Returns a vector with all the 
				unique locations entered.
	 ************************************/
		return uniquePokemonLocations;
	}
	vector<vector<Locations>> getUniquePaths()
	{/************************************
	 Purpose :  Returns a vector that 
				contains all the paths with
				locations that do not contain 
				same Pokemon.		
	 ************************************/
		return uniquePaths;
	}
	vector<Locations> getWinnerPath()
	{
		return winnerPath;
	}
	int getShortestPath()
	{
		return shortestPath;
	}

	void setAllUniquePaths(vector<Locations> location, int n) 
	{/***********************************************
	 Purpose :  Recursive function is needed to create 
				all possible combinations of unique locations
				to permute.
	 Pre	:	A vector that has only the first entered
				locations that do not have similar Pokemon, 
				together with an intiger n (0 < n < location.size())
				that symbolizes the index of the element that 
				is being compared with the other locations 
				that have the same Pokemon as this one.

	 Post	:	A vector containing vectors that only 
				containing paths through locations that 
				do not contain same Pokemon.
	 ***********************************************/
          cout << "this is n from recursive function : " << n<< endl;
		if (n == 0) 
		{
			uniquePaths.push_back(location);
			for (int i = 0; i < duplicatePokemonLocations.size(); i++) 
			{
				if (location[0].name == duplicatePokemonLocations[i].name) 
				{
					location[0] = duplicatePokemonLocations[i];
					uniquePaths.push_back(location);
				}
			}
		}

		if (n > 0) 
		{
			for (int i = 0; i < duplicatePokemonLocations.size(); i++) 
			{
				if (location[n].name == duplicatePokemonLocations[i].name) 
				{
					location[n] = duplicatePokemonLocations[i];
					if (n == 1) 
					{
						setAllUniquePaths(location, n - 1);
					}
					else {
						setAllUniquePaths(location, 0);
						setAllUniquePaths(location, n - 1);
					}
				}
			}
		}
	}
     void deleteSameLocations(vector<Locations> & locations)
     {
          for (int i = 0; i < locations.size(); i++)
          {
               for (int j = i + 1; j < locations.size(); j++)
               {
                    if (locations[i].x == locations[j].x && locations[i].y == locations[j].y)
                    {
                         locations.erase(locations.begin() + j);
                         j = i;
                    }
               }
          }
     }

	void findShortestPath(vector<Locations> locations) 
     {    
		int path;
          cout << "this is the print before: ";
          print(locations);
          cout << endl;
          deleteSameLocations(locations);
          cout << "this is the print after : ";
          print(locations);
          cout << endl;
		do 
          {
               
               cout << "this is k from next permutation : " << k << endl;
               k++;
			for (int i = 0; i < locations.size(); i++)
			{
				if (i == 0) 
                    {
					path = abs(locations[i].x + locations[i].y);
				}
				if (i > 0) 
                    {
					path += abs((locations[i - 1].x - locations[i].x)) 
						+ abs((locations[i - 1].y - locations[i].y));
				}
				if (i == locations.size() - 1) 
                    {
					path += abs(locations[i].x + locations[i].y);
				}
			}
			if (check ==  false) {
				shortestPath = path;
				winnerPath = locations;
                    check = true;
			}
			if  (check == true )
               {
				if (path < shortestPath) 
                    {
					shortestPath = path;
					winnerPath = locations;
				}
			}
		} while (next_permutation(locations.begin(), locations.end()));
	}

     void print(vector<Locations> loc)
     {/***********************************************
      Purpose :  To print the path in a single line
      output of positions of Locations
      entered from the user.
      Pre	:	vector<Locations> needed to cout
      positions.
      Post	:	Single line output with integers
      symbolizing the path taken.
      ***********************************************/
          for (auto i : loc) {
               cout << i.pos << " ";
          }
     }
};



void print(vector<Locations> loc) 
{/***********************************************
	 Purpose :  To print the path in a single line 
				output of positions of Locations 
				entered from the user.
	 Pre	:	vector<Locations> needed to cout 
				positions.
	 Post	:	Single line output with integers 
				symbolizing the path taken.
	 ***********************************************/
	for (auto i : loc) {
		cout << i.pos << " ";
	}
}

int main() 
{
	int x;
	int y;
	string name;
	int n; 
	vector<Locations> locations;

	cin >> n;// number of locations to enter

	for (int i = 1; i < n + 1; i++) 
	{
		cin >> x >> y >> name;
		Locations loc(x, y, name, i);// an object created with all info for location
		locations.push_back(loc);// storing all locations in a vector of type Locations 
	}
	FindShortPath path(locations);

	for (int i = 0; i < path.getUniquePokemon().size(); i++) 
	{
		path.setAllUniquePaths(path.getUniquePokemon(), i);// sets all paths with locations without the same Pokemon.
	}
	for (auto i : path.getUniquePaths()) 
	{
		path.findShortestPath(i);
	}
	print(path.getWinnerPath());
	cout << path.getShortestPath() << endl;

	return 0;
}
