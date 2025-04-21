// https://leetcode.com/problems/count-the-hidden-sequences
class Solution {
public:
	static int numberOfArrays(const vector<int> &differences, int lower, int upper) {
		int64_t mn = 0, mx = 0, n = 0;
		for (auto d: differences) {
			n += d;
			mn = min(mn, n);
			mx = max(mx, n);
		}
		int64_t d1 = upper - lower;
		int64_t d2 = mx - mn;
		return d1 >= d2 ? d1 - d2 + 1 : 0;
	}
};

