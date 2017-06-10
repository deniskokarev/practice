#include <iostream>
#include <vector>
#include <algorithm>
/* CodeForces CF813C problem */
using namespace std;

struct Node {
	vector<int> e;
	int d;
	int p;
};

void setstat(vector<Node> &t, int r, int p) {
	Node &n = t[r];
	n.p = p;
	n.d = 1;
	for (auto e:n.e) {
		if (e != p) {
			setstat(t, e, r);
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
	setstat(t, 1, 0);
	int l = 0;
	int b = x;
	for (b=x; b != 1; b=t[b].p,l++);
	b = x;
	int mx = t[x].d-1+l;
	for (int i=0; i<l/2-1; i++) {
		mx = max(mx, l-i+t[b].d-1);
		b = t[b].p;
	}
	cout << mx*2 << endl;
	return 0;
}
