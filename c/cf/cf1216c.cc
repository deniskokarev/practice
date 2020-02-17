#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
/* CodeForces CF1216C problem */
using namespace std;

struct R {
	int x1, y1;
	int x2, y2;
	R overlap(const R &o) const {
		R res {max(x1, o.x1), max(y1, o.y1), min(x2, o.x2), min(y2, o.y2)};
		if (res.x2>res.x1 && res.y2>res.y1)
			return res;
		else
			return R {0, 0, 0, 0};
	}
	int64_t area() const {
		if (x2>x1 && y2>y1)
			return int64_t(x2-x1)*(y2-y1);
		else
			return 0;
	}
};

int main(int argc, char **argv) {
	R w;
	cin >> w.x1 >> w.y1 >> w.x2 >> w.y2;
	R b1;
	cin >> b1.x1 >> b1.y1 >> b1.x2 >> b1.y2;
	R b2;
	cin >> b2.x1 >> b2.y1 >> b2.x2 >> b2.y2;
	R wb1 = w.overlap(b1);
	R wb2 = w.overlap(b2);
	R wb1b2 = wb1.overlap(wb2);
	int64_t res = w.area() - wb1.area() - wb2.area() + wb1b2.area();
	cout << ((res>0)?"YES":"NO") << endl; 
	return 0;
}
