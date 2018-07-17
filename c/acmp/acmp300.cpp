#include <iostream>
#include <algorithm>
/* ACMP 300 */
using namespace std;

struct R {
	int angle;
	uint64_t t, v, atv;
};

int angle(R *rr, int i, int j) {
	return min((rr[i].angle+4-rr[j].angle)%4, (rr[j].angle+4-rr[i].angle)%4);
}

int main(int argc, char **argv) {
	R rr[4];
	uint64_t vvvv = 1;
	for (int i=0; i<4; i++) {
		auto &r = rr[i];
		cin >> r.t >> r.v;
		vvvv *= r.v;
		r.angle = i;
	}
	uint64_t t, d;
	cin >> t >> d;
	uint64_t dv = d * vvvv;
	for (auto &r:rr)
		r.atv = r.t * vvvv + dv/r.v;
	sort(rr, rr+4, [](const R &a, const R &b){return a.atv < b.atv;});
	for (int f=0,i=2; i<4; i++)
		if (rr[i-1].atv == rr[i].atv && angle(rr, f, i-1) > angle(rr, f, i))
			swap(rr[i-1], rr[i]);
		else
			f = i-1;
	int cnt = 1;
	uint64_t tv = t * vvvv;
	for (int i=1; i<4; i++)
		if (rr[i-1].atv + angle(rr, i-1, i)*tv <= rr[i].atv)
			cnt++;
		else
			break;
	//cerr << cnt << endl;
	if (cnt == 4)
		cout << "ALIVE" << endl;
	else
		cout << cnt++ << endl;
	return 0;
}
