// https://leetcode.com/problems/solving-questions-with-brainpower
class Solution {
	static constexpr int MX_SZ = 2e5 + 1;

public:
	static long long mostPoints(const vector<vector<int>> &qq) {
		int sz = qq.size();
		vector<uint64_t> dp_sfx(MX_SZ);
		for (int i = sz - 1; i >= 0; i--) {
			int pt = qq[i][0];
			int skip = qq[i][1];
			dp_sfx[i] = max(pt + dp_sfx[i + skip + 1], dp_sfx[i + 1]);
		}
		return dp_sfx[0];
	}
};

