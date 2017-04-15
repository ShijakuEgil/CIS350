/*
Egil Shijaku
Barbie & KenKen
Program 4 CIS 350
Prof. Bruce Elenbogen

Description:
*/

#include<iostream>
#include<algorithm>
#include<string>
#include<vector>
using namespace std;

class Board
{
	int size;
	vector<vector<int>> board;
	vector<int> numbers;

	bool findSolution(vector<vector<int>> ken, vector<int> nr, int row)
	{
		cout << "inside recursion" << endl;
		bool check;
		do
		{
			insertRow(ken, nr, row);
			if (checkRow(ken, nr, row) && row == size - 1)
			{
				return true;
			}
			if (checkRow(ken, nr, row))
			{
				check = findSolution(ken, nr, row + 1);
			}
			if (check)
			{
				return true;
			}
		} while (next_permutation(nr.begin(), nr.end()));
		return false;
	}

	void insertRow(vector<vector<int>> & ken, vector<int> nr, int row)
	{
		cout << "inside insertRow" << endl;
		for (int j = 0; j < size; j++)
		{
			ken[row][j] = nr[j];
		}
	}
	bool checkRow(vector<vector<int>> ken, vector<int> nr, int row)
	{
		cout << " inside checkRow" << endl;
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < row; j++)
			{
				if (ken[row][i] == ken[j][i])
				{
					return false;
				}
			}
		}
		return true;
	}
public:
	Board(int size)
	{
		this->size = size;
		for (int i = 0; i < size; i++)
		{
			numbers[i] = i + 1;
			cout << "constructor" << endl;
		}
	}
	void findSolution()
	{
		cout << " first findSolution" << endl;
		if (findSolution(board, numbers, 0))
		{
			cout << " before print" << endl;
			print();
		}
	}
	void print()
	{
		cout << "inside print" << endl;
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				cout << board[i][j] << " ";
			}
			cout << endl;
		}
	}
};

int main()
{
	cout << "main" << endl;
	int size;
	cin >> size;
	Board newBoard(size);
	cout << " board created" << endl;
	newBoard.findSolution();
	return 0;
}