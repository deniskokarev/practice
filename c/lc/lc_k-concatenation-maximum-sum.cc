#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <climits>
/* https://leetcode.com/contest/weekly-contest-154/problems/k-concatenation-maximum-sum/ */
using namespace std;

class Solution {
	static constexpr int MOD = 1e9+7;
public:
	static int kConcatenationMaxSum(const vector<int>& arr, int k) {
		int mx = 0;
		int mn_pfx = 0;
		int sm = 0;
		for (int i=0; i<arr.size(); i++) {
			sm += arr[i];
			mx = max(mx, sm-mn_pfx);
			mn_pfx = min(mn_pfx, sm);
		}
		if (k>1) {
			int mn_sfx = 0;
			for (int a=0,i=arr.size()-1; i>=0; i--) {
				a += arr[i];
				mn_sfx = min(mn_sfx, a);
			};
			mx = max(int64_t(mx), int64_t(sm)*2 - mn_pfx - mn_sfx) % MOD;
			mx = max(int64_t(mx), int64_t(sm)*k - mn_pfx - mn_sfx) % MOD;
		}
		return mx;
	}
};

int main(int argc, char **argv) {
	cout << Solution::kConcatenationMaxSum({1,2}, 3) << endl;
	cout << Solution::kConcatenationMaxSum({1,-2,1}, 5) << endl;
	cout << Solution::kConcatenationMaxSum({-1,-2}, 7) << endl;
	cout << Solution::kConcatenationMaxSum({1,0,4,1,4}, 4) << endl;
	cout << Solution::kConcatenationMaxSum({-5,-2,0,0,3,9,-2,-5,4}, 5) << endl;
	cout << Solution::kConcatenationMaxSum({-5,4,-4,-3,5,-3}, 3) << endl;
	cout << Solution::kConcatenationMaxSum({-9,13,4,-16,-12,-16,3,-7,5,-16,16,8,-1,-13,15,3}, 6) << endl;
	return 0;
}
