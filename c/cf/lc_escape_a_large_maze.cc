#include <iostream>
#include <vector>
#include <unordered_set>
#include <algorithm>
/* https://leetcode.com/problems/escape-a-large-maze/ */
using namespace std;

namespace std {
	template <> struct hash<std::pair<int, int>> {
		inline size_t operator()(const std::pair<int, int> &p) const {
			return p.first*1e6+p.second;
		}
	};
}

static const pair<int,int> moves[4] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

static int dfs(const unordered_set<pair<int,int>> &bl, unordered_set<pair<int,int>> &seen, const pair<int,int> &s, const pair<int,int> &t, int depth) {
	if (s == t || depth > 4000) {
		return depth;
	} else {
		pair<int,int> best_mv[4];
		int bmi = 0;
		for (int i=0; i<4; i++) {
			auto &m = moves[i];
			pair<int,int> ns = make_pair(s.first+m.first, s.second+m.second);
			if (ns.first >= 0 && ns.first <= 1e6 && ns.second >= 0 && ns.second <= 1e6 && bl.find(ns) == bl.end() && seen.find(ns) == seen.end())
				best_mv[bmi++] = make_pair(abs(t.first-ns.first)+abs(t.second-ns.second), i);
		}
		sort(best_mv, best_mv+bmi);
		for (int i=0; i<bmi; i++) {
			auto &m = moves[best_mv[i].second];
			auto ns = make_pair(s.first+m.first, s.second+m.second);
			seen.insert(ns);
			int r = dfs(bl, seen, ns, t, depth+1);
			if (r > 0)
				return r;
		}
		return -1;
	}
}

class Solution {
public:
    static const bool isEscapePossible(const vector<vector<int>> &blocked, const vector<int> &source, const vector<int> &target) {
        unordered_set<pair<int,int>> bl(2000);
		for (auto &b:blocked)
			bl.insert(make_pair(b[0], b[1]));
		const pair<int,int> s {source[0], source[1]};
		const pair<int,int> t {target[0], target[1]};
		int ds, dt;
		{
			unordered_set<pair<int,int>> seen(10000000);
			seen.insert(s);
			ds = dfs(bl, seen, s, t, 0);
		}
		{
			unordered_set<pair<int,int>> seen(10000000);
			seen.insert(t);
			dt = dfs(bl, seen, t, s, 0);
		}
		cerr << "ds=" << ds << " dt=" << dt << endl;
		return ds >= 0 && dt >= 0;
    }
};

int main(int argc, char **argv) {
	cout << Solution::isEscapePossible({{0,1},{1,0}}, {0,0}, {0,2}) << '\n';
	cout << Solution::isEscapePossible({}, {0,0}, {999999,999999}) << '\n';
	return 0;
}
