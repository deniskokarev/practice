// https://leetcode.com/problems/count-days-without-meetings
// supporting non-overlapping intervals in real-time
class Solution {
	struct Iv {
		int b, e;
		bool operator<(const Iv &rhs) const { return b < rhs.b; }
	};

public:
	static int countDays(int days, const vector<vector<int>> &meetings) {
		set<Iv> s;
		s.insert({.b = -1, .e = -1});
		for (const auto &m: meetings) {
			Iv v{.b = m[0], .e = m[1]};
			auto curr = s.lower_bound(v);
			while (curr != s.end()) {
				if (curr->b <= v.e) {
					v.e = std::max(v.e, curr->e);
					curr = s.erase(curr);
				} else { break; }
			}
			curr = s.lower_bound(v);
			--curr;
			if (curr->e >= v.b) {
				v.b = curr->b;
				v.e = std::max(v.e, curr->e);
				s.erase(curr);
			}
			s.insert(v);
		}
		int busy = 0;
		for (const auto &v: s) {
			// cerr << v.b << ' ' << v.e << endl;
			busy += (v.e - v.b) + 1;
		}
		return days - busy + 1;
	}
};

