#include <cstdio>
#include <cstring>
#include <climits>
#include <algorithm>
#include <array>
/* CodeForces CF1065D problem */
using namespace std;

struct P {
	int x, y;
};

typedef bool (*MAY_MOVE)(const P &p1, const P &p2);

const P kmoves[8] = {{2, 1}, {1, 2}, {-1, 2}, {-2, 1}, {-2, -1}, {-1, -2}, {1, -2}, {2, -1}}; 

static bool may_knight1(const P &p1, const P &p2) {
	for (auto &m:kmoves)
		if (p1.x+m.x == p2.x && p1.y+m.y == p2.y)
			return true;
	return false;
}

static bool may_knight2(const P &p1, const P &p2) {
	return false;
	for (auto &m1:kmoves)
		for (auto &m2:kmoves)
			if (p1.x+m1.x+m2.x == p2.x && p1.y+m1.y+m2.y == p2.y)
				return true;
	return false;
}

static bool may_bishop1(const P &p1, const P &p2) {
	return (p1.x+p1.y == p2.x+p2.y) || (p1.x-p2.x == p1.y-p2.y); // same diag
}

static bool may_bishop2(const P &p1, const P &p2) {
	return (p1.x ^ p1.y ^ p2.x ^ p2.y ^ 1) & 1; // same color
}

static bool may_rook1(const P &p1, const P &p2) {
	return (p1.x == p2.x) || (p1.y == p2.y); 
}

static bool may_rook2(const P &p1, const P &p2) {
	return true;
}

enum {
	P_N, P_B, P_R, P_SZ
};

static const MAY_MOVE fmay_move[P_SZ][2] = {
	{may_knight1, may_knight2},
	{may_bishop1, may_bishop2},
	{may_rook1, may_rook2}
};

constexpr int INF = INT_MAX/2;

int main(int argc, char **argv) {
	int n;
	scanf("%d", &n);
	P ll[n*n];
	for (int i=0; i<n; i++) {
		for (int j=0; j<n; j++) {
			int v;
			scanf("%d", &v);
			ll[v-1] = P {j, i};
		}
	}
	array<array<pair<int, int>, P_SZ>, P_SZ> opt;
	for (int i=1; i<n*n; i++) {
		array<array<pair<int, int>, P_SZ>, P_SZ> nopt {{
			{{{INF, 0}, {INF, 0}, {INF, 0}}},
			{{{INF, 0}, {INF, 0}, {INF, 0}}},
			{{{INF, 0}, {INF, 0}, {INF, 0}}}
		}};
		for (int m=0; m<2; m++)
			for (int pf=0; pf<P_SZ; pf++)
				for (int pt=0; pt<P_SZ; pt++)
					for (int pi=0; pi<P_SZ; pi++)
						if (fmay_move[pi][m](ll[i-1], ll[i]))
							nopt[pf][pi] = min(nopt[pf][pi], make_pair(opt[pf][pt].first+m+1+(pt!=pi), opt[pf][pt].second + (pt!=pi)));
		opt = nopt;
	}
	pair<int,int> ans = {INF, INF};
	for (int pf=0; pf<P_SZ; pf++)
		for (int pt=0; pt<P_SZ; pt++)
			ans = min(ans, opt[pf][pt]);
	printf("%d %d\n", ans.first, ans.second);
	return 0;
}
