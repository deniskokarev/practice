class Solution {
public:
	static int maxCoins(const vector<int>& nums) {
		int sz = nums.size()+2;
		vector<int> nn(sz);
		copy(nums.begin(), nums.end(), nn.begin()+1);
		nn[0] = nn[sz-1] = 1;
		vector<vector<unsigned>> dp(sz, vector<unsigned>(sz));
		for (int l=2; l<sz; l++)
			for (int i=0; i+l<sz; i++)
				for (int k=i+1; k<i+l && k<sz; k++)
					dp[i][i+l] = max(dp[i][i+l], dp[i][k] + dp[k][i+l] + nn[i]*nn[k]*nn[i+l]);
		return dp[0][sz-1];
	}
};

