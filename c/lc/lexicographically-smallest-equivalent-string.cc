// https://leetcode.com/problems/lexicographically-smallest-equivalent-string
class Solution {
	struct JSet {
		static constexpr int SZ = 'z' - 'a' + 1;
		int pp[SZ];
		JSet() {
			for (int i = 0; i < SZ; i++)
				pp[i] = i;
		}
		// associate a and b in min lex order
		void join(int a, int b) {
			int pa = parent(a);
			int pb = parent(b);
			if (pa > pb)
				swap(pa, pb);
			pp[pb] = pa;
		}

		int parent(int n) {
			return (pp[n] == n) ? n : (pp[n] = parent(pp[n]));
		}
	};

public:
	static string smallestEquivalentString(const string &s1, const string &s2, const string &base) {
		JSet js;
		for (int i = 0; i < s1.size(); i++)
			js.join(s1[i] - 'a', s2[i] - 'a');
		string ans(base);
		for (auto &ch: ans) {
			int c = ch - 'a';
			ch = 'a' + js.parent(c);
		}
		return ans;
	}
};

