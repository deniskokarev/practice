/* ACMP 532 */
#include <set>
#include <vector>
#include <algorithm>
#include <cassert>
#include <stdio.h>

using namespace std;

enum {
	DIR_NONE = -1,
	DIR_IN = 0,
	DIR_OUT
};

enum {
	P_NOT_IN = -1,
	P_SIT = 0,
	P_STAND,
	P_ALWAYS_STAND 
};

struct P {
	int p, stop, dir;
	int ai, bi;
	int on;
	int s; // sit/stand
	int d;
	bool operator<(const P &b) const {
		return d < b.d || (d == b.d && p < b.p);
	}
	bool operator>(const P &b) const {
		return d > b.d || (d == b.d && p > b.p);
	}
};

int main(int argc, char **argv) {
	int n, m, p;
	scanf("%d%d%d", &n, &m, &p);
	P pp[2*n];
	for (int i=0; i<n; i++) {
		int ci, di;
		int j = i*2;
		scanf("%d%d%d%d", &pp[j].ai, &pp[j].bi, &ci, &di);
		pp[j].p = i;
		pp[j].d = pp[j].ai-pp[j].bi;
		pp[j].stop = ci;
		pp[j].dir = DIR_IN;
		pp[j].on = -1;
		pp[j+1] = pp[j];
		pp[j+1].stop = di;
		pp[j+1].dir = DIR_OUT;
	}
	sort(pp, pp+2*n, [](const P &a, const P &b){return a.stop<b.stop||(a.stop==b.stop&&a.dir<b.dir);});
	set<P, less<P>> sit;
	set<P, greater<P>> stand;
	P tram[n]; // use p and ai of the person inside
	fill(tram, tram+n, P{-1,-1,DIR_NONE,-1,-1,-1,P_NOT_IN});
	int64_t h = 0;
	for (auto &p:pp) {
		if (p.dir == DIR_IN) {
			assert(tram[p.p].s == P_NOT_IN && "passenger is already on board");
			p.on = p.stop;
			if (p.d>0) {
				if (sit.size() < m) {
					p.s = P_SIT;
					sit.insert(p);
				} else if (p > *(sit.begin())) {
					auto top = *sit.begin();
					h += top.ai*(p.stop-top.on);
					top.on = p.stop;
					top.s = P_STAND;
					stand.insert(top);
					sit.erase(sit.begin());
					tram[top.p] = top;
					p.s = P_SIT;
					sit.insert(p);
				} else {
					p.s = P_STAND;
					stand.insert(p);
				}
			} else {
				p.s = P_ALWAYS_STAND;
			}
			tram[p.p] = p;
		} else {
			// OUT
			if (tram[p.p].s == P_ALWAYS_STAND) {
				h += tram[p.p].bi * (p.stop - tram[p.p].on);
			} else if (tram[p.p].s == P_STAND) {
				h += tram[p.p].bi * (p.stop - tram[p.p].on);
				stand.erase(tram[p.p]);
			} else if (tram[p.p].s == P_SIT) {
				h += tram[p.p].ai * (p.stop - tram[p.p].on);
				sit.erase(tram[p.p]);
				if (stand.size() > 0) {
					auto top = *stand.begin();
					h += top.bi * (p.stop - top.on);
					stand.erase(stand.begin());
					top.on = p.stop;
					top.s = P_SIT;
					sit.insert(top);
					tram[top.p] = top;
				}
			} else {
				assert(false && "passenger is not on board");
			}
			tram[p.p].s = P_NOT_IN;
		}
	}
	printf("%lld\n", h);
	return 0;
}
