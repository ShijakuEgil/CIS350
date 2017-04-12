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

struct Cage
{
	int result;
	char operand, id;
	vector<pair<int, int>> cellLoc;
	Cage(char cellId, int row, int col)
	{
		id = cellId;
		pair< int, int> p;
		p.first = row;
		p.second = col;
		cellLoc.push_back(p);
	}

	void addCageResult(int cageResult, char operand)
	{
		result = cageResult;
		this->operand = operand;
	}
	void addCageOp(int row, int col)
	{
		pair< int, int> p;
		p.first = row;
		p.second = col;
		cellLoc.push_back(p);
	}
	bool checkCage(vector<vector<int>> board)// checks the cages if they are loaded 
};
class KenKen
{
	vector<vector<int>> kenKen;
	vector<Cage> cages;
	vector<int> numbers;
	int size, nrCages;

	bool findSolution(vector<vector<int>> board, vector<int> nrs, int row)//recursive function to get solution
	{
		do
		{
			insertRow(board, nrs, row);//
			if (checkRow(board, row))
			{
				vector<int> cagePos;
				if (checkCage(board, row, cagePos ))
				{

				}
				if (findSolution(board, nrs, row + 1))
				{
					return true;
				}
			}
		} while (next_permutation(nrs.begin(), nrs.end())));
		return false;
	}
	bool checkRow(vector<vector<int>> board,  int row)
	{
		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < size; j++)
			{
				if (board[i][j] == board[row][j])
				{
					return false;
				}
			}
		}
		return true;
	}
	bool checkCage(vector<vector<int>> board, int row, vector<int> & cagePos)
	{
		for (int i = 0; i < cages.size(); i++)
		{
			if (cages[i].isFull(board))
			{
				cagePos.push_back(i);
				return true;
			}
		}
	}
	void InsertRow(vector<vector<int>> & board, vector<int> nrs, int row)
	{
		for (int i = 0; i < nrs.size(); i++)
		{
			board[row][i] == nrs[i];
		}
	}

public:
	KenKen(int sizeOfBoard, int nrOfCages)
	{
		size = sizeOfBoard;
		nrCages = nrOfCages;
		for (int i = 1; i <= size; i++)
		{
			numbers.push_back(i);
		}
	}
	void addCellPosition(char cellid, int row, int col)
	{
		bool check = false;
		if (cages.size() > 0)
		{
			for (int i = 0; i < cages.size(); i++)
			{
				if (cellid == cages[i].id)
				{
					check == true;
					cages[i].addCageOp(row, col);
				}
			}
			if (check == false)
			{
				Cage cage(cellid, row, col);
				cages.push_back(cage);
			}
		}
		else
		{
			Cage cage(cellid, row, col);
			cages.push_back(cage);
		}
	}
	void addCellOperand(int total, char operand, int i)
	{
		cages[i].addCageResult(total, operand);
	}
	void findSolution()
	{
		findsolution(kenKen, numbers, 0);
	}
};

int main()
{
	int sizeOfBoard, nrOfCages, cageOpResult;
	char cellId, operand;
	vector<vector<char>> board;
	vector<Cage> cages;

	cin >> sizeOfBoard >> nrOfCages;

	if ((sizeOfBoard >= 0 && sizeOfBoard <= 9) &&
		(nrOfCages >= sizeOfBoard && nrOfCages <= (pow(sizeOfBoard, 2) / 2)))
	{
		KenKen newBoard(sizeofBoard, nrOfcages);
		for (int i = 0; i < sizeOfBoard; i++)
		{
			for (int j = 0; j < sizeOfBoard; j++)
			{
				cin >> cellId;
				newBoard.addCellPosition(cellId, i, j);
			}
		}
		for (int i = 0; i < nrOfCages; i++)
		{
			cin >> cageOpResult >> operand;
			newBoard.addCellOperand(cageOpResult, operand, i);
		}
		newBoard.findSolution();
	}
	return 0;
}