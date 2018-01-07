/* ACMP 382 */
#include <iostream>
#include <vector>

using namespace std;

enum {
	EMPTY = 0,
	WALL = 1,
	VISITING = 2,
	REACHABLE = 3,
};

bool walk(vector<vector<int>> &map, int x, int y) {
	if (map[y][x] == REACHABLE) {
		return true;
	} else if (map[y][x] == WALL) {
		return false;
	} else if (map[y][x] == VISITING) {
		return false;
	} else {
		map[y][x] = VISITING;
		bool ok = walk(map, x-1, y) || walk(map, x+1, y) || walk(map, x, y-1) || walk(map, x, y+1);
		if (ok)
			map[y][x] = REACHABLE;
		else
			map[y][x] = EMPTY;
		return ok;
	}
}

int main(int argc, char **argv) {
	int n;
	cin >> n;
	vector<vector<int>> map(n+2, vector<int>(n+2, WALL));
	for (int y=1; y<=n; y++) {
		string s;
		cin >> s;
		for(int j=0; j<s.length(); j++)
			map[y][j+1] = (s[j] == '.')?EMPTY:WALL;
	}
	map[1][1] = map[n][n] = REACHABLE;
	for (int y=1; y<=n; y++)
		for (int x=1; x<=n; x++)
			walk(map, x, y);
	int len = 0;
	for (int y=1; y<=n; y++) {
		for (int x=1; x<=n; x++) {
			//cerr << map[y][x] << ' ';
			if (map[y][x] == REACHABLE) {
				if (map[y-1][x] == WALL)
					len++;
				if (map[y+1][x] == WALL)
					len++;
				if (map[y][x-1] == WALL)
					len++;
				if (map[y][x+1] == WALL)
					len++;
			}
		}
		//cerr << endl;
	}
	len -= 4;
	cout << len*5*5 << endl;
	return 0;
}
