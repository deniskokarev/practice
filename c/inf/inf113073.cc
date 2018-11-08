#include <cstdio>
#include <algorithm>
/* INF 113073 */

struct S {
	int b, e;
	bool operator<(const S &b) const {
		return e<b.e;
	}
};

int main(int argc, char **argv) {
	int n;
	scanf("%d", &n);
	constexpr int MXTM = 1440;
	S ss[n];
	for (auto &s:ss)
		scanf("%d%d", &s.b, &s.e);
	std::sort(ss, ss+n);
	int solution[MXTM+1];
	solution[0] = 0;
	int h = 0;
	for (int t=1; t<=MXTM; t++) {
		solution[t] = solution[t-1];
		while (h<n && ss[h].e == t) {
			solution[t] = std::max(solution[t], solution[ss[h].b]+1);
			h++;
		}
	}
	printf("%d\n", solution[MXTM]);
	return 0;
}
