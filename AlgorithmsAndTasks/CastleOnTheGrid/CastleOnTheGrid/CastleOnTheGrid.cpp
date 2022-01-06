#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>> changeGrid(vector<string>& grid)
{
	vector<vector<int>> result;

	for (string& row : grid)
	{
		vector<int> current;

		for (char& ch : row)
		{
			switch (ch)
			{
			case 'X':
				current.push_back(-2);
				break;
			case '.':
				current.push_back(-1);
				break;
			default:
				break;
			}
		}

		result.push_back(current);
	}

	return result;
}

bool valid(const vector<vector<int>>& grid, int x, int y)
{
	return (x >= 0 && x < grid.size()) &&
		(y >= 0 && y < grid.size()) &&
		(grid[x][y] != -2);
}

void moveGrid(vector<vector<int>>& grid, int iteratorX, int iteratorY, int mX, int mY, int step) {
	iteratorX += mX;
	iteratorY += mY;

	while (valid(grid, iteratorX, iteratorY)) {
		if (grid[iteratorX][iteratorY] > step + 1 || grid[iteratorX][iteratorY] == -1) {
			grid[iteratorX][iteratorY] = step + 1;
		}
		iteratorX += mX;
		iteratorY += mY;
	}
}

void initializeByPoint(vector<vector<int>>& grid, int startX, int startY, int step)
{
	//up
	moveGrid(grid, startX, startY, 1, 0, step);
	//down:
	moveGrid(grid, startX, startY, -1, 0, step);
	//left
	moveGrid(grid, startX, startY, 0, -1, step);
	//rigth
	moveGrid(grid, startX, startY, 0, 1, step);
}

void initialize(vector<vector<int>>& grid, int step)
{
	int size = grid.size();

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (grid[i][j] == step)
			{
				initializeByPoint(grid, i, j, step);
			}
		}
	}
}

int minimumMoves(vector<string> grid, int startX, int startY, int goalX, int goalY)
{
	vector<vector<int>> curr = changeGrid(grid);
	curr[startX][startY] = 0;
	int steps = 0;

	while (curr[goalX][goalY] == -1) {
		initialize(curr, steps);
		++steps;
	}

	return curr[goalX][goalY];
}

int main()
{
	std::vector<std::string> grind = {
						".X..XX...X",
						"X.........",
						".X.......X",
						"..........",
						"........X.",
						".X...XXX..",
						".....X..XX",
						".....X.X..",
						"..........",
						".....X..XX" };

	std::cout << minimumMoves(grind, 9, 1, 9, 6);

	return 0;
}