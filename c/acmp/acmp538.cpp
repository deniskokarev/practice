/* ACMP 538 */
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <cmath>

using namespace std;

struct P {
	short x, y;
	int sd(const P &b) const {
		int dx = x-b.x;
		int dy = y-b.y;
		return dx*dx+dy*dy;
	}
};

// to be declared an array of node -> (dist, from_node, color)
struct DFC {
	int sq;
	short from;
	short color;
};

inline short alt(short color) {
	return color%2+1;
}

int main(int argc, char **argv) {
	short n;
	cin >> n;
	P pp[n];
	for (auto &p:pp)
		cin >> p.x >> p.y;
	// min spanning tree using Prim
	DFC aa[n+1];
	fill(aa, aa+n+1, DFC{INT_MAX, -1, 0}); // min arcs to node
	short v = 0;
	aa[v] = {0, 0, 1};
	int nc = 1;
	while (nc < n) {
		int mnv = n;
		for (short j=0; j<n; j++) {
			if (aa[j].color == 0) {
				DFC dfc {pp[v].sd(pp[j]), v, 0};
				if (aa[j].sq > dfc.sq)
					aa[j] = dfc;
				if (aa[mnv].sq > aa[j].sq)
					mnv = j;
			}
		}
		v = mnv;
		aa[v] = {0, 0, alt(aa[aa[v].from].color)};
		nc++;
	}
	int md = INT_MAX;
	for (short i=0; i<n-1; i++)
		for (short j=i+1; j<n; j++)
			if (aa[i].color == aa[j].color)
				md = min(md, pp[i].sd(pp[j]));
	cout << fixed << setprecision(9) << sqrt(md)/2 << endl;
	for (int i=0; i<n; i++)
		cout << aa[i].color << ' ';
	cout << endl;
	return 0;
}
