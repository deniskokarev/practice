#include <iostream>
#include <vector>
#include <map>
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
			for (int j=i+1; j<up; j++) {
				pp[j] = P {h, -1};
				f2p[ff[j]] = i;
			}
			up = i;
		}
	}
	cout << pp[0].h << endl;
	for (int i=0,pi=0; i<pp[0].h; i++,pi=pp[pi].nxt)
		cout << pi+1 << ' ';
	cout << endl;
	return 0;
}
