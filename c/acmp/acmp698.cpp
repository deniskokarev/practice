#include <iostream>
#include <cstring>
#include <cassert>
/* ACMP 698 */
using namespace std;

struct C {
	char s;
	int d;
	bool greater(const C &b, const char trump) const {
		if (s == trump && b.s != trump)
			return true;
		else if (s != trump && b.s == trump)
			return false;
		else if (s == b.s)
			return d > b.d;
		else
			return false;
	}
};

C parse_card(const string &s) {
	const char card[9] = {'6', '7', '8', '9', 'T', 'J', 'Q', 'K', 'A'};
	for (int i=0; i<9; i++)
		if (s[0] == card[i])
			return C {s[1], i};
	assert(false && "cannot parse card");
}

// edge and the graph matrix elements at the same time
// to speed-up sparse graphs traversal
struct E {
	int cost;
	int next;
};
  
// BFS Q element
struct Q {
	int to;
	int min_flow;
};
 
/**
 * BFS for shortest path from src to drn and identify the "thinnest" edge
 * on the way. Populate the path
 * @param[in] ff[sz][sz] - graph matrix with flow capacities
 * @param[in] sz - number of nodes
 * @param[in] src - source node
 * @param[in] dst - drain node
 * @param[out] path[sz] - trace path in parent-of fashion
 * @param[out] *min_flow - smallest edge on the path
 * @return - true when path was found - otherwise false
 */
static int bfs_shortest_path(const E *ff, int sz, int src, int drn, int *path, int *min_flow) {
	memset(path, 0xff, sz*sizeof(*path)); // fill(path, path+sz, -1)
	Q queue[sz];			// queue right on stack
	int qh = 0, qt = 0;		// head and tail of the queue
	Q q = {src, INT_MAX};
	queue[qt++] = q;
	path[src] = src;
	while (qh != qt && queue[qh].to != drn) {
		int idx_0 = queue[qh].to*sz;
		for (int v=ff[idx_0].next; v; v=ff[idx_0+v].next) {
			if (ff[idx_0+v].cost>0 && path[v]==-1) {
				q.to = v;
				q.min_flow = min(queue[qh].min_flow, ff[idx_0+v].cost);
				path[q.to] = queue[qh].to;
				queue[qt++] = q;
			}
		}
		qh++;
	}
	*min_flow = queue[qh].min_flow;
	return (qh != qt);
}
  
/**
 * find max flow from src into drn in the graph in O(V*V*FLOW)
 * @param[in,out] ff[sz][sz] - graph
 * @param[in] sz - graph size
 * @param[in] src - source node
 * @param[in] drn - drain node
 * @return maximum possible flow
 * ff[sz][sz] will reflect the said maximum flow subtracted
 */
int maxflow(E *ff, int sz, int src, int drn) {
	int path[sz];
	int df;
	int flow = 0;
	while (bfs_shortest_path(ff, sz, src, drn, path, &df)) {
		flow += df;
		for (int v=drn,vp=path[v]; v!=src; v=vp,vp=path[v]) {
			ff[vp*sz+v].cost -= df; // ff[vp][v] -= df;
			ff[v*sz+vp].cost += df; // ff[v][vp] += df;
		}
	}
	return flow;
}
 
// !!!NB: graph nodes must be 1-based
void add_edge(E *mm, int dim, int f, int t) {
	if (mm[f*dim+t].cost == 0) {
		mm[f*dim+t] = E {1, mm[f*dim].next};
		mm[f*dim].next = t;
		mm[t*dim+f] = E {0, mm[t*dim].next};
		mm[t*dim].next = f;
	}
}

int main(int argc, char **argv) {
	int n, m;
	string r;
	cin >> n >> m >> r;
	char trump = r[0];
	// using maxflow approach
	// !!!NB: graph nodes must be 1-based
	C cc[n+m+1];
	for (int i=1; i<=n; i++) {
		string s;
		cin >> s;
		cc[i] = parse_card(s);
	}
	for (int i=n+1; i<=n+m; i++) {
		string s;
		cin >> s;
		cc[i] = parse_card(s);
	}
	int dim = n+m+2+1;
	E mm[dim][dim];
	memset(mm, 0, sizeof(mm));
	for (int i=1; i<=n; i++)
		for (int j=n+1; j<=n+m; j++)
			if (cc[i].greater(cc[j], trump))
				add_edge((E*)mm, dim, i, j);
	int src = n+m+1;
	int drn = src+1;
	for (int i=1; i<=n; i++)
		add_edge((E*)mm, dim, src, i);
	for (int j=n+1; j<=n+m; j++)
		add_edge((E*)mm, dim, j, drn);
	int flow = maxflow((E*)mm, dim, src, drn);
	//cerr << "flow:" << flow << endl;
	bool ans = (flow == m);
	cout << (ans?"YES":"NO") << endl;
	return 0;
}
