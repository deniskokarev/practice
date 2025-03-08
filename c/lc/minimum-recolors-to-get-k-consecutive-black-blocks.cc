// https://leetcode.com/problems/minimum-recolors-to-get-k-consecutive-black-blocks
class Solution {
	static bool is_black(char c) { return c == 'B'; }

public:
	static int minimumRecolors(const string &blocks, int k) {
		const int sz = blocks.size();
		vector<bool> cc(sz, false);
		int sm = 0;
		for (int i = 0; i < k; ++i) {
			bool is_b = is_black(blocks[i]);
			cc[i] = is_b;
			sm += is_b;
		}
		int ans = k - sm;
		for (int i = k; i < sz; ++i) {
			sm -= cc[i % k];
			bool is_b = is_black(blocks[i]);
			cc[i % k] = is_b;
			sm += is_b;
			ans = min(ans, k - sm);
		}
		return ans;
	}
};

