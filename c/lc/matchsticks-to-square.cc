// TL
// O(3^|nums|)
class Solution {
public:
	static bool makesquare(const vector<int>& nums) {
		int sz = nums.size();
		if (!sz)
			return false; // pidarasen
		int p = accumulate(nums.begin(), nums.end(), 0);
		int l = p/4;
		const int ONES = (1<<sz)-1;
		vector<bool> one_side(ONES+1);
		for (int i=1; i<=ONES; i++) {
			int sm = 0;
			for (int b=0; b<sz; b++)
				sm += nums[b] * ((i>>b) & 1);
			one_side[i] = (sm == l);
		}
		vector<bool> dp(one_side);
		for (int side=1; side<4; side++) {
			for (int msk=ONES; msk>0; msk--) {
				int nmsk = ONES & ~msk;
				for (int s=nmsk; s; s=(s-1) & nmsk)
					dp[msk | s] = (dp[msk | s] || (dp[msk] && one_side[s]));
			}
		}
		return dp[ONES];
	}
};
