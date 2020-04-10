class Solution {
	static string to_string(const vector<int> &dc) {
		string ans;
		for (int i=9; i>0; i--)
			ans += string(dc[i], '0'+i);
		if (ans.size())
			ans += string(dc[0], '0');
		else if (dc[0])
			ans = "0";
		return ans;
	}
public:
	static string largestMultipleOfThree(const vector<int>& digits) {
		int sm = 0;
		vector<int> dc(10);
		for (int d:digits) {
			dc[d]++;
			sm += d;
		}
		int m = sm % 3;
		if (m == 0)
			return to_string(dc);
		// try removing 1 digit
		for (int i=1; i<10; i++) {
			if (dc[i] && (m == (i%3))) {
				dc[i]--;
				return to_string(dc);
			}
		}
		// try removing 2 digits
		for (int i=1; i<10; i++) {
			if (dc[i]) {
				dc[i]--;
				m = (sm-i) % 3;
				for (int j=1; j<10; j++) {
					if (dc[j] && (m == (j%3))) {
						dc[j]--;
						return to_string(dc);
					}
				}
				m = sm % 3;
				dc[i]++;
			}
		}
		return "";
	}
};

