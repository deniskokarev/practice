// https://leetcode.com/problems/number-of-sub-arrays-with-odd-sum
class Solution {
	static constexpr int MOD = 1e9 + 7;

public:
	static int numOfSubarrays(const vector<int> &aa) {
		// number of odd and even sums from 0..current
		int cnt[2]{1, 0};
		int sm = 0;
		int ans = 0;
		for (int a: aa) {
			sm += a;
			int o = sm & 1;
			ans += cnt[!o];
			ans %= MOD;
			cnt[o]++;
		}
		return ans;
	}
};

