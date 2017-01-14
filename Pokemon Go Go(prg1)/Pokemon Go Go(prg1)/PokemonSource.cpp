/*
Egil Shijaku
Program 1
CIS 350
Prof. Bruce Elenbogen
*/

/*
The purpose of this program is to permute the different locations of pokemons given by the user 
and give back the smallest distance that can be traveled in blocks, also the path to follow in 
order to achieve the smallest distance. The user input will consist of only integers for the 
locations and strings for the pokemon names. The first input will be an integer n (0 < n < 11) 
that will determine the amount of locations that the user wants the program to permute through. 
Each of the next n inputs will consist of 2 integers separated by a space and the name of the 
pokemon located at that location. The output will consist of the locations in the permuted order
that add up to the smallest distance and the distance traveled in blocks
*/

#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

int main()
{
	int nrOfPokemon;
	int north, east;
	string name;
	vector<int> blocksNorth;
	vector<int> blocksEast;
	vector<string> pokemon;

	cin >> nrOfPokemon;
	while (nrOfPokemon <= 0 || nrOfPokemon >= 11)
	{
		cin >> nrOfPokemon;
	}
	for (int i = 0; i < nrOfPokemon; i++)
	{
		cin >> north >> east;
		getline(cin,name);
		blocksNorth.push_back(north);
		blocksEast.push_back(east);
		pokemon.push_back(name);
	}

	return 0;
}