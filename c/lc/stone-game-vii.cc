class Solution {
	static int score(vector<vector<int>> &cache, const vector<int> &sm, int b, int e) {
		if (cache[b][e] == INT_MIN) {
			if (b < e) {
				int sb = sm[e] - sm[b+1] - score(cache, sm, b+1, e);
				int se = sm[e-1] - sm[b] - score(cache, sm, b, e-1);
				cache[b][e] = max(sb, se);
			} else {
				cache[b][e] = 0;
			}
		}
		return cache[b][e];
	}
public:
	static int stoneGameVII(const vector<int>& stones) {
		int sz = stones.size();
		vector<int> sm(sz+1);
		for (int i=1; i<=sz; i++)
			sm[i] = sm[i-1]+stones[i-1];
		vector<vector<int>> cache(sz+1, vector<int>(sz+1, INT_MIN));
		return score(cache, sm, 0, sz);
	}
};
