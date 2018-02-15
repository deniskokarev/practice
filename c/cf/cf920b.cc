#include <iostream>
#include <queue>

/* CodeForces CF920B problem */
using namespace std;

int main(int argc, char **argv) {
	int t;
	cin >> t;
	while (t--) {
		int n;
		cin >> n;
		struct S {
			int l, r, i;
		};
		deque<S> qq;
		for (int i=0; i<n; i++) {
			S s;
			cin >> s.l >> s.r;
			s.i = i;
			qq.push_back(s);
		}
		int ans[n];
		int ct = qq.front().l;
		while (!qq.empty()) {
			const S &h = qq.front();
			if (ct <= h.r) {
				ans[h.i] = ct;
				ct = max(ct+1, h.l);
			} else {
				ans[h.i] = 0;
			}
			qq.pop_front();
		}
		for (auto a:ans)
			cout << a << ' ';
		cout << endl;
	}
	return 0;
}
