// https://leetcode.com/problems/build-array-from-permutation/
// O(n) complexity
// O(1) extra space
// support n <= 2^31-1
class Solution {
	// makes a tour in 1-based positive permutation
	// replace nn[i] = - nn[nn[i]] on the way
	static void tour_shift_once(vector<int> &nn, const int p) {
		int b = nn[p];
		int p0 = p + 1;
		int p1 = nn[p0 - 1];
		while (p1 != p + 1) {
			nn[p0 - 1] = -nn[p1 - 1];
			p0 = p1;
			p1 = nn[p0 - 1];
		}
		nn[p0 - 1] = -b;
	}

public:
	static vector<int> &buildArray(vector<int> &nn) {
		int sz = nn.size();
		// +1
		transform(begin(nn), end(nn), begin(nn), [](int n) { return n + 1; });
		for (int i = 0; i < sz; i++) {
			if (nn[i] > 0) {
				// shift and * -1 that loop
				tour_shift_once(nn, i);
			}
		}
		// recover orig values
		transform(begin(nn), end(nn), begin(nn), [](int n) { return -n - 1; });
		return nn;
	}
};

