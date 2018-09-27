#include <iostream>
#include <vector>
#include <map>
#include <climits>
/* ROI 2013E */
using namespace std;

struct P {
	int h;
	int nxt;
};

int main(int argc, char **argv) {
	int n;
	cin >> n;
	vector<P> pp(n, P {0, -1}); // planets
	vector<int> ff(n);				// fuel types
	for (auto &f:ff)
		cin >> f;
	map<int,int> f2p;  // fuel type -> planet pos
	int up = n-1;      // unresolved planets
	f2p[ff[up]] = n-1;
	for (int i=n-2; i>=0; i--) {
		if (f2p[ff[i]] != 0) {
			int h = pp[f2p[ff[i]]].h+1;
			pp[i] = P {h, f2p[ff[i]]};
			f2p[ff[i]] = i;
			for (int j=i+1; j<up; j++) {
				pp[j] = P {h, INT_MAX};
				f2p[ff[j]] = i;
			}
			up = i;
		}
	}
	if (pp[0].h > 0) {
		vector<int> ans;
		ans.push_back(1);
		int pn = pp[0].nxt;
		int mni = 0;
		int i = 0;
		while (pn != n-1) {
			for (; i<=pn; i++) {
				if (pp[i].h < pp[mni].h)
					mni = i;
			}
			ans.push_back(mni+1);
			pn = pp[mni].nxt;
		}
		cout << ans.size() << endl;
		for (auto a:ans)
			cout << a << ' ';
		cout << endl;
	} else {
		cout << 0 << endl;
	}
	return 0;
}
