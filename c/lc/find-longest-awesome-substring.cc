ass Solution {
public:
	static int longestAwesome(const string &s) {
		constexpr int ALP = 10;
		constexpr int NONE = -2;
		vector<int> hist(1<<ALP, NONE);
		int k = 0;
		hist[k] = -1;
		int ans = 0;
		for (int i=0; i<s.size(); i++) {
			int c = s[i] % ALP;
			k = k ^ (1<<c);
			if (hist[k] != NONE)
				ans = max(ans, i-hist[k]);
			for (int p=0; p<ALP; p++) {
				int k_odd = k ^ (1<<p);
				if (hist[k_odd] != NONE)
					ans = max(ans, i-hist[k_odd]);
			}
			if (hist[k] == NONE)
				hist[k] = i;
		}
		return ans;
	}
};

