class Solution {
public:
	static int minimumTimeRequired(const vector<int>& jobs, int k) {
		int jsz = jobs.size();
		const int JONES = (1<<jsz)-1;
		vector<int> jsum(JONES+1);
		for (int i=0; i<=JONES; i++)
			for (int j=0; j<jsz; j++)
				jsum[i] += jobs[j] * ((i>>j) & 1);
		// profile DP O(k * 3^jsz)
		// solving on prefix of workers
		// adding w-th worker to already best dp[idx] solutions for w-1 workers
		// where idx specifies which jobs are done by w-1 workers
		// just need to find the best idx complement to JONES each time
		vector<int> dp(jsum);
		for (int w=1; w<k; w++) {
			for (int msk=JONES; msk>0; msk--) { // go backwards to update dp[] in-place
				// Enumerating all submasks of a given mask https://cp-algorithms.com/algebra/all-submasks.html
				int nmsk = JONES & (~msk);
				for (int s=nmsk; s; s=(s-1) & nmsk) // powerset of nmsk takes 3^jsz iterations altogether for all msk
					dp[msk | s] = min(dp[msk | s], max(dp[msk], jsum[s]));
			}
		}
		return dp[JONES];
	}
};
