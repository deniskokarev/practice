#include <iostream>
#include <vector>
/* https://leetcode.com/problems/longest-valid-parentheses/ */
using namespace std;

static int enableFastIO() {
        ios::sync_with_stdio(false);
        cin.tie(nullptr);
        return 0;
}

static const int fastIO = enableFastIO();

class Solution {
public:
	static int longestValidParentheses(const string &str) {
		int sum = str.size()+1;
		vector<int> best_pos(sum*2);
		int mx = 0;
		for (int i=1; i<=str.size(); i++) {
			if (str[i-1] == '(') {
				if (best_pos[sum] == 0)
					best_pos[sum] = i;
				sum--;
			} else {
				best_pos[sum] = 0;
				sum++;
				int l = best_pos[sum];
				if (l > 0)
					mx = max(mx, i-l+1);
			}
		}
		return mx;
	}
};

int main(int argc, char **argv) {
	cout << Solution::longestValidParentheses("(()") << " == 2"  << endl;
	cout << Solution::longestValidParentheses(")()())") << " == 4" << endl;
	cout << Solution::longestValidParentheses("") << " == 0" << endl;
	cout << Solution::longestValidParentheses("(") << " == 0" << endl;
	cout << Solution::longestValidParentheses(")") << " == 0" << endl;
	cout << Solution::longestValidParentheses(")(") << " == 0" << endl;
	cout << Solution::longestValidParentheses("(())()(()((") << " == 6" << endl;
	cout << Solution::longestValidParentheses("(()()") << " == 4" << endl;
	return 0;
}
