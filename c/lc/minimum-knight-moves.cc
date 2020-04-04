#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <queue>
/* https://leetcode.com/contest/biweekly-contest-9/problems/minimum-knight-moves/ */
using namespace std;

struct P {
	int x, y;
};

static const P mv[8] = {{+2, +1}, {+1, +2}, {-1, +2}, {-2, +1}, {-2, -1}, {-1, -2}, {+1, -2}, {+2, -1}};

class Solution {
	static constexpr int SZ = 320;
public:
    static int minKnightMoves(int x, int y) {
        vector<vector<int>> bb(SZ*2, vector<int>(SZ*2));
		queue<P> qq;
		qq.push(P{SZ, SZ});
		bb[SZ][SZ] = 1;
		while (!qq.empty()) {
			P p = qq.front();
			qq.pop();
			int l = bb[p.x][p.y];
			for (auto m:mv) {
				P np = P {p.x + m.x, p.y + m.y};
				if (np.x >= 0 && np.x < SZ*2 && np.y >= 0 && np.y < SZ*2 && bb[np.x][np.y] == 0) {
					bb[np.x][np.y] = l+1;
					qq.push(np);
				}
			}
		}
		return bb[x+SZ][y+SZ]-1;
    }
};

int main(int argc, char **argv) {
	cout << Solution::minKnightMoves(2, 1) << endl;
	cout << Solution::minKnightMoves(5, 5) << endl;
	cout << Solution::minKnightMoves(130, -86) << endl;
	cout << Solution::minKnightMoves(209, -58) << endl;
	return 0;
}
