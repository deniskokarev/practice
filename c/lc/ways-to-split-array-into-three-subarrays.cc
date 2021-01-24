class Solution {
public:
	static int waysToSplit(const vector<int>& nums) {
		constexpr int MOD = 1e9+7;
		int sz = nums.size();
		vector<int> lsm(sz+1);
		for (int i=1; i<=sz; i++)
			 lsm[i] = lsm[i-1]+nums[i-1];
		vector<int> lo(sz+1);
		// for x in [0..lo[i]) lsm[x] <= lsm[i] - lsm[x]
		int i=0;
		for (int j=2; j<=sz; j++) {
			while (i<j && lsm[i] <= lsm[j]-lsm[i])
				i++;
			lo[j] = i;
		}
		uint64_t ans = 0;
		int rsm = 0;
		i = sz-1;
		for (int j=sz; j>0; j--) {
			rsm += nums[j-1];
			while (i > 0 && lsm[j-1] - lsm[i] <= rsm)
				i--;
			int d = lo[j-1] - i;
			if (d > 1)
				ans += d - 1;
		}
		return ans % MOD;
	}
};
