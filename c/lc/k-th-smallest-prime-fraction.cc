/**
 * https://leetcode.com/problems/k-th-smallest-prime-fraction
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

class Solution {
	struct Q {
		int p, q;
		bool operator<(const Q &o) const {
			return int64_t(p)*o.q < int64_t(o.p)*q;
		}
	};
	static int cntLE(double key, Q &mx, const vector<int> &a) {
		int sz = a.size();
		int cnt = 0;
		for (int i=0; i<sz-1; i++) {
			int num = a[i];
			int f = i+1, t=sz;
			while (f<t) {
				int m = (f+t)/2;
				if (key < double(num)/a[m])
					f = m+1;
				else
					t = m;
			}
			if (f<sz) {
				cnt += sz-f;
				mx = max(mx, Q{num, a[f]});
			}
		}
		return cnt;
	}
public:
	static vector<int> kthSmallestPrimeFraction(const vector<int> &a, int k) {
		double f=0, t=1;
		while (true) {
			double m = (f+t)/2;
			Q mx {0, 1};
			int cnt = cntLE(m, mx, a);
			if (cnt > k)
				t = m;
			else if (cnt < k)
				f = m;
			else
				return {mx.p, mx.q};
		}
	}
};

int main(int argc, char **argv) {
	vector<int> a1 = Solution::kthSmallestPrimeFraction({1, 2, 3, 5}, 3);
	cout << a1[0] << " / " << a1[1] << endl;
	vector<int> a2 = Solution::kthSmallestPrimeFraction({1, 7}, 1);
	cout << a2[0] << " / " << a2[1] << endl;
	return 0;
}

