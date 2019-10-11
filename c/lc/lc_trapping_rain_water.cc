#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

/* https://leetcode.com/problems/trapping-rain-water/ */

using namespace std;

class Solution {
public:
	static int trap(const vector<int>& height) {
		vector<int> mxl(height);
		for (int i=1; i<mxl.size(); i++)
			mxl[i] = max(mxl[i], mxl[i-1]);
		vector<int> mxr(height);
		for (int i=mxr.size()-2; i>=0; i--)
			mxr[i] = max(mxr[i], mxr[i+1]);
		vector<int> mn(height.size());
		for (int i=0; i<mn.size(); i++)
			mn[i] = min(mxl[i], mxr[i]);
		int64_t sum1 = accumulate(height.begin(), height.end(), 0L);
		int64_t sum2 = accumulate(mn.begin(), mn.end(), 0L);
		return sum2 - sum1;
	}
};

int main(int argc, char **argv) {
	cout << Solution::trap({0,1,0,2,1,0,1,3,2,1,2,1}) << endl;
	cout << Solution::trap({2,0,2}) << endl;
	return 0;
}
