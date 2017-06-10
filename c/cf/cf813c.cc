#include <iostream>
#include <vector>
#include <algorithm>
/* CodeForces CF813C problem */
using namespace std;

struct Node {
	vector<int> e;
	int u, d;	// up, max down
	int p;		// patent
};

void setstat(vector<Node> &t, int r, int p, int u) {
	Node &n = t[r];
	n.p = p;
	n.d = 1;
	n.u = u;
	for (auto e:n.e) {
		if (e != p) {
			setstat(t, e, r, u+1);
			n.d = max(n.d, t[e].d+1);
		}
	}
}

int main(int argc, char **argv) {
	int n, x;
	cin >> n >> x;
	vector<Node> t(n+1);
	for (int i=0; i<n-1; i++) {
		int a, b;
		cin >> a >> b;
		t[a].e.push_back(b);
		t[b].e.push_back(a);
	}
	setstat(t, 1, 0, 0);
	int mx = t[x].d-1+t[x].u;
	for (int i=0,b=x; i<(t[x].u)/2; i++) {
		mx = max(mx, t[x].u-i+t[b].d-1);
		b = t[b].p;
	}
	cout << mx*2 << endl;
	return 0;
}
