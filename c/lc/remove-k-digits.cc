#include <iostream>
#include <stack>
/* https://leetcode.com/problems/remove-k-digits/ */
using namespace std;

class Solution {
public:
	static string removeKdigits(const string &num, int k) {
		stack<char> stack;
		int sub = k;
		for (auto it=num.begin(); it != num.end(); ++it) {
			while (sub && stack.size() && stack.top() > *it) {
				--sub;
				stack.pop();
			}
			stack.push(*it);
		}
		string ans(stack.size(), ' ');
		for (int i=ans.size()-1; i>=0; i--,stack.pop())
			ans[i] = stack.top();
		int lz = 0;
		while (ans[lz] == '0')
			lz++;
		ans = ans.substr(lz, num.size()-k-lz);
		if (!ans.size())
			ans = "0";
		return ans;
	}
};

int main(int argc, char **argv) {
	cout << '"' << Solution::removeKdigits("1432219", 3) << '"' << endl;
	cout << '"' << Solution::removeKdigits("10200", 1) << '"' << endl;
	cout << '"' << Solution::removeKdigits("10", 2) << '"' << endl;
	cout << '"' << Solution::removeKdigits("1234567890", 9) << '"' << endl;
	return 0;
}

