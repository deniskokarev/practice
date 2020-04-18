class Solution {
	static inline bool may_be_nested(const string &s, int i, int j) {
		return
			(s[i] == '(' && s[j] == ')') ||
			(s[i] == '*' && s[j] == ')') ||
			(s[i] == '(' && s[j] == '*');
	}
public:
	static bool checkValidString(const string &s) {
		int sz = s.size();
		if (sz == 0)
			return true;
		vector<vector<bool>> dp(sz+1, vector<bool>(sz+1, false)); // dp[from_pos][to_pos]
		for (int i=0; i<sz; i++) {
			dp[i+1][i] = true; // always true for empty string
			dp[i][i] = (s[i] == '*'); // true for string with one *
		}
		for (int l=1; l<sz; l++) { // length == l+1
			for (int i=0; i+l<sz; i++) { // from_pos
				const int j = i+l; // to_pos
				dp[i][j] = may_be_nested(s, i, j) && dp[i+1][j-1];
				for (int m=i; m<j; m++) // mid
					dp[i][j] = dp[i][j] || (dp[i][m] && dp[m+1][j]);
			}
		}
		return dp[0][sz-1];
	}
};
