#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

/* CodeForces CF831C problem */
using namespace std;

int main(int argc, char **argv) {
	int k, n;
	cin >> k >> n;
	int64_t aa[k];
	cin >> aa[0];
	for (int i=1; i<k; i++) {
		cin >> aa[i];
		aa[i] += aa[i-1];
	}
	int64_t bb[n];
	for (auto &b:bb)
		cin >> b;
	sort(aa, aa+k);
	sort(bb, bb+n);
	int mn;
	mn = aa[0];
	for (auto &a:aa) {
		a -= mn;
		//cerr << a << ' ';
	}
	//cerr << endl;
	mn = bb[0];
	for (auto &b:bb) {
		b -= mn;
		//cerr << b << ' ';
	}
	//cerr << endl;
	vector<unordered_map<int, int>> ss(k);
	for (int i=0; i<k-1; i++)
		for (int j=k-1; j>i; j--)
			ss[i][aa[j]-aa[i]] = j;
	int ans = 0;
	for (int ai=0; ai<k; ai++) {
		int p = ai;
		int bi;
		int inc = (ai==0 || (aa[ai]>aa[ai-1]))?1:0;
		for (bi=1; bi<n && p<k; bi++) {
			int d = bb[bi]-bb[bi-1];
			while (p<k) {
				if (ss[p].find(d) == ss[p].end()) {
					goto nx;
				} else {
					p = ss[p][d];
					break;
				}
				p++;
			}
		}
	nx:
		if (bi == n)
			ans += inc;
	}
	cout << ans << endl;
	return 0;
}
