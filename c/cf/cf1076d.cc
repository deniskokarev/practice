#include <cstdio>
#include <queue>
#include <algorithm>
/* CodeForces CF1076D problem */
using namespace std;

struct E {
	int id;
	int f, t, w;
	bool sp; // on shortest path
	int score;
	E *nxt;
};

struct Q {
	int64_t sw;
	E *e;
	bool operator<(const Q &b) const {
		return sw > b.sw; // for max heap
	}
};

int dfs(E *ine, E **gg, int n) {
	ine->score = 1;
	for (E *e = gg[ine->t]; e; e=e->nxt)
		if (e->sp)
			ine->score += dfs(e, gg, n);
	return ine->score;
}

int main(int argc, char **argv) {
	int n, m, k;
	scanf("%d%d%d", &n, &m, &k);
	E ee[m*2];
	E *gg[n];
	fill(gg, gg+n, nullptr);
	for (int i=0; i<m; i++) {
		int f, t, w;
		scanf("%d%d%d", &f, &t, &w);
		f--, t--;
		ee[i*2] = E {i, f, t, w, false, 0, gg[f]};
		gg[f] = &ee[i*2];
		ee[i*2+1] = E {i, t, f, w, false, 0, gg[t]};
		gg[t] = &ee[i*2+1];
	}
	// dijkstra
	priority_queue<Q> qq;
	int vv[n];
	fill(vv, vv+n, 0);
	E fe {-1, -1, 0, -1, false, -1, nullptr};
	qq.push(Q {0, &fe});
	while (!qq.empty()) {
		Q top = qq.top();
		qq.pop();
		int v = top.e->t;
		if (!vv[v]) {
			vv[v] = 1;
			top.e->sp = true;
			for (E *e = gg[v]; e; e=e->nxt)
				qq.push(Q{top.sw+e->w, e});
		}
	}
	// calc importance of E
	E ans {-1, -1, 0, -1, false, 0, nullptr};
	dfs(&ans, gg, n);
	E ee_ans[m];
	for (int i=0; i<m; i++)
		ee_ans[i] = (ee[2*i].score > ee[2*i+1].score) ? ee[2*i] : ee[2*i+1];
	sort(ee_ans, ee_ans+m, [](const E &a, const E &b){return a.score>b.score;});
#if 0
	for (auto &e:ee_ans)
		fprintf(stderr, "%d %d->%d : %d (sp=%d)\n", e.id, e.f+1, e.t+1, e.w, e.sp);
#endif
	printf("%d\n", k);
	for (int i=0; i<k; i++)
		printf("%d ", ee_ans[i].id+1);
	printf("\n");
	return 0;
}
