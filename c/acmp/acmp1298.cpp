#include <iostream>
#include <vector>
#include <map>
/* ACMP 1298 */
using namespace std;

struct LP {
	int len;
	int pos;
	bool operator<(const LP &o) const {
		return len<o.len;
	}
};

int main(int argc, char **argv) {
	int n;
	cin >> n;
	vector<int> aa(n);
	for (auto &a:aa)
		cin >> a;
	vector<int> pos(n, -1);
	map<int,LP,std::greater<int>> hh;
	hh[INT_MAX] = LP {0, -1};
	hh[INT_MIN] = LP {0, -1};
	LP mx {0, -1};
	for (int i=0; i<n; i++) {
		auto fnd = hh.upper_bound(aa[i]);
		LP lp {fnd->second.len+1, i};
		pos[i] = fnd->second.pos;
		--fnd;
		if (fnd != hh.begin() && fnd->second.len <= lp.len)
			hh.erase(fnd);
		hh[aa[i]] = lp;
		mx = max(mx, lp);
	}
	cout << mx.len << '\n';
	vector<int> ans(mx.len);
	for (int i=mx.len-1,p=mx.pos; p>=0; p=pos[p],i--)
		ans[i] = p;
	for (auto a:ans)
		cout << aa[a] << ' ';
	cout << '\n';
	return 0;
}
