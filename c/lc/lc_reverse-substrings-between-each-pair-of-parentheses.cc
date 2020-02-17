#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
/* https://leetcode.com/contest/weekly-contest-154/problems/reverse-substrings-between-each-pair-of-parentheses/ */
using namespace std;

class Solution {
public:
	static string reverseParentheses(const string &s) {
		vector<string> stack {""};
		int sp = 1;
		for (char c:s) {
			if (c == '(') {
				stack.resize(sp+1);
				stack[sp] = "";
				sp++;
			} else if (c == ')') {
				reverse(stack[sp-1].begin(), stack[sp-1].end());
				sp--;
				stack[sp-1] += stack[sp];
			} else {
				stack[sp-1].push_back(c);
			}
		}
		if (sp > 1) {
			sp--;
			stack[sp-1] += stack[sp];
		}
		return stack[0];
	}
};

int main(int argc, char **argv) {
	cout << Solution::reverseParentheses("a(bc)d") << endl;
	cout << Solution::reverseParentheses("(abcd)") << endl;
	cout << Solution::reverseParentheses("(u(love)i)") << endl;
	cout << Solution::reverseParentheses("(ed(et(oc))el)") << endl;
	cout << Solution::reverseParentheses("a(bcdefghijkl(mno)p)q") << endl;
	return 0;
}
