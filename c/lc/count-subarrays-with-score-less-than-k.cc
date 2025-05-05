// https://leetcode.com/problems/count-subarrays-with-score-less-than-k
// O(n * log(n))
class Solution {
	static int bfind_from(const vector<uint64_t> &sml, int r, uint64_t k) {
		int f = 0, t = r;
		while (f < t) {
			int m = f + (t - f) / 2;
			auto score = (sml[r] - sml[m]) * (r - m);
			if (score >= k) {
				f = m + 1;
			} else {
				t = m;
			}
		}
		return f;
	}

public:
	static long long countSubarrays(const vector<int> &nums, long long k) {
		int sz = nums.size();
		vector<uint64_t> sml(sz + 1);
		uint64_t ans = 0;
		for (int i = 1; i <= sz; i++) {
			sml[i] = sml[i - 1] + nums[i - 1];
			ans += i - bfind_from(sml, i, k);
		}
		return ans;
	}
};

