#include <iostream>
#include <vector>
#include <algorithm>

/* CodeForces CF808C problem */
using namespace std;

struct Cup {
	int i;
	int v;
	int f;
	int rem() const {
		return v-f;
	}
};

int main(int argc, char **argv) {
	int n, w;
	cin >> n >> w;
	vector<Cup> aa(n);
	for (int i=0; i<n; i++) {
		cin >> aa[i].v;
		aa[i].i = i;
		int f = (aa[i].v+1)/2;
		aa[i].f = f;
		w -= f;
	}
	sort(aa.begin(), aa.end(), [](const Cup &a, const Cup b){return a.v<b.v;});
	int i=0;
	while (i<n && w>0) {
		int per = w/(n-i);
		if (per >= aa[i].rem()) {
			int r = aa[i].rem();
			for (int j=i; j<n; j++) {
				aa[j].f += r;
				w -= r;
			}
		} else {
			int r = (w+n-i-1)/(n-i);
			for (int j=n-1; w>0 && j>=i; j--) {
				int mn = min(r, w);
				aa[j].f += mn;
				w -= mn;
			}
		}
		while (aa[i].rem() <= 0)
			i++;
	}
	if (w == 0) {
		sort(aa.begin(), aa.end(), [](const Cup &a, const Cup b){return a.i<b.i;});
		for (int i=0; i<n; i++) {
			cout << aa[i].f << ' ';
		}
	} else {
		cout << -1;
	}
	cout << endl;
	return 0;
}
