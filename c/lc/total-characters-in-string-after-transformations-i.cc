// https://leetcode.com/problems/total-characters-in-string-after-transformations-i
class Solution {
	static constexpr int SZ = 26;
	static constexpr int MOD = 1e9 + 7;

	static void one_move(int cnt[SZ], int &z) {
		int a = (z + 1) % SZ;
		cnt[a] += cnt[z];
		cnt[a] %= MOD;
		z += SZ - 1;
		z %= SZ;
	}

public:
	static int lengthAfterTransformations(const string &s, int t) {
		int cnt[SZ]{};
		for (auto c: s) { cnt[c - 'a']++; }
		int z = SZ - 1;
		while (t--) { one_move(cnt, z); }
		int ans = accumulate(begin(cnt), end(cnt), 0, [](int a, int b) { return (a + b) % MOD; });
		return ans;
	}
};
