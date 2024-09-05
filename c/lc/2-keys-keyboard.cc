// https://leetcode.com/problems/2-keys-keyboard
class Solution {
	static int fact(int n, int *ff) {
		int sz = 0;
		for (int f = 2; f * f <= n; f++) {
			while ((n % f) == 0) {
				ff[sz++] = f;
				n /= f;
			}
		}
		if (n > 1) {
			ff[sz++] = n;
		}
		return sz;
	}

public:
	static int minSteps(int n) {
		int ff[64];
		int sz = fact(n, ff);
		return accumulate(&ff[0], &ff[sz], 0);
	}
};

