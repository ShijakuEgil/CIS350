/*
Egil Shijaku
Barbie & KenKen 
Program 4 CIS 350
Prof. Bruce Elenbogen

Description:
*/
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
//enum OP_ALPHABET{ add = '+', sub = '-', mul = 'x', div = '/' };
vector<pair<int, char>> cageOper;

class KenKen
{
	int sizeOfBoard;
	int board, cages;
	char ** squares;
public:
	KenKen(int n, int c)
	{
		board = n;// board size
		cages = c;//cages
		squares = new char * [n];
		for (int i = 0; i < n; i++)// making 2 dim array to
		{							// reapresent board
			squares[i] = new char[n];
		}
	}

	void add(char sqId, int i, int j)// adding identefiers to board square by square
	{
		squares[i][j] = sqId;
	}

	void addOperands(int opId, char operand)
	{
		pair<int, char> pair;
		pair.first = opId;
		pair.second = opId;
		cageOper.push_back(pair);
	}
	void print()
	{
		cout << "operands :";
		for (auto x : cageOper)
		{
			cout << x.first << " " << x.second << " ";
		}
		for (int i = 0; i < board; i++)
		{
			for (int j = 0; j < board; j++)
			{
				cout << squares[i][j];
				if (j == board - 1)
				{
					cout << endl;
				}
			}
		}
	}
};

int main()
{
	int boardSize, cages, opId;
	char squareId, operand;
	cin >> boardSize >> cages;
	KenKen newBoard(boardSize, cages);
	for (int i = 0; i < boardSize; i++)
	{
		for (int j = 0; j < boardSize; j++)
		{
			cin >> squareId;
			newBoard.add(squareId, i, j);
		}
	}
	for (int i = 0; i < cages; i++)
	{
		cin >> opId, operand;
		newBoard.addOperands(opId, operand);
	}

	newBoard.print();
	return 0;
}