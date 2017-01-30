#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
using namespace std;
struct Location {
     int x;
     int y;
     int pos;
     string name; 
     Location(int px, int py, int ps, string mn)
     {
          x = px;
          y = py;
          pos = ps;
          name = mn;
     }
};
void print(vector<Location> loc)
{
     for (auto x : loc) {
          cout << x.pos << " ";
     }
}
void getUniquePoke( vector<Location> & pokeSpots, vector<Location> & repeatPoke)
{ 
     vector<Location> temp;
     for (int i = 0; i < pokeSpots.size(); i++)
     {
          temp.push_back(pokeSpots[i]);
          for (int j = i + 1; j < pokeSpots.size(); j++)
          {
               if (pokeSpots[j].name == pokeSpots[i].name)
               {
                    repeatPoke.push_back(pokeSpots[j]);
                    pokeSpots.erase(pokeSpots.begin() + j);
                    j = i;
               }
          }
     }
     pokeSpots = temp;
}

void nextDigitRotation(vector<vector<Location>>  & comboOfLocation,
     vector<Location> & pokeStops, vector<Location> repeatPoke, int n)
{
     for (int i = 0; i < repeatPoke.size(); i++)
     {
          if (pokeStops[n].name == repeatPoke[i].name)
          {
               pokeStops[n] = repeatPoke[i];
               comboOfLocation.push_back(pokeStops);
          }
     }
}

void firstDigitRotation(vector<vector<Location>> & comboOfLocations,
     vector<Location> pokeStops,vector<Location> repeatPoke)
{
     Location temp = pokeStops[0];
     comboOfLocations.push_back(pokeStops);
     for (int i = 0; i < repeatPoke.size(); i++)
     {
          if (pokeStops[0].name == repeatPoke[i].name)
          {
               pokeStops[0] = repeatPoke[i];
               comboOfLocations.push_back(pokeStops);
          }
     }
     pokeStops[0] = temp;
}

void getCombinationOfLocations(vector<vector<Location>> & comboOfLocation,
     vector<Location> pokeStop,vector<Location> repeatPoke, int n)
{
     if (n = 0)
     {
          
     }
     if (n == 1)
     {
          nextDigitRotation(comboOfLocation, pokeStop, repeatPoke, n);
          getCombinationOfLocations(comboOfLocation, pokeStop, repeatPoke, n - 1);
     }
     if (n > 1)
     {
          nextDigitRotation(comboOfLocation, pokeStop, repeatPoke, n);
          firstDigitRotation(comboOfLocation, pokeStop, repeatPoke);
          getCombinationOfLocations(comboOfLocation, pokeStop, repeatPoke, n - 1);
     }
}

int main() 
{
     int x;
     int y;
     int n;
     string name;
     vector<Location> pokeSpots;
     vector<Location> repeatPoke;
     vector<vector<Location>> comboLocation;
     vector<int> index;
     cin >> n;
     for (int i = 1; i < n + 1; i++)
     {
          cin >> x >> y >> name;
          Location loc(x, y, i, name); 
          pokeSpots.push_back(loc);    
     }
     getUniquePoke(pokeSpots, repeatPoke);
     print(pokeSpots);
     cout << endl;
     print(repeatPoke);
     cout << endl;
     index.resize(pokeSpots.size());
     for (int i = 0; i < pokeSpots.size(); i++)
     {
          for (int j = 0; j < repeatPoke.size(); j++)
          {
               if (pokeSpots[i].name == repeatPoke[j].name)
               {
                    index[i] = j;
                    break;
               }
          }

     }
     for (int i = 0; i < pokeSpots.size(); i++)
     {
          getCombinationOfLocations(comboLocation, pokeSpots, repeatPoke, i);
     }
     //cout << "index : ";
     for (auto x : comboLocation)
     {
          print(x);
          cout << endl;
     }
     
	return 0;
}