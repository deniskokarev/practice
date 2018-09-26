#include <iostream>
#include <algorithm>
#include <queue>
/* ROI 2016A */
using namespace std;

struct WALL {
	int a, k;	// spec: a-enimies, k-strength
	bool operator<(const WALL &b) const {
		return min(a, k) < min(b.a, b.k); // we'll use max heap
	}
};

int main(int argc, char **argv) {
	int64_t toten = 0;	// total enimies
	int n, s;		// spec: n-number of walls, s-number of defenders
	cin >> n >> s;
	priority_queue<WALL> walls;	// best wall to start killing on
	while (n--) {
		WALL w;
		cin >> w.a >> w.k;
		walls.push(w);
		toten += w.a;
	}
	while (walls.top().a > 0 && s > 0) {
		auto w = walls.top();
		walls.pop();
		if (w.a > w.k) {
			// dispatch troops to kill all but (a % k) enimies
			int disp = min(s, w.a/w.k);
			w.a -= disp * w.k;
			toten -= disp * w.k;
			s -= disp;
		} else {
			// dispatch only 1 solder to finish last enimies on the wall
			toten -= w.a;
			w.a = 0;
			s -= 1;
		}
		walls.push(w);
	}
	cout << toten << endl;
	return 0;
}
