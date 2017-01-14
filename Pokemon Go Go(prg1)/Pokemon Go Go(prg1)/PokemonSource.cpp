/*
Egil Shijaku
Program 1
CIS 350
Prof. Bruce Elenbogen
*/

/*
The The program will take input from the user consisting of integers only. 
The first input will be an integer n (0< n < 11) that will determine */

#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

int main()
{
	int nrOfPokemon = 0;
	int north, east;
	vector<vector<int> > blocks;
	while (nrOfPokemon <= 0 || nrOfPokemon >= 11) 
	{
		cin >> nrOfPokemon;
	}
	for (int i = 0; i < nrOfPokemon; i++)
	{
		cin >> north >> east;

	}

	return 0;
}