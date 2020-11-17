class Solution {
	static constexpr int MX_N = 1000;
public:
	static bool canDistribute(const vector<int>& nums, const vector<int>& ords) {
		int cnt[MX_N+1]{0};
		for (int n:nums)
			cnt[n]++;
		vector<int> ncnt;
		for (int i=0; i<=MX_N; i++)
			if (cnt[i])
				ncnt.push_back(cnt[i]);
		int ords_sz = ords.size();
		// we go integer by integer augmenting all entries in DP vector, where dp[ord_msk] == 1 means orders from ord_msk
		// could be fulfilled by numbers we've seen so far
		vector<int> dp(1 << ords_sz, 0); // 1-dimension is enough for dp if we fill it from back
		dp[0] = 1; // we start with no orders
		for (int n:ncnt) {
			// fit[ord_msk] means the orders from ord_msk may be filled by current integer having count n
			vector<int> fit(1 << ords_sz, 0);
			for (int ord_msk=0; ord_msk < (1<<ords_sz); ord_msk++) {
				int sm = 0;
				for (int i=0,b=ord_msk; b; i++,b>>=1)
					sm += ords[i] * (b&1);
				fit[ord_msk] = (n >= sm);
			}
			// complementing dp[] with fit[]
			for (int ord_msk=(1 << ords_sz)-1; ord_msk >= 0; ord_msk--) {
				if (dp[ord_msk]) {
					int neg_msk = (~ord_msk) & (1 << ords_sz)-1;
					for (int s=neg_msk; s; s=(s-1)&neg_msk) // 3^ords_sz iterations altogether
						dp[ord_msk | s] |= fit[s];
				}
			}
		}
		return dp[(1 << ords_sz)-1];
	}
};
