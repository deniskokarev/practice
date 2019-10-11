#include <iostream>
/* https://leetcode.com/problems/numbers-with-repeated-digits/ */
using namespace std;

class Solution {
	static int a(int h, int len) {
		int res = 1;
		while (len--)
			res *= h--;
		return res;
	}
	static int digits(int *dd, int n) {
		int len = 0;
		while (n>0) {
			dd[len++] = n%10;
			n /= 10;
		}
		return len;
	}
	static int all_diff_r(int *dd, int len, int *may_use, int ntaken) {
		if (len>0) {
			int res = 0;
			for (int i=0; i<dd[len-1]; i++)
				res += may_use[i] * a(9-ntaken, len-1);
			if (may_use[dd[len-1]]) {
				may_use[dd[len-1]] = 0;
				res += all_diff_r(dd, len-1, may_use, ntaken+1);
			}
			return res;
		} else {
			return 0;
		}
	}
public:
    static int numDupDigitsAtMostN(int N) {
        int may_use[10] = {1,1,1,1,1,1,1,1,1,1};
		int dd[32];
		int len = digits(dd, N+1);
		int diff = all_diff_r(dd, len, may_use, 0);
		#if 1
		for (int l=1; l<len-2; l++)
			diff += a(9, l);
		#endif
		return N - diff;
    }
};

int main(int argc, char **argv) {
	cout << Solution::numDupDigitsAtMostN(20) << endl;
	cout << Solution::numDupDigitsAtMostN(100) << endl;
	cout << Solution::numDupDigitsAtMostN(1000) << endl;
	return 0;
}
