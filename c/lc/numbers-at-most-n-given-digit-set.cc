class Solution {
public:
	static int place(bitset<10> set, int len) {
		int p = 1;
		int cnt = set.count();
		while (len--)
			p *= cnt;
		return p;
	}
	static int place_le(bitset<10> digs, const string &ns, int len) {
		if (len > 0) {
			int ans = 0;
			int sz = ns.size();
			int p = sz - len;
			int d;
			for (d=0; d<ns[p]; d++)
				if (digs[d])
					ans += place(digs, len-1);
			if (digs[d])
				ans += place_le(digs, ns, len-1);
			return ans;
		} else {
			return 1;
		}
	}
	static int solve(bitset<10> digs, const string &ns, int len) {
		int ans = place_le(digs, ns, len);
		for (int l=len-1; l>0; l--)
			ans += place(digs, l);
		return ans;
	}
public:
	static int atMostNGivenDigitSet(vector<string>& digits, int n) {
		bitset<10> digs;
		for (auto d:digits)
			digs[d[0]-'0'] = 1;
		string ns = to_string(n);
		for (char &c:ns)
			c -= '0';
		return solve(digs, ns, ns.size());
	}
};

