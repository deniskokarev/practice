#include <iostream>
#include <vector>
/* CodeForces CF813C problem */
using namespace std;

struct Node {
	int l, r;
	int d;
	int p;
};

void setstat(vector<Node> &t, int r, int p) {
	if (r) {
		Node &n = t[r];
		n.p = p;
		setstat(t, n.l, r);
		setstat(t, n.r, r);
		n.d = max(t[n.l].d, t[n.r].d)+1;
	}
}

int main(int argc, char **argv) {
	int n, x;
	cin >> n >> x;
	vector<Node> t(n+1, {0, 0, 0, 0});
	for (int i=0; i<n-1; i++) {
		int a, b;
		cin >> a >> b;
		Node &n = t[a];
		if (!n.l)
			n.l = b;
		else
			n.r = b;
	}
	setstat(t, 1, 0);
	int l = 0;
	int b;
	for (b=x; b != 1; b=t[b].p,l++);
	b = x;
	int mx = 0;
	for (int i=0; i<l/2-1; i++) {
		mx = max(mx, l-i*2+t[n].d);
		b = t[b].p;
	}
	mx = max(mx, (t[x].d-1+l));
	cout << mx*2 << endl;
	return 0;
}
