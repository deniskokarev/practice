#include <iostream>
#include <map>
#include <algorithm>
/* CodeForces CF988D problem */
using namespace std;

int main(int argc, char **argv) {
	int n;
	cin >> n;
	int64_t xx[n];
	for (auto &x:xx)
		cin >> x;
	sort(xx, xx+n);
	map<int64_t,int> x2p;
	for (int i=0; i<n; i++) {
		int64_t d = 1;
		for (int l2=0; l2<32; l2++,d*=2) {
			if (x2p.find(xx[i]-d) != x2p.end() && x2p.find(xx[i]-d*2) != x2p.end()) {
				cout << 3 << endl;
				cout << xx[i]-2*d << ' ' << xx[i]-d << ' ' << xx[i] << endl;
				return 0;
			}
		}
		x2p[xx[i]] = i;
	}
	x2p.clear();
	for (int i=0; i<n; i++) {
		int64_t d = 1;
		for (int l2=0; l2<32; l2++,d*=2) {
			if (x2p.find(xx[i]-d) != x2p.end()) {
				cout << 2 << endl;
				cout << xx[i]-d << ' ' << xx[i] << endl;
				return 0;
			}
		}
		x2p[xx[i]] = i;
	}
	cout << 1 << endl;
	cout << xx[0] << endl;
	return 0;
}
