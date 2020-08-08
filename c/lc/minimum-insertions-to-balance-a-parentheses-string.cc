class Solution {
public:
	static int minInsertions(const string &s) {
		int lvl = 0;
		int ans = 0;
		for (char c:s) {
			if (c == '(') {
				if (lvl < 0) {
					ans += (-lvl+1)/2+(lvl&1);
					lvl = 0;
				} else if (lvl&1) {
					lvl--;
					ans++;
				}
				lvl += 2;
			} else {
				lvl--;
			}
		}
		if (lvl < 0) {
			ans += (-lvl+1)/2+(lvl&1);
		} else {
			ans += lvl;
		}
		return ans;
	}
};

