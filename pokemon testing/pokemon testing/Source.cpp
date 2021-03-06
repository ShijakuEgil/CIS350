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
the amount of locations of Pokemon to be permuted by the program. Each of the next 2
inputs will consist of 2 integers separated by a space that will represent the number
of blocks North- South or East - West respectively. The Next input required after the 2
integers will be the name of the Pokemon located at that location. This data will
determine the location for one Pokemon and will be repeated n times.
The output will consist of one line of integers that will represent the order of
locations visited together with the number of blocks traveled that will represented
by the last integer in the line of output. The program will also make sure that only
unique Pokemon locations are calculated because nobody needs to catch the same
Pokemon twice. If two or more locations have the same Pokemon than only the unique 
location that produce the shortest path will be shown in line of output.
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
	int x;//representing north - south 
	int y;// representing south - west
	string name;
	int pos; // represents the position of location in the order of input 
	Locations(int px, int py, string nm, int p) {
		x = px;
		y = py;
		name = nm;
		pos = p;
	}

};
class FindShortPath
{
	vector<Locations> duplicatePokemonLocations;
	vector<Locations> uniquePokemonLocations;
	vector<vector<Locations>> uniquePaths;

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
		{ /* Purpose  : Separating duplicate Pokemon locations 
						and unique one into two vectors*/
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

	void setAllUniquePaths(vector<Locations> location, int n)
	{/***********************************************
	 Purpose :  Recursive function is used to create
				all possible combinations of unique locations
				to permute.
	 Pre	 : 	A vector that has only the first entered
				locations that do not have similar Pokemon,
			    together with an intiger n (0 < n < location.size())
				that symbolizes the index of the element in that 
				vector that is being rotated with the other 
				locations that have the same Pokemon as this one.
				n can not be a negative number or recursive function 
				will run and infinite loop

	 Post	 :	A vector of vectors that only contain paths 
				through unique locations with unique Pokemon.
	 ***********************************************/
		if (n == 0)
		{ // if n = 0  no recursive call is needed because only the first 
		  // is being rotated in the vector.
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
		{/*if n > 0 than a recursive call is needed so that the previous elements
		   in the vector can be rotated with the elements in current n so a unique 
		   path can be achieved.*/
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
						setAllUniquePaths(location, 0);// The function is called recursively with n = 0
													   // so that a rotation of the first element is done
													   // with current new element in n.
						setAllUniquePaths(location, n - 1);
					}
				}
			}
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
	cout << endl;
}

int main()
{
     int x;
     int y;
     string name;
     int n;
     vector<Locations> locations;

     cin >> n; //number of locations user specified

     for (int i = 1; i < n + 1; i++)
     {
          cin >> x >> y >> name;
          Locations loc(x, y, name, i);// an object created with all info for location
          locations.push_back(loc);    // storing all locations in a vector of type Locations 
     }
     FindShortPath path(locations); // starts at line 51

     for (int i = 0; i < path.getUniquePokemon().size(); i++) // getUniquePokemon() starts at line 93
     {
          path.setAllUniquePaths(path.getUniquePokemon(), i); //sets all paths with locations without the same Pokemon.  Starts at line 110.
     }   
     
     for (auto i : path.getUniquePaths())
     {
          print(i);
     }
     return 0;
}