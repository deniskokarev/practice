#include <iostream>
#include <algorithm>

#include <vector>
template<typename N> struct FenwickTree {
	using Container = std::vector<N>;
	using SZ = typename Container::difference_type;
	SZ sz;
	Container vv;
	FenwickTree(SZ _sz):sz(_sz),vv(sz,0){}
	void inc(SZ pos, N delta) {
		do vv[pos] += delta; while((pos=pos|(pos+1)) < sz);
	}
	// @return sum[0..last]
	N sum(SZ last) {
		N sum = 0;
		do sum += vv[last]; while ((last=(last&(last+1))-1) >= 0);
		return sum;
	}
};

/* ACMP 441 problem */
using namespace std;

int main(int argc, char **argv) {
	int n;
	cin >> n;
	vector<pair<int,int>> aa(n);
	for (int i=0; i<n; i++) {
		cin >> aa[i].first;
		aa[i].second = i;
	}
	vector<pair<int,int>> bb(n);
	for (int i=0; i<n; i++) {
		cin >> bb[i].first;
		bb[i].second = i;
	}
	sort(aa.begin(), aa.end());
	sort(bb.begin(), bb.end());
	vector<pair<int,int>> cc(n);
	for (int i=0; i<n; i++) {
		if (aa[i].first != bb[i].first) {
			cout << -1 << endl;
			return 0;
		}
		cc[i] = make_pair(bb[i].second, aa[i].second);
	}
	sort(cc.begin(), cc.end());
	FenwickTree<uint64_t> fwt(n);
	int64_t ans = 0;
	for (int i=0; i<n; i++) {
		int d = cc[i].second + fwt.sum(n-cc[i].second-1) - i;
		if (d < 0) {
			ans = -1;
			break;
		}
		ans += d;
		fwt.inc(n-cc[i].second-1, 1);
	}
	cout << ans << endl;
	return 0;
}
