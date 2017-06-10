#include <iostream>
#include <vector>
#include <algorithm>
/* CodeForces CF813C problem */
using namespace std;

struct Node {
	vector<int> e;
	int u, d;	// up, max(down)
	int p;		// parent
};

void trstat(vector<Node> &t, int r, int p, int u) {
	Node &n = t[r];
	n.p = p;
	n.d = 0;
	n.u = u;
	for (auto e:n.e) {
		if (e != p) {
			trstat(t, e, r, u+1);
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
	trstat(t, 1, 0, 0);
	int l = t[x].u;
	int mx = t[x].d+l;
	for (int i=0,b=x; 2*i<l; i++) {
		mx = max(mx, l-i+t[b].d);
		b = t[b].p;
	}
	cout << mx*2 << endl;
	return 0;
}
