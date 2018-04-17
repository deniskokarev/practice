#include <iostream>
#include <algorithm>
#include <set>
/* ACMP 1392 */
using namespace std;

struct E {
	int to;
	E *next;
};

enum {
	T_W = 0,
	T_C,
};

struct N {
	int id;
	int type;
	int ecnt;
	E *ee;
	bool sel;
	bool operator<(const N &b) const {
		return ecnt < b.ecnt || (ecnt == b.ecnt && id < b.id);
	}
	bool operator==(const N &b) const {
		return id == b.id;
	}
};

int main(int argc, char **argv) {
	int n, k;
	cin >> n >> k;
	E eeall[n*k*2], *e = eeall;
	N nn[n*2];
	fill(nn, nn+n, N {0, T_W, 0, nullptr, false});
	fill(nn+2, nn+2*n, N {0, T_C, 0, nullptr, false});
	for (int i=0; i<n*k; i++) {
		int f, t;
		cin >> f >> t;
		f--, t--;
		nn[f].id = f;
		nn[f].type = T_W;
		nn[f].ecnt++;
		e->to = t+n;
		e->next = nn[f].ee;
		nn[f].ee = e++;
		nn[t+n].id = t+n;
		nn[t+n].type = T_C;
		nn[t+n].ecnt++;
		e->to = f;
		e->next = nn[t+n].ee;
		nn[t+n].ee = e++;
	}
	// greedy solution
	set<N> q;
	for (auto &n:nn)
		q.insert(n);
	while (!q.empty()) {
		N top = *q.begin();
		E *mnto = top.ee;
		for (E *e=top.ee; e; e=e->next)
			if (nn[e->to].ecnt < nn[mnto->to].ecnt)
				mnto = e;
		if (top.type == T_W)
			cout << top.id+1 << " " << nn[mnto->to].id-n+1 << endl;
		else
			cout << nn[mnto->to].id-n+1 << " " << top.id+1 << endl;
		q.erase(top);
		q.erase(nn[mnto->to]);
	}
	return 0;
}
