#include <cstdio>
#include <algorithm>
/* ACMP 89 */
using namespace std;

struct T {
	char nm[128];
	int t;
	bool operator<(const T &b) const {
		return t < b.t;
	}
};

int main(int argc, char **argv) {
	const int d = 650;
	int n;
	scanf("%d ", &n);
	T tt[n];
	for (auto &t:tt) {
		int fh, fm, th, tm;
		scanf("%*[\"]%127[^\"]%*[\"] %d:%d %d:%d ", t.nm, &fh, &fm, &th, &tm);
		int start = fh*60+fm;
		int end = th*60+tm;
		t.t = (end+24*60-1 - start) % (24*60) + 1;
		//fprintf(stderr, "%s: %d\n", t.nm, t.t);
	}
	auto &t = *min_element(tt, tt+n);
	int sp = (d*60*2+t.t)/t.t/2;
	printf("The fastest train is \"%s\".\n"
		   "Its speed is %d km/h, approximately.\n", t.nm, sp);
	return 0;
}
