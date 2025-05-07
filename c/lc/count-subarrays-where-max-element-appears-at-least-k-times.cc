// https://leetcode.com/problems/count-subarrays-where-max-element-appears-at-least-k-times
class Solution {
public:
	// . . . . x . . . . x . . x
	//         ^         ^
	//         i         j
	static long long countSubarrays(const vector<int> &nn, int k) {
		int mx = *max_element(nn.begin(), nn.end());
		int sz = nn.size();
		int j = 0;
		int cnt = 0;
		while (cnt < k && j < sz) {
			cnt += (nn[j++] == mx);
		}
		int i = 0;
		uint64_t ans = 0;
		while (j < sz) {
			while (i < j && cnt == k) {
				cnt -= (nn[i++] == mx);
			}
			ans += i;
			cnt += (nn[j++] == mx);
		}
		while (i < j && cnt == k) {
			cnt -= (nn[i++] == mx);
		}
		ans += i;
		return ans;
	}
};

