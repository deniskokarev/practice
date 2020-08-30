#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
/* CodeForces CF...C problem */
using namespace std;

bool can_make_good(vector<int> &bb, int psz) {
	int sz = bb.size();
	int hi = INT_MIN;
	int f=psz, b=sz-1;
	while (f<b) {
		if (bb[f] < bb[b]) {
			if (bb[f] < hi)
				return false;
			else
				hi = bb[f++];
		} else {
			if (bb[b] < hi)
				return false;
			else
				hi = bb[b--];
		}
	}
	return true;
}

int main(int argc, char **argv) {
	int t;
	cin >> t;
	while (t--) {
		int n;
		cin >> n;
		vector<int> bb(n);
		for (auto &b:bb)
			cin >> b;
		int f=0, t=n-1;
		while (f<=t) {
			int m = (f+t)/2;
			if (can_make_good(bb, m))
				t = m-1;
			else
				f = m+1;
		}
		cout << t+1 << '\n';
	}
	return 0;
}
