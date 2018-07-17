#include <iostream>
#include <algorithm>
/* ACMP 300 */
using namespace std;

struct R {
	int angle;
	uint64_t t, v, atv;
};

int main(int argc, char **argv) {
	R rr[4];
	uint64_t vvvv = 1;
	for (int i=0; i<4; i++) {
		auto &r = rr[i];
		cin >> r.t >> r.v;
		if (r.v > 0)
			vvvv *= r.v;
		r.angle = i;
	}
	uint64_t t, d;
	cin >> t >> d;
	uint64_t dv = d * vvvv;
	for (auto &r:rr)
		if (r.v > 0)
			r.atv = r.t * vvvv + dv/r.v;
		else
			r.atv = ULLONG_MAX;
	sort(rr, rr+4, [](const R &a, const R &b){return a.atv < b.atv;});
	int cnt = 1;
	int killed = (rr[0].atv != ULLONG_MAX);
	uint64_t tv = t * vvvv;
	for (int i=1; i<4; i++) {
		int a = min((rr[i].angle+4-rr[i-1].angle)%4, (rr[i-1].angle+4-rr[i].angle)%4);
		if (rr[i].atv == ULLONG_MAX) {
			cnt++;
		} else if (rr[i].atv == ULLONG_MAX || rr[i-1].atv + a*tv <= rr[i].atv) {
			cnt++;
			killed++;
		} else {
			break;
		}
	}
	//cerr << cnt << endl;
	if (cnt == 4)
		cout << "ALIVE" << endl;
	else
		cout << killed << endl;
	return 0;
}
