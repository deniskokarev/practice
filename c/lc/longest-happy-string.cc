class Solution {
	struct L {
		char ch;
		int n;
		bool operator<(const L &o) const {
			return n<o.n;
		}
	};
public:
	static string longestDiverseString(int a, int b, int c) {
		L l[3] {{'a', a}, {'b', b}, {'c', c}};
		sort(l, l+3);
		int n[3] {l[0].n, l[1].n, l[2].n};
		char ch[3] {l[0].ch, l[1].ch, l[2].ch};
		list<char> res1;
		while (n[0]--) {
			res1.push_back(ch[0]);
			res1.push_back(ch[1]);
			res1.push_back(ch[2]);
			n[1]--, n[2]--;
		}
		list<char> res2;
		while (n[1]--) {
			res2.push_back(ch[1]);
			res2.push_back(ch[2]);
			n[2]--;
		}
		if (res1.size()) {
			for (auto it=res1.begin(); it != res1.end(); ++it) {
				int j;
				if (*it == ch[1])
					j = 2;
				else if (*it == ch[2])
					j = 1;
				else
					j = 0;
				while (n[2] && j) {
					res1.insert(it, ch[2]);
					n[2]--;
					j--;
				}
			}
		}
		int j = 2;
		while (n[2] && j) {
			res1.insert(res1.begin(), ch[2]);
			n[2]--;
			j--;
		}
		for (auto it=res2.begin(); it != res2.end(); ++it) {
			if (*it == ch[1] && n[2]) {
				++it;
				res2.insert(it, ch[2]);
				n[2]--;
			}
		}
		return string(res1.begin(), res1.end()) + string(res2.begin(), res2.end());
	}
};

