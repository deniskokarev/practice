#include <iostream>
#include <set>
#include <vector>
#include <cmath>

/* CodeForces CF830B problem */
using namespace std;

class IntervalSum {
	size_t sz;
	size_t psz;
	vector<int64_t> vv;
public:
	IntervalSum(size_t _sz):sz(_sz) {
		psz = (1ULL<<int(ceil(log2(sz))))-1;
		vv.resize(psz+sz);
	}
	void add(size_t pos, int64_t v) {
		size_t p = pos+psz+1;
		while (p>0) {
			vv[p-1] += v;
			p >>= 1;
		}
	}
	const int64_t total() const {
		return vv[0];
	}
	const int64_t gt(size_t pos) const {
		int64_t rc = 0;
		if (pos<sz-1) {
			size_t p = pos+psz+1;
			while (p>0) {
				if ((p & 1) == 0)
					rc += vv[p]; // add right sibling
				p >>= 1;
			}
		}
		return rc;
	}
	const int64_t ge(size_t pos) const {
		if (pos < sz)
			return gt(pos)+vv[pos+psz];
		else
			return 0;
	}
	const int64_t between(size_t b, size_t e) const {
		return ge(b)-ge(e);
	}
};

int main(int argc, char **argv) {
	int n;
	cin >> n;
	set<pair<int,int>> mx;
	for (int i=0; i<n; i++) {
		int a;
		cin >> a;
		mx.insert(make_pair(a, i));
	}
	IntervalSum taken(n);
	auto it = mx.begin();
	int64_t ans = it->second+1;
	auto lel = *it;
	taken.add(lel.second, 1);
	mx.erase(it);
	while (!mx.empty()) {
		it = mx.upper_bound(lel);
		if (it->first != lel.first)
			it = mx.upper_bound(make_pair(lel.first, -1));
		if (it->second > lel.second) {
			ans += it->second - lel.second - taken.between(lel.second, it->second) + 1;
		} else {
			ans += n - lel.second - taken.between(lel.second, n);
			ans += it->second - taken.between(0, it->second) + 1;
		}
		lel = *it;
		taken.add(lel.second, 1);
		mx.erase(it);
	}
	cout << ans << endl;
	return 0;
}
