/* ACMP 1464 */
/* max subsequence */

#include <iostream>
#include <vector>
#include <algorithm>
#include <deque>

using namespace std;

int main(int argc, char **argv) {
	int n, a, k, b, m;
	cin >> n >> a >> k >> b >> m;
	vector<int> aa(n);
	aa[0] = a;
	for (int i=1; i<n; i++)
		aa[i] = (aa[i-1]*k+b) % m;
	vector<pair<int,int>> ll(n+1, make_pair(INT_MAX, -1)); // mxlen -> (val,s_idx)
	int mx = 2;
	ll[0] = make_pair(INT_MIN, -1);
	vector<pair<int,int>> ss;	// (val,prev_s_idx) list
	for (int i=0; i<n; i++) {
		int a = aa[i];
		auto f = upper_bound(ll.begin(), ll.begin()+mx, make_pair(a, INT_MAX));
		if ((f-1)->first < a) { // ll[i] cannot be equal to ll[i+1]
			if (a < f->first) {
				ss.push_back(make_pair(a, (f-1)->second));
				*f = make_pair(a, ss.size()-1);
			}
			mx = max(mx, int(f-ll.begin())+1);
		}
	}
	deque<int> rv;
	for (int si=ll[mx-1].second; si>=0; si=ss[si].second)
		rv.push_front(ss[si].first);
	for (auto &a:rv)
		cout << a << ' ';
	cout << endl;
	return 0;
}
