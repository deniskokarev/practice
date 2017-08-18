#include <iostream>
/* CodeForces CF818C problem */
using namespace std;

struct P {
	int x, y;
};

constexpr int sz = 100000+2;

int hl[sz]; // horiz to the left
int hr[sz]; // horiz to the right
int vu[sz]; // vert up
int vd[sz]; // vert down

int main(int argc, char **argv) {
	int d, n, m;
	cin >> d >> n >> m;
	P dd[d][2];
	for (auto &c:dd) {
		int x1, x2, y1, y2;
		cin >> x1 >> y1 >> x2 >> y2;
		c[0] = {min(x1,x2), min(y1,y2)};
		c[1] = {max(x1,x2), max(y1,y2)};
	}
	int cl, cr, ct, cb;
	cin >> cl >> cr >> ct >> cb;
	for (auto &c:dd) {
		if (c[0].x == c[1].x) {
			// vert
			hl[c[0].x+1]++;
			hr[c[0].x-1]++;
			vu[c[1].y]++;
			vd[c[0].y]++;
		} else {
			// horiz
			hl[c[1].x]++;
			hr[c[0].x]++;
			vu[c[0].y+1]++;
			vd[c[0].y-1]++;
		}
	}
	for (int i=1; i<sz; i++) {
		hl[i] += hl[i-1];
		vu[i] += vu[i-1];
	}
	for (int i=sz-2; i>=0; i--) {
		hr[i] += hr[i+1];
		vd[i] += vd[i+1];
	}
#if 0
	cerr << "hl: ";
	for (int i=0; i<=n+1; i++)
		cerr << hl[i] << ' ';
	cerr << endl;
	cerr << "hr: ";
	for (int i=0; i<=n+1; i++)
		cerr << hr[i] << ' ';
	cerr << endl;
	cerr << "vu: ";
	for (int i=0; i<=m+1; i++)
		cerr << vu[i] << ' ';
	cerr << endl;
	cerr << "vd: ";
	for (int i=0; i<=m+1; i++)
		cerr << vd[i] << ' ';
	cerr << endl;
#endif
	int ans = 0;
	for (int i=0; i<d; i++) {
		auto &c = dd[i];
		if (c[0].x == c[1].x) {
			// vert
			if (hl[c[0].x] == cl && hr[c[0].x] == cr &&
				vu[c[1].y] == ct+1 && vd[c[0].y] == cb+1) {
				ans = i+2;
				break;
			}
		} else {
			// horiz
			if (vu[c[0].y] == ct && vd[c[0].y] == cb &&
				hl[c[1].x] == cl+1 && hr[c[0].x] == cr+1) {
				ans = i+2;
				break;
			}
		}
	}
	cout << (ans-1) << endl;
	return 0;
}
