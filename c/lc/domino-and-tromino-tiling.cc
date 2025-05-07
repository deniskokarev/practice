// https://leetcode.com/problems/domino-and-tromino-tiling
class Solution {
	static constexpr unsigned MOD = 1e9 + 7;

	enum {
		NONE = 0x0,
		UP = 0x1,
		DOWN = 0x2,
	};

public:
	static int numTilings(int n) {
		unsigned dp[2][4]{};// none, up, down, both
		dp[0][UP | DOWN] = 1;
		for (int i = 0; i < n; i++) {
			int p = i & 1;
			int c = (i + 1) & 1;;
			// p    p .
			// p    p .
			dp[c][NONE] = dp[p][UP | DOWN];
			// .    c c
			// .    c .
			//
			// .    c c
			// p    p .
			dp[c][UP] = dp[p][DOWN] + dp[p][NONE];
			// like UP
			dp[c][DOWN] = dp[p][UP] + dp[p][NONE];
			// p    p c
			// p    p c
			//
			// p    p c
			// .    c c
			//
			// .    c c
			// p    p c
			//
			// .    c c
			// .    c c
			dp[c][UP | DOWN] = dp[p][UP | DOWN] + dp[p][DOWN] + dp[p][UP] + dp[p][NONE];
			for (auto &d: dp[c]) { d %= MOD; }
		}
		return dp[n & 1][UP | DOWN];
	}
};

