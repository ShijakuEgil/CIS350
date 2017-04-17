#include<iostream>
#include<algorithm>
#include<string>
#include<vector>
using namespace std;
struct Pair
{
	int row;
	int col;
	Pair(int r, int c)
	{
		row = r;
		col = c;
	}
};
class Cage
{
	char id, op;
	int cellRow = -1, result;
	vector<int> test;
	vector<Pair> cagePoints;
public:

	Cage(char cId)
	{
		id = cId;
	}
	void setPoints(int row, int col)
	{
		if (row > cellRow)
			cellRow = row;
		Pair p(row, col);
		cagePoints.push_back(p);
		test.push_back(col);
	}
	char getId()
	{
		return id;
	}
	void setOp(char oper)
	{
		op = oper;
	}
	void setResult(int res)
	{
		result = res;
	}
	bool checkCage(int ** board, int row)
	{
		if (row < cellRow)
		{
			return true;
		}
		else
		{
			vector<int> points;
			int res = 0;
			switch (op)
			{
			case '+':
				for (auto x : cagePoints)
				{
					res += board[x.row][x.row];
				}
				if (result == res)
					return true;
				else
					return false;
			case 'x':
				result = 1;
				for (auto x : cagePoints)
				{
					result *= board[x.row][x.col];
				}
				if (result == res)
					return true;
				else
					return false;
			case '/':
				points.clear();
				for (auto x : cagePoints)
				{
					points.push_back(board[x.row][x.col]);
				}
				sort(points.begin(), points.end());
				result = points[1] / points[0];
				if (result == res)
					return true;
				else
					return false;
			case '-':
				points.clear();
				for (auto x : cagePoints)
				{
					points.push_back(board[x.row][x.col]);
				}
				sort(points.begin(), points.end());
				result = points[1] - points[0];
				if (result == res)
					return true;
				else
					return false;
			}
		}
	}
	void print()
	{
		//cout << "print from cage:" << endl;
		cout << id << " : ";
		vector<Pair> ::iterator it;
		for (it = cagePoints.begin(); it != cagePoints.end(); ++it)
		{
			cout << "(" << it->row << ", " << it->col << ")" << op << " " << result << " " << cellRow;
		}
		cout << endl;
	}
};
class Board
{
	int boardSize;
	int nrOfCages;
	int ** board;
	vector<int> nrs;
	vector<Cage> cages;
	vector<Cage> ::iterator it;
	Cage * c;
	bool findSolution(int** board, vector<int> nr, int row)
	{
		bool check = false;
		do
		{
			insertRow(nr, row);
			if (checkRow(board, nr, row) && row == boardSize - 1 && checkCages(board, row))
			{
				return true;
			}

			if (checkRow(board, nr, row) && checkCages(board, row))
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
	bool checkCages(int ** board, int row)
	{
		bool check;
		for (it = cages.begin(); it != cages.end(); ++it)
		{
			check = it->checkCage(board, row);
		}
	}
	void insertRow(vector<int> nr, int row)
	{
		for (int j = 0; j < boardSize; j++)
		{
			board[row][j] = nr[j];
		}
	}
	bool checkRow(int ** board, vector<int> nr, int row)
	{
		for (int i = 0; i < boardSize; i++)
		{
			for (int j = 0; j < row; j++)
			{
				if (board[row][i] == board[j][i])
				{
					return false;
				}
			}
		}
		return true;
	}
public:
	Board(int size, int cage)
	{
		boardSize = size;
		nrOfCages = cage;
		board = new int *[boardSize];
		for (int i = 0; i < boardSize; i++)
		{
			board[i] = new int[boardSize];
			nrs.push_back(i + 1);
		}
	}
	void findSolution()
	{
		if (findSolution(board, nrs, 0))
			print();
		else
			cout << "no solution" << endl;
	}
	void setCage(char id, int row, int col)
	{
		if (cages.size() == 0)
		{
			c = new Cage(id);
			c->setPoints(row, col);
			cages.push_back(*c);
		}
		else
		{
			bool check = false;
			for (it = cages.begin(); it != cages.end(); ++it)
			{
				if (id == it->getId())
				{
					check = true;
					it->setPoints(row, col);
				}
			}
			if (!check)
			{
				c = new Cage(id);
				c->setPoints(row, col);
				cages.push_back(*c);
			}
		}
	}
	void addCageOperands(vector<pair< int, char>> p)
	{
		int i = 0;
		for (it = cages.begin(); it != cages.end(); ++it)
		{
			it->setOp(p[i].second);
			it->setResult(p[i].first);
			i++;
		}
	}

	void print()
	{
		/*for (it = cages.begin(); it != cages.end(); ++it)
		{
		it->print();
		}*/
		for (int i = 0; i < boardSize; i++)
		{
			for (int j = 0; j < boardSize; j++)
			{
				cout << board[i][j] << " ";
			}
			cout << endl;
		}
	}
};

int main()
{
	int size, nrCages, operand;
	char cellId;
	vector<pair<int, char> > operands;
	cin >> size >> nrCages;

	if ((size >= 3 && size <= 9) && (nrCages >= size && nrCages <= pow(size, 2) / 2))
	{
		Board newBoard(size, nrCages);
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				cin >> cellId;
				newBoard.setCage(cellId, i, j);
			}
		}
		for (int i = 0; i < nrCages; i++)
		{
			cin >> operand >> cellId;
			pair<int, char> p;
			p.first = operand;
			p.second = cellId;
			operands.push_back(p);
		}
		newBoard.addCageOperands(operands);
		/*cout << "print form main: " << endl;*/
		newBoard.print();
	}
	system("pause");
	return 0;
}