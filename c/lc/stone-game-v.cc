class Solution {
public:
	static int stoneGameV(const vector<int>& stone) {
        constexpr int MXSZ = 500;
        int dp[MXSZ+1][MXSZ+1]; // dp[len][beg] - best score
        memset(dp, 0, sizeof(dp));
        int sz = stone.size();
		vector<int> sm(sz+1);
		for (int i=1; i<=sz; i++)
			sm[i] = sm[i-1]+stone[i-1];
		for (int l=1; l<=sz; l++) {
			for (int b=0; b+l<=sz; b++) {
				for (int mid=1; mid<l; mid++) {
					int lsm = sm[b+mid] - sm[b];
					int rsm = sm[b+l] - sm[b+mid];
					if (lsm > rsm)
						dp[l][b] = max(dp[l][b], rsm + dp[l-mid][b+mid]);
					else if (lsm < rsm)
						dp[l][b] = max(dp[l][b], lsm + dp[mid][b]);
					else
						dp[l][b] = max(dp[l][b], lsm + max(dp[l-mid][b+mid], dp[mid][b]));
				}
			}
		}
		return dp[sz][0];
	}
};

