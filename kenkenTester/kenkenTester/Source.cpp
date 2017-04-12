#include<iostream>
#include<algorithm>
#include<string>
#include<vector>
using namespace std;

class Board
{
	vector<vector<int>> board;
	vector<int> numbers;
	int boardSize;
	
	bool findSolution(vector<vector<int>> thisBoard, vector<int> thisNums, int row)
	{
		do 
		{
			if (checkBoard(thisBoard, thisNums, row))
			{
				for (int i = 0; i < boardSize; i++)
				{
					thisBoard[row][i] = thisNums[i];
				}
				return findSolution(thisBoard, thisNums, row++);
			}
			else 
				return false;
		} 
while (next_permutation(thisBoard.begin(), thisBoard.end()));
	}
	bool checkBoard(vector<vector<int>> thisBoard, vector<int> thisNums, int row)
	{
		for (int i = 0; i < boardSize; i++)
		{

		}
	}

public:
	Board(int size)
	{
		boardSize = size;
		for (int i = 0; i < size; i++)
		{
			numbers[i] = i + 1;
		}
	}

	void findSolution()
	{
		bool solu;
		solu = findSolution(board, numbers, 0);
	}

};

int main()
{
	int size;
	cin >> size;
	Board newBoard(size);
	newBoard.findSolution();
	return 0;
}