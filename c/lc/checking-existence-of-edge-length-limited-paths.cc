/**
 * https://leetcode.com/problems/checking-existence-of-edge-length-limited-paths/
 * Hmm, gives TL
 * Works in O(|E| * log(|E|) + |Q| * log(|V|))
 */

/*
 * Compute upper bound of logarithm for an integer argument
 * Example:
 *    int l = ilog<2>(n);
 * which computes
 *	  int l = (n==0) ? 0 : int(ceil(log2(n)))
 * The log<N>() code is taking advantage of C++11 template engine, which unrolls
 * the statement into the binary decision ?: operator at compile time.
 * This way ilog<2>(i) is about x10 faster than int(ceil(log2(i)))
 * and x3 faster than doing similar binary search in a loop.
 * The template implementation is enven sligthly faster that its "C" counterpart
 * log2_u32(i) function (see genilog.sh)
 * The logarithm base is a constexpr integer
 */

#include <type_traits>

namespace __ilog {

	template<typename N, N b, int p> struct ipow {
		static constexpr N value = N(ipow<N,b,p-1>::value*b);
	};

	template<typename N, N b> struct ipow<N,b,0> {
		static constexpr N value = 1;
	};

	template<typename UI, int base, int f, int t> struct _ilog {
		static int eval(UI n) {
			constexpr int m = (f+t)/2;
			return (n <= ipow<UI,base,m>::value) ? _ilog<UI,base,f,m>::eval(n) : _ilog<UI,base,m+1,t>::eval(n);
		}
	};

	template<typename UI, int base, int f> struct _ilog<UI,base,f,f> {
		static int eval(UI n) {
			return f;
		}
	};

	template<int p> struct val {
		static constexpr int value = p;
	};
		
	template<typename UI, int b, int p, unsigned long long mx> struct _ipowmax {
		static constexpr int value = std::conditional<(UI(mx) < UI(mx*b)), _ipowmax<UI, b, p+1, mx*b>, val<p>>::type::value; 
	};

	template<typename UI, int b> struct ipowmax {
		static constexpr int value = _ipowmax<UI, b, 0, 1>::value;
	};
	
	template<typename UI, int b> struct ilog {
		static int eval(UI n) {
			return _ilog<UI,b,0,ipowmax<UI,b>::value+1>::eval(n);
		}
	};

};

template<int base> int ilog(int n) { return __ilog::ilog<int, base>::eval(n); }

using namespace std;

struct E {
	int from, to;
	int score;
	int id;
	int mx;
	bool operator<(const E &o) const {
		return score > o.score;
	}
};

class Solution {
	static vector<vector<int>> bld_min_spanning_tree(const vector<vector<int>> &gg, const vector<E> &ee) {
		vector<vector<int>> rg(gg.size());
		vector<bool> seen(gg.size());
		int nseen = gg.size();
		priority_queue<E> pq;
		seen[0] = true;
		nseen--;
		for (auto ce_id:gg[0])
			pq.push(ee[ce_id]);
		while (!pq.empty()) {
			E e = pq.top();
			int root = e.to;
			pq.pop();
			if (!seen[root]) {
				seen[root] = true;
				rg[e.from].push_back(e.id);
				nseen--;
				if (!nseen)
					break;
				for (auto &ce_id:gg[root])
					pq.push(ee[ce_id]);
			}
		}
		return rg;
	}
	// populate par_e[node] -> [parent_edge_up(-1), parent_edge_up(-2), parent_edge_up(-4), -8, ...
	// populate mx_score_e[edge] -> mx score from edge edge below
	// @return mx_score
	static void prep_r(vector<array<int,20>> &par_e, vector<array<int,20>> &mx_score_e, const vector<vector<int>> tree, const vector<E> &ee, int e_id, vector<int> &up_e, vector<int> &dep, int lvl) {
		int root = ee[e_id].to;
		dep[root] = lvl;
		up_e.push_back(e_id);
		mx_score_e[root][0] = ee[e_id].score;
		par_e[root][0] = up_e.back();
		for (unsigned l=1,p2=2; p2<=up_e.size(); p2*=2,l++) {
			par_e[root][l] = up_e[up_e.size()-p2];
			mx_score_e[root][l] = max(mx_score_e[root][l-1],mx_score_e[ee[par_e[root][l-1]].from][l-1]); 
		}
		for (int ce_id:tree[root])
			prep_r(par_e, mx_score_e, tree, ee, ce_id, up_e, dep, lvl+1);
		up_e.pop_back();
	}
	struct PR {
		vector<array<int,20>> par_e;
		vector<array<int,20>> mx_score_e;
		vector<int> dep;
	};
	static PR prep(const vector<vector<int>> tree, const vector<E> &ee) {
		PR res { vector<array<int,20>>(tree.size(), {{0}}), vector<array<int,20>>(ee.size(), {{0}}), vector<int>(tree.size())};
		vector<int> up_e;
		prep_r(res.par_e, res.mx_score_e, tree, ee, 0, up_e, res.dep, 0);
		return res;
	}
	static int do_query(const PR &pr, const vector<E> &ee, int i, int j) {
		//cerr << "i=" << i << " j=" << j << " mx=";
		int dep_i = pr.dep[i];
		int dep_j = pr.dep[j];
		if (dep_i > dep_j) {
			swap(i, j);
			swap(dep_i, dep_j);
		}
		int d = dep_j - dep_i;
		int mx = INT_MIN;
		while (d > 0) {
			int jmp;
			int l = ilog<2>(d);
			for (jmp=1<<l; jmp>d; jmp>>=1,l--);
			int up_e = pr.par_e[j][l];
			mx = max(mx, pr.mx_score_e[j][l]);
			j = ee[up_e].from;
			d -= jmp;
		}
		d = dep_i;
		while (i != j) {
			int jmp;
			int l = ilog<2>(d);
			for (jmp=1<<l; jmp>d || pr.par_e[i][l] == pr.par_e[j][l]; jmp>>=1,l--);
			int up_e_i = pr.par_e[i][l];
			int up_e_j = pr.par_e[j][l];
			mx = max(mx, max(pr.mx_score_e[i][l], pr.mx_score_e[j][l]));
			i = ee[up_e_i].from;
			j = ee[up_e_j].from;
			d -= jmp;
		}
		//cerr << mx << endl;
		return mx;
	}
public:
	static vector<bool> distanceLimitedPathsExist(int n, const vector<vector<int>>& edgeList, const vector<vector<int>>& queries) {
		vector<vector<int>> gg(n);
		vector<E> ee;
		ee.push_back(E {-1, 0, 0, 0, INT_MIN});
		for (auto &e:edgeList) {
			int eid = ee.size();
			ee.push_back({e[0], e[1], e[2], eid, INT_MIN});
			gg[e[0]].push_back(eid);
			eid = ee.size();
			ee.push_back({e[1], e[0], e[2], eid, INT_MIN});
			gg[e[1]].push_back(eid);
		}
		// make sure it's fully connected graph, even though with very costly edges
		for (int i=1; i<n; i++) {
			int eid = ee.size();
			ee.push_back({0, i, int(1e9+1), eid, INT_MIN});
			gg[0].push_back(eid);
		}
		auto tree = bld_min_spanning_tree(gg, ee);
		auto pr = prep(tree, ee);
		int qsz = queries.size();
		vector<bool> res(qsz);
		for (int i=0; i<qsz; i++)
			res[i] = (do_query(pr, ee, queries[i][0], queries[i][1]) < queries[i][2]);
		return res;
	}
};

