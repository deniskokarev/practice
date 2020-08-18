
class Solution {
	static constexpr int SZ = 10000;
	vector<int> dp;
public:
	Solution():dp(SZ) {
		for (int i=1; i<SZ; i++) {
			dp[i] = dp[i-1]+1;
			if (i%2 == 0)
				dp[i] = min(dp[i], dp[i/2]+1);
			if (i%3 == 0)
				dp[i] = min(dp[i], dp[i/3]+1);
		}
	}
	int minDays(int n) {
		queue<int> qq;
		unordered_map<int,int> dist;
		qq.push(n);
		int mn = INT_MAX;
		while (!qq.empty()) {
			int i = qq.front();
			qq.pop();
			int d = dist[i];            
			if (i<SZ) {
				if (dp[i]+d-10 > mn)
					break;
				mn = min(mn, dp[i]+d);
			} else {
				if ((i % 3 == 0) && !dist[i/3]) {
					dist[i/3] = d+1;
					qq.push(i/3);
				}
				if ((i % 2 == 0) && !dist[i/2]) {
					dist[i/2] = d+1;
					qq.push(i/2);
				}
				if (!dist[i-1]) {
					dist[i-1] = d+1;
					qq.push(i-1);
				}
			}
		}
		return mn;
	}
};

