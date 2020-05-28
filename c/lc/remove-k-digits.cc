#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <queue>
#include <list>
/* https://leetcode.com/problems/remove-k-digits/ */
using namespace std;

class Solution {
public:
	static string removeKdigits(const string &num, int k) {
		list<char> res(num.begin(), num.end());
		res.push_back('9'+1);
		auto it = res.begin();
		int sub = k;
		while (sub && it != prev(res.end())) {
			if (*it > *next(it)) {
				auto rm = it;
				if (it != res.begin())
					--it;
				else
					++it;
				--sub;
				res.erase(rm);
			} else {
				++it;
			}
		}
		string ans(res.begin(), res.end());
		ans = ans.substr(0, num.size()-k);
		int lz = 0;
		while (ans[lz] == '0')
			lz++;
		ans = ans.substr(lz);
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
