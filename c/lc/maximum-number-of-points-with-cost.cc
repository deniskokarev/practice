// https://leetcode.com/problems/maximum-number-of-points-with-cost
class Solution {
public:
	static long long maxPoints(const vector<vector<int>> &pp) {
		int h = pp.size();
		int w = pp[0].size();
		vector<vector<long long>> dp(2, vector<long long>(w));
		copy(pp[0].begin(), pp[0].end(), dp[0].begin());
		for (int r = 1; r < h; r++) {
			fill(dp[r & 1].begin(), dp[r & 1].end(), 0);
			long long mx = 0;
			for (int c = 0; c < w; c++) {
				mx = std::max(mx - 1, dp[~r & 1][c]);
				dp[r & 1][c] = std::max(dp[r & 1][c], mx + pp[r][c]);
			}
			mx = 0;
			for (int c = w - 1; c >= 0; c--) {
				mx = std::max(mx - 1, dp[~r & 1][c]);
				dp[r & 1][c] = std::max(dp[r & 1][c], mx + pp[r][c]);
			}
		}
		return *max_element(dp[~h & 1].begin(), dp[~h & 1].end());
	}
};

