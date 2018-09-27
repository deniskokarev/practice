#include <iostream>
#include <vector>
#include <map>
/* ROI 2013E */
using namespace std;

struct P {
	int h;
};

int main(int argc, char **argv) {
	int n;
	cin >> n;
	vector<P> pp(n, P {0}); // planets
	int ff[n];				// fuel types
	for (auto &f:ff)
		cin >> f;
	map<int,int> f2p;  // fuel type -> planet pos
	int up = n-1;      // unresolved planets
	f2p[ff[up]] = n-1;
	for (int i=n-2; i>=0; i--) {
		if (f2p[ff[i]] != 0) {
			int h = pp[f2p[ff[i]]].h+1;
			pp[i] = P {h};
			for (int j=i+1; j<up; j++) {
				pp[j] = P {h};
				f2p[ff[j]] = j;
			}
			up = i;
		}
	}
	if (pp[0].h > 0) {
		cout << pp[0].h << endl;
		for (int i=0,fnd=pp[0].h; i<n-1; i++) {
			if (pp[i].h == fnd) {
				cout << i+1 << ' ';
				fnd--;
			}
		}
		cout << endl;
	} else {
		cout << 0 << endl;
	}
	return 0;
}
