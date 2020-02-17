#include <iostream>
#include <vector>
#include <array>
/* https://leetcode.com/problems/matrix-cells-in-distance-order/ */
using namespace std;

class Solution {
public:
    static vector<vector<int>> allCellsDistOrder(int R, int C, int r0, int c0) {
		vector<vector<int>> ans(R*C, vector<int>(2));
		vector<pair<int,vector<int>>> srt(R*C);
		for (int i=0; i<R; i++)
			for (int j=0; j<C; j++)
				srt[i*C+j] = make_pair(abs(i-r0)+abs(j-c0), vector<int>({i,j}));
		sort(srt.begin(), srt.end());
		for (int i=0; i<R*C; i++) {
			ans[i] = move(srt[i].second);
			cerr << ans[i][0] << ' ' << ans[i][1] << '\n';
		}
		return ans;
    }
};

int main(int argc, char **argv) {
	Solution::allCellsDistOrder(2,2,0,1);
	return 0;
}
