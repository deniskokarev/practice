#include <iostream>
#include <vector>
#include <algorithm>
/* https://leetcode.com/problems/moving-stones-until-consecutive/ */
using namespace std;

static int enableFastIO() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	return 0;
}

static const int fastIO = enableFastIO();

class Solution {
public:
    static vector<int> numMovesStones(int a, int b, int c) {
        int xx[3] {a, b, c};
		sort(xx, xx+3);
		int mn = 0;
		if (xx[0]+1 == xx[1] && xx[1]+1 == xx[2])
			mn = 0;
		else if (xx[0]+2 >= xx[1] || xx[1]+2 >= xx[2])
			mn = 1;
		else
			mn = 2;
		int mx = xx[2] - xx[1] - 1;
		mx += xx[1] - xx[0] - 1;
		return {mn, mx};
    }
};

int main(int argc, char **argv) {
	for (auto a:Solution::numMovesStones(1, 2, 5)) cout << a << ' '; cout << endl;
	for (auto a:Solution::numMovesStones(4, 3, 2)) cout << a << ' '; cout << endl;
	for (auto a:Solution::numMovesStones(3, 5, 1)) cout << a << ' '; cout << endl;
	for (auto a:Solution::numMovesStones(7, 4, 1)) cout << a << ' '; cout << endl;
	return 0;
}
