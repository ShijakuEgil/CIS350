#include<iostream>
#include<algorithm>
#include<string>
#include<vector>
using namespace std;

struct Cage
{
	
	char Id, oper;
	int maxRow = -1;
	int maxCol = -1;
	int res;
	vector<pair<int, int>> cageLoc;
	Cage(char cellId, int row, int col)
	{
		maxRow = row;
		maxCol = col;
		Id = cellId;
		pair<int, int> cellLoc;
		cellLoc.first = row;
		cellLoc.second = col;
		cageLoc.push_back(cellLoc);
	}
	void addCellLoc(int row, int col)// adss locations of points that make up
	{
		if (row > maxRow)
			maxRow = row;
		if (col > maxCol)
			maxCol = col;
		pair<int, int> cellLoc;
		cellLoc.first = row;
		cellLoc.second = col;
		cageLoc.push_back(cellLoc);
	}
	bool checkIfFull(int row)
	{
		if (row >= maxRow)
			return true;
		else
			return false;
	}
	bool getResult(int ** board, int row)
	{
		if (checkIfFull(row))
		{
			vector<int> points;
			int result = 0;
			switch (oper)
			{
			case '+':
				for (auto x : cageLoc)
				{
					result += board[x.first][x.second];
				}
				if (result == res)
					return true;
				else
					return false;
			case 'x':
				result = 1;
				for (auto x : cageLoc)
				{
					result *= board[x.first][x.second];
				}
				if (result == res)
					return true;
				else
					return false;
			case '/':
				points.clear();
				for (auto x : cageLoc)
				{
					points.push_back(board[x.first][x.second]);
				}
				sort(points.begin(), points.end());
				result = points[1] / points[0];
				if (result == res)
					return true;
				else
					return false;
			case '-':
				points.clear();
				for (auto x : cageLoc)
				{
					points.push_back(board[x.first][x.second]);
				}
				sort(points.begin(), points.end());
				result = points[1] - points[0];
				if (result == res)
					return true;
				else
					return false;

			}
		}
		else
			return false;
	}
};

class Board
{
	int boardSize, cages;
	vector<int> numbers;
	vector<Cage> cageObj;
	int ** boards;

	bool findSolution(int** board, vector<int> nr, int row)
	{
		cout << "recursive " << row << endl;

		bool check = false;
		do
		{
			insertRow(nr, row);
			if (checkRow(board, nr, row) && row == boardSize - 1 && )
			{
				return true;
			}

			if (checkRow(board, nr, row))
			{
				check = findSolution(board, nr, row + 1);
			}
			if (check)
			{
				return true;
			}

		} while (next_permutation(nr.begin(), nr.end()));

		return false;
	}

	void insertRow(vector<int> nr, int row)
	{
		for (int j = 0; j < boardSize; j++)
		{
			boards[row][j] = nr[j];
		}
		//print();
	}

	bool checkRow(int ** board, vector<int> nr, int row)
	{
		for (int i = 0; i < boardSize; i++)
		{
			for (int j = 0; j < row; j++)
			{
				if (boards[row][i] == boards[j][i])
				{
					return false;
				}
			}
		}
		return true;
	}
public:
	Board(int size, int nrCages)
	{
		cages = nrCages;
		boardSize = size;
		boards = new int * [size];
		cageObj.resize(cages);
		for (int i = 0; i < size; i++)
		{
			boards[i] = new int[size];
			numbers.push_back(i + 1);
		}
		
	}

	void findSolution()
	{
		if (findSolution(boards, numbers, 0))
		{
			print();
		}
		
	}
	void setCage(char cellId, int row, int col)
	{
		if (cageObj.size() == 0)
		{
			Cage newCage(cellId, row, col);
			cageObj.push_back(newCage);
		}
		else
		{
			bool check = false;
			for (auto x : cageObj)
			{
				if (cellId == x.Id)
				{
					x.addCellLoc(row, col);
					check = true;
				}
			}
			if (check == false)
			{
				Cage newCage(cellId, row, col);
				cageObj.push_back(newCage);
			}
		}
	}
	void addCageOperands(int result, char oper, int i)
	{
		cageObj[i].res = result;
		cageObj[i].oper = oper;
	}
	void print()
	{
		for (int i = 0; i < boardSize; i++)
		{
			for (int j = 0; j < boardSize; j++)
			{
				cout << boards[i][j] << " ";
			}
			cout << endl;
		}
	}
};

int main()
{
	int size, nrCages, operand;
	char cellId;
	cin >> size >> nrCages;
	if ((size >= 3 && size <= 9) && (nrCages >= size && nrCages <= pow(size, 2) / 2))
	{
		Board newBoard(size, nrCages);
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				cin >> cellId;
			}
		}
		for (int i = 0; i <= nrCages; i++)
		{
			cin >> operand >> cellId;
			newBoard.addCageOperands(operand, cellId, i);
		}
		newBoard.findSolution();
	}
	return 0;
}