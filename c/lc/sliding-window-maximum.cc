#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
//https://leetcode.com/problems/sliding-window-maximum

using namespace std;

class Solution {
public:
	vector<int> maxSlidingWindow(vector<int>& nums, int k) {
		if (k == 0 || nums.size() < k)
			return vector<int>();
		vector<int> ww(2*k, INT_MIN);
		for (int i=0; i<k; i++)
			ww[k+i] = nums[i];
		for (int j=2*k-1; j>0; j--)
			ww[j>>1] = max(ww[j>>1], ww[j]);
		vector<int> res(nums.size()-k+1);
		int ri = 0;
		res[ri++] = ww[1];
		for (int i=k; i<nums.size(); i++) {
			int j = k + i%k;
			ww[j] = nums[i];
			while (j>0) {
				ww[j>>1] = max(ww[j^1], ww[j]);
				j >>= 1;
			}
			res[ri++] = ww[1];
		}
		return res;
	}
};

int main(int argc, char **argv) {
	return 0;
}
