#include <iostream>
/* CodeForces CF920B problem */
using namespace std;

int main(int argc, char **argv) {
	int t;
	cin >> t;
	while (t--) {
		int n;
		cin >> n;
		struct S {
			int l, r;
		} ss[n];
		for (auto &s:ss)
			cin >> s.l >> s.r;
		int ct = ss[0].l;
		for (int i=0; i<n-1; i++) {
			if (ct <= ss[i].r) {
				cout << ct << ' ';
				ct++;
				if (ct < ss[i+1].l)
					ct = ss[i+1].l;
			} else {
				cout << 0 << ' ';
				if (ct < ss[i+1].l)
					ct = ss[i+1].l;
			}
		}
		if (ct <= ss[n-1].r)
			cout << ct;
		else
			cout << 0;
		cout << endl;
	}
	return 0;
}
