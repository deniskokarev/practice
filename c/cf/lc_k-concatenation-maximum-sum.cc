#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <queue>
/* https://leetcode.com/contest/weekly-contest-154/problems/k-concatenation-maximum-sum/ */
using namespace std;

class Solution {
	static constexpr int MOD = 1e9+7;
public:
	static int kConcatenationMaxSum(const vector<int>& arr, int k) {
		int mn_pfx = 0;
		for (int a=0,i=0; i<arr.size(); i++) {
			a += arr[i];
			mn_pfx = min(mn_pfx, a);
		};
		int mn_sfx = 0;
		for (int a=0,i=arr.size()-1; i>=0; i--) {
			a += arr[i];
			mn_sfx = min(mn_sfx, a);
		};
		if (k>1) {
			vector<int> sm(arr.size()*2+1);
			copy(arr.begin(), arr.end(), sm.begin()+1);
			copy(arr.begin(), arr.end(), sm.begin()+1+arr.size());
			for (int i=1; i<sm.size(); i++)
				sm[i] += sm[i-1];
			int mx2 = INT_MIN;
			int mn = 0;
			for (int i=1; i<sm.size(); i++) {
				mn = min(mn, sm[i]);
				mx2 = max(mx2, sm[i]-mn);
			}
			return max(mx2, int((int64_t(sm[arr.size()])*k % MOD - mn_pfx - mn_sfx) % MOD));
		} else {
			vector<int> sm(arr.size()+1);
			copy(arr.begin(), arr.end(), sm.begin()+1);
			for (int i=1; i<sm.size(); i++)
				sm[i] += sm[i-1];
			int mx1 = INT_MIN;
			int mn = 0;
			for (int i=1; i<sm.size(); i++) {
				mn = min(mn, sm[i]);
				mx1 = max(mx1, sm[i]-mn);
			}
			return mx1;
		}
	}
};

int main(int argc, char **argv) {
	cout << Solution::kConcatenationMaxSum({1,2}, 3) << endl;
	cout << Solution::kConcatenationMaxSum({1,-2,1}, 5) << endl;
	cout << Solution::kConcatenationMaxSum({-1,-2}, 7) << endl;
	cout << Solution::kConcatenationMaxSum({1,0,4,1,4}, 4) << endl;
	cout << Solution::kConcatenationMaxSum({-5,-2,0,0,3,9,-2,-5,4}, 5) << endl;
	return 0;
}
