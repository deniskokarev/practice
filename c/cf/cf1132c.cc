#include <iostream>
#include <vector>
#include <algorithm>
/* CodeForces CF1132C problem */
using namespace std;

constexpr int MX = 5000;

struct R {
	int l, r;
	bool operator<(const R &o) const {
		return l<o.l;
	}
};

int main(int argc, char **argv) {
	int n, q;
	cin >> n >> q;
	vector<int> bb(MX+2);
	vector<R> rr(q);
	for (int i=0; i<q; i++) {
		int l, r;
		cin >> l >> r;
		rr[i] = {l, r};
		bb[l]++;
		bb[r+1]--;
	}
	for (int i=1; i<MX+2; i++)
		bb[i] += bb[i-1];
	int cnt = 0;
	for (int i=1; i<MX+2; i++)
		cnt += (bb[i] > 0);
	vector<int> ss2 = bb;
	for (int i=1; i<MX+2; i++)
		ss2[i] = min(ss2[i], 2) + ss2[i-1];
	vector<int> ss3 = bb;
	for (int i=1; i<MX+2; i++)
		ss3[i] = min(ss3[i], 3) + ss3[i-1];
	int mn = INT_MAX;
	sort(rr.begin(), rr.end());
	for (int i=0; i<q; i++) {
		for (int j=i+1; j<q; j++) {
			int	bare = 2*(rr[i].r-rr[i].l+1) - (ss2[rr[i].r]-ss2[rr[i].l-1]);
			bare += 2*(rr[j].r-rr[j].l+1) - (ss2[rr[j].r]-ss2[rr[j].l-1]);
			if (rr[i].r >= rr[j].l) {
				int l = rr[j].l;
				int r = rr[i].r;
				bare += 3*(r-l+1) - (ss3[r]-ss3[l-1]);
			}
			mn = min(mn, bare);
		}
	}
	cout << cnt - mn << endl;
	return 0;
}
