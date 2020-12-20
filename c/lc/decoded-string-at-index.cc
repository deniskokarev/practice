class Solution {
	struct T {
		string s;
		int64_t before_len;
		int rep;
	};
public:
	static string decodeAtIndex(const string &s, int k) {
		k--;
		// "leet2code3" -> {{"leet", 0, 2}, {"code", 8, 3}}
		// "ha22" -> {{"ha", 0, 2}, {"", 4, 2}}
		vector<T> tokens;
		int64_t tot_len = 0;
		T tok;
		for (char c:s) {
			if (!isdigit(c)) {
				tok.s += c;
			} else {
				tok.before_len = tot_len;
				tot_len += tok.s.size();
				tok.rep = c-'0';
				tokens.push_back(tok);
				tot_len *= tok.rep;
				tok = {"", 0, 1};
			}
		}
		// cover no rep at the end
		if (tok.s.size()) {
			tok.before_len = tot_len;
			tok.rep = 1;
			tokens.push_back(tok);
		}
		// "leet leet code  leet leet code  leet leet code"
		//              12              24              36
		while (!tokens.empty()) {
			auto &t = tokens.back();
			k %= t.before_len + t.s.size();
			if (k < t.before_len) {
				tokens.pop_back();
				continue;
			} else {
				return string(1, t.s[k-t.before_len]);
			}
		}
		assert(false && "Hmm, must not come here");
	}
};

