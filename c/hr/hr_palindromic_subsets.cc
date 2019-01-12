#include <cstdio>
#include <vector>
#include <algorithm>
#include <cmath>
/* Hakerrank https://www.hackerrank.com/challenges/palindromic-subsets */

using namespace std;

constexpr int MOD = 1e9+7;

struct N {
	static constexpr int L = 26;
	int ofs;
	int ch[L];
	N():ofs(0) {
		std::fill(ch, ch+L, 0);
	}
	N(const unsigned char c):N() {
		ch[c%N::L]++;
	}
	int &operator[](int p) {
		return ch[(p + ofs) % N::L];
	}
	void operator+=(int o) {
		ofs = (ofs + N::L - o % N::L) % N::L;
	}
	void operator+=(N &b) {
		for (int i=0; i<N::L; i++)
			operator[](i) += b[i];
	}
};

void rebuild(vector<N> &tree, int sz) {
	for (int i=sz+sz-1; i>1; i-=2) {
		tree[i>>1] = N();
		tree[i>>1] += tree[i-1];
		tree[i>>1] += tree[i];
	}
}

static void rebuild_pos(vector<N> &tree, vector<int> &shift, int sz, int p) {
	while (p > 1) {
		p >>= 1;
		tree[p] = N();
		tree[p] += tree[p<<1];
		tree[p] += tree[p<<1|1];
		tree[p] += shift[p];
	}
}

void shift_range(vector<N> &tree, vector<int> &shift, int sz, int b, int e, int v) {
	b += sz;
	e += sz;
	int rb = b;
	int re = e;
	while (b < e) {
		if (b&1) {
			tree[b] += v;
			shift[b] += v;
			b++;
		}
		if (e&1) {
			--e;
			tree[e] += v;
			shift[e] += v;
		}
		b >>= 1;
		e >>= 1;
	}
	rebuild_pos(tree, shift, sz, rb);
	rebuild_pos(tree, shift, sz, re-1);
}

static void propagate_shift(vector<N> &tree, vector<int> &shift, int sz, int l2, int pos) {
	pos += sz;
	for (int l=l2; l>0; l--) {
		int p = pos >> l;
		int c1 = p << 1;
		int c2 = c1 | 1;
		shift[c1] += shift[p];
		shift[c2] += shift[p];
		tree[c1] += shift[p];
		tree[c2] += shift[p];
		shift[p] = 0;
	}
}

N fold(vector<N> &tree, vector<int> &shift, int sz, int l2, int b, int e) {
	propagate_shift(tree, shift, sz, l2, b);
	propagate_shift(tree, shift, sz, l2, e-1);
	b += sz;
	e += sz;
	N v;
	while (b < e) {
		if (b&1)
			v += tree[b++];
		if (e&1)
			v += tree[--e];
		b >>= 1;
		e >>= 1;
	}
	return v;
}

int ans(const N &res, int *p2m) {
	// two possibilities:
	// 1) one odd others even
	// 2) choosing i-th to be even greater or equal 2
	//    whereas i+1,i+2,... are even too
	pair<int,int64_t> p2[N::L+1];
	int sz = 0;
	for (auto p:res.ch)
		if (p)
			p2[sz++] = make_pair(p, p2m[p-1]);
	p2[sz++] = make_pair(0, 1);
	for (int i=sz-2; i>=0; i--) {
		p2[i].second *= p2[i+1].second;
		p2[i].second %= MOD;
	}
	int64_t ans = p2[0].second*(sz-1); // (1)
	for (int i=0; i<sz-1; i++) { // (2)
		ans += p2[i+1].second * (p2m[p2[i].first-1]-1);
		ans %= MOD;
	}
	return int(ans);
}

int main(int argc, char **argv) {
	int n, q;
	scanf("%d%d", &n, &q);
	std::vector<N> tree(n+n+1); // segment tree
	std::vector<int> shift(n+n+1); // segment tree
	int l2 = int(floor(log2(n))); // tree height
	int i = n;
	int c;
	fgetc(stdin);
	while ((c=fgetc(stdin)) != '\n' && c != EOF && i<n+n)
		tree[i++] = N(c);
	rebuild(tree, n);
	int p2m[n+1];
	p2m[0] = 1;
	for (int i=1; i<=n; i++)
		p2m[i] = p2m[i-1]*2 % MOD;
	while (q--) {
		int qt;
		int l, r, t; 
		scanf("%d", &qt);
		N res;
		switch (qt) {
		case 1:
			scanf("%d%d%d", &l, &r, &t);
			t %= N::L;
			shift_range(tree, shift, n, l, r+1, t);
			break;
		case 2:
			scanf("%d%d", &l, &r);
			res = fold(tree, shift, n, l2, l, r+1);
			printf("%d\n", ans(res, p2m));
			break;
		}
	}
	return 0;
}
