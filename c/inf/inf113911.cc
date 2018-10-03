#include <iostream>
#include <vector>
/* ROI 2018A */
using namespace std;

struct P {
	int a;
	int x, y;
	bool ismx;
	bool operator==(const P &b) const {
		return a == b.a; // as per input spec
	}
	bool operator<(const P &b) const {
		return a < b.a;
	}
};

int main(int argc, char **argv) {
	int n, m, q;
	cin >> n >> m >> q;
	vector<P> x_top(n, P {-1, 0, 0, false});
	vector<P> y_top(m, P {-1, 0, 0, false});
	for (int x=0; x<n; x++) {
		for (int y=0; y<m; y++) {
			P a {-1, x, y, false};
			cin >> a.a;
			x_top[x] = max(x_top[x], a);
			y_top[y] = max(y_top[y], a);
		}
	}
	int ans = 0;
	for (int x=0; x<n; x++) {
		for (int y=0; y<m; y++) {
			if (x_top[x] == y_top[y]) {
				ans++;
				x_top[x].ismx = y_top[y].ismx = true;
			}
		}
	}
	while (q--) {
		P a;
		cin >> a.x >> a.y >> a.a;
		a.x--, a.y--;
		P was_x_top = x_top[a.x];
		P was_y_top = y_top[a.y];
		x_top[a.x] = max(x_top[a.x], a);
		y_top[a.y] = max(y_top[a.y], a);
		if (was_x_top.ismx && was_x_top < x_top[a.x]) {
			ans--;
			x_top[a.x].ismx = y_top[was_x_top.y].ismx = false;
		}
		if (was_y_top.ismx && was_y_top < y_top[a.y]) {
			ans--;
			y_top[a.y].ismx = x_top[was_y_top.x].ismx = false;
		}
		if (x_top[a.x] == y_top[a.y]) {
			x_top[a.x].ismx = y_top[a.y].ismx = true;
			ans++;
		}
		if (was_x_top == was_y_top)
			ans++;
		cout << ans << '\n';
	}
	return 0;
}
