#include <iostream>
#include <vector>
/* https://leetcode.com/problems/largest-1-bordered-square */
using namespace std;

class Solution {
public:
	static int largest1BorderedSquare(const vector<vector<int>>& grid) {
		vector<vector<int>> gu(grid);
		vector<vector<int>> gl(grid);
		vector<vector<int>> gd(grid);
		vector<vector<int>> gr(grid);
		int sz_w = grid[0].size();
		int sz_h = grid.size();
		for (int i=1; i<sz_h; i++) {
			for (int j=1; j<sz_w; j++) {
				gu[i][j] *= gu[i-1][j]+1;
				gl[i][j] *= gl[i][j-1]+1;
			}
		}
		for (int i=sz_h-2; i>=0; i--) {
			for (int j=sz_w-2; j>=0; j--) {
				gd[i][j] *= gd[i+1][j]+1;
				gr[i][j] *= gr[i][j+1]+1;
			}
		}
		int ans = 0;
		for (int i=0; i<sz_h; i++) {
			for (int j=0; j<sz_w; j++) {
				int l = min(gu[i][j], gl[i][j]);
				for (int x=j,y=i,d=1; x>=0 && y>=0 && l; x--,y--,l--,d++) {
					int r = min(gd[y][x], gr[y][x]);
					if (r>=d)
						ans = max(ans, d);
				}
			}
		}
		return ans*ans;
	}
};

int main(int argc, char **argv) {
	cout << Solution::largest1BorderedSquare({{1,1,1},{1,0,1},{1,1,1}}) << endl;
	cout << Solution::largest1BorderedSquare({{1,1,0,0}}) << endl;
	cout << Solution::largest1BorderedSquare({{1,1},{1,1}}) << endl;
	cout << Solution::largest1BorderedSquare({{0}}) << endl;
	return 0;
}
