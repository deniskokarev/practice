// https://leetcode.com/problems/dungeon-game/
class Solution {
public:
	static int calculateMinimumHP(vector<vector<int>>& dp) {
		const int h = dp.size();
		const int w = dp[0].size();
		dp[h-1][w-1] = min(0, dp[h-1][w-1]);
		for (int i=h-2; i>=0; i--)
			dp[i][w-1] = min(0, dp[i][w-1]+dp[i+1][w-1]);
		for (int j=w-2; j>=0; j--)
			dp[h-1][j] = min(0, dp[h-1][j]+dp[h-1][j+1]);
		for (int i=h-2; i>=0; i--)
			for (int j=w-2; j>=0; j--)
				dp[i][j] = min(0, dp[i][j]+max(dp[i+1][j], dp[i][j+1]));
		return max(1, 1-dp[0][0]);
	}
};

