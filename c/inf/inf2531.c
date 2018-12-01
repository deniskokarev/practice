#include <cstdio>
#include <queue>
#include <algorithm>
/* ROI 2010C */
using namespace std;

struct S {
	int f, t, p, id, x;
};

struct S_FCMP {
	bool operator()(const S &a, const S &b) {
		return a.f < b.f;
	};
};

struct S_PCMP {
	bool operator()(const S *a, const S *b) {
		return (a->t > b->t) || (a->t == b->t && a->p < b->p);
	};
};

int main(int argc, char **argv) {
	int n, m, k;
	scanf("%d%d%d", &n, &m, &k);
	S ss[n];
	int pcnt = 0;
	for (int i=0; i<n; i++) {
		auto &s = ss[i];
		scanf("%d%d%d", &s.f, &s.t, &s.p);
		s.id = i;
		s.x = -1;
		pcnt += (s.p > 0); 
	}
	sort(ss, ss+n, S_FCMP());
	priority_queue<S*, vector<S*>, S_PCMP> qq;
	for (int x=1; x<=m; x++) {
		S key {x, 0, 0};
		int i = int(lower_bound(ss, ss+n, key, S_FCMP()) - ss);
		while (i<n && ss[i].f == x)
			qq.push(&ss[i++]);
		while (qq.top()->t < x)
			qq.pop();
		for (int l=0; l<k && !qq.empty(); l++) {
			S *e = qq.top();
			e->x = x-1;
			qq.pop();
		}
	}
	int vans[n];
	int ans = 0;
	fill(vans, vans+n, 0);
	for (int i=0; i<n; i++) {
		vans[ss[i].id] = ss[i].x+1;
		if (ss[i].x >= 0) {
			pcnt -= (ss[i].p > 0);
			ans++;
		}
	}
	if (pcnt > 0) {
		printf("0\n");
	} else {
		printf("%d\n", ans);
		for (int i=0; i<n; i++)
			printf("%d ", vans[i]);
		printf("\n");
	}
	return 0;
}
