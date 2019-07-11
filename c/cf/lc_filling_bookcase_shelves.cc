#include <iostream>
#include <vector>
/* https://leetcode.com/contest/weekly-contest-143/problems/filling-bookcase-shelves/ */
using namespace std;

class Solution {
public:
	static int minHeightShelves(const vector<vector<int>>& books, int shelf_width) {
		int sz = books.size();
		vector<vector<int>> bb(sz+1, vector<int>(2));
		copy(books.begin(), books.end(), bb.begin()+1);
		vector<int> ans(bb.size(), INT_MAX/2);
		ans[0] = 0;
		for (int i=1; i<bb.size(); i++) {
			int w = bb[i][0];
			int mxh = bb[i][1];
			for (int j=i-1; j >= 0 && w <= shelf_width; j--) {
				ans[i] = min(ans[i], ans[j]+mxh);
				w += bb[j][0];
				mxh = max(mxh, bb[j][1]);
			}
		}
		return ans[sz];
	}
};

int main(int argc, char **argv) {
	cout << Solution::minHeightShelves({{1,1}}, 1) << '\n';
	cout << Solution::minHeightShelves({{1,1},{2,3},{2,3}}, 4) << '\n';
	cout << Solution::minHeightShelves({{1,1},{2,3},{2,3},{1,1},{1,1},{1,1},{1,2}}, 4) << '\n';
	cout << Solution::minHeightShelves({{7,3},{8,7},{2,7},{2,5}}, 10) << '\n';
	cout << Solution::minHeightShelves({{1,7},{6,4},{10,7},{6,10},{8,10},{1,10},{10,7}}, 10) << '\n';
	cout << Solution::minHeightShelves({{1,7},{6,4},{10,7}}, 10) << '\n';
	return 0;
}
