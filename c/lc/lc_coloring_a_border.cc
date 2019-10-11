#include <iostream>
#include <vector>
/* https://leetcode.com/problems/coloring-a-border/ */
using namespace std;

static int enableFastIO() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	return 0;
}

static const int fastIO = enableFastIO();

struct P {
	int x, y;
};

static const P moves[] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

static bool is_border(const vector<vector<int>> &mm, int x, int y) {
	for (auto &m:moves)
		if (mm[x][y] != mm[x+m.x][y+m.y])
			return true;
	return false;
}

static void dfs(const vector<vector<int>> &mm, vector<vector<int>> &seen, int x, int y, int mc) {
	if (mm[x][y] == mc && !seen[x][y]) {
		if (is_border(mm, x, y))
			seen[x][y] = 2;
		else
			seen[x][y] = 1;
		for (auto &m:moves)
			dfs(mm, seen, x+m.x, y+m.y, mc);
	}
}

class Solution {
public:
    static vector<vector<int>> colorBorder(vector<vector<int>>& grid, int r0, int c0, int color) {
		vector<vector<int>> mm(grid.size()+2, vector<int>(grid[0].size()+2));
		for (int x=0; x<grid.size(); x++)
			for (int y=0; y<grid[0].size(); y++)
				mm[x+1][y+1] = grid[x][y];
		vector<vector<int>> seen(grid.size()+2, vector<int>(grid[0].size()+2));
		dfs(mm, seen, r0+1, c0+1, mm[r0+1][c0+1]);
		vector<vector<int>> res(grid.size(), vector<int>(grid[0].size()));
		for (int x=0; x<grid.size(); x++)
			for (int y=0; y<grid[0].size(); y++)
				if (seen[x+1][y+1] == 2)
					res[x][y] = color;
				else
					res[x][y] = grid[x][y];
		return res;
    }
};

int main(int argc, char **argv) {
	cout << "real answer" << endl;
	return 0;
}
