#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
/* https://leetcode.com/problems/camelcase-matching/ */
using namespace std;

class Solution {
	static bool is_subseq(const string &src, const string &pattern) {
		vector<vector<int>> dp(2, vector<int>(src.size()+2));
		for (int i=0,l=0,nl=1; i<pattern.size(); i++,l^=1,nl^=1) {
			for (int j=1; j<=src.size(); j++) {
				dp[nl][j] = max(dp[l][j], dp[nl][j-1] + (src[j-1] == pattern[i]));
				if (dp[nl][j] == pattern.size())
					return true;
			}
		}
		return false;
	};
	static vector<string> camel_tokenize(const string &s) {
		vector<string> res;
		int p=0;
		for (int i=1; i<s.size(); i++) {
			if (isupper(s[i])) {
				res.push_back(s.substr(p, i-p));
				p = i;
			}
		}
		res.push_back(s.substr(p, s.size()-p));
		return res;
	}
public:
    static vector<bool> camelMatch(const vector<string>& queries, const string &pattern) {
  		vector<bool> res;
		vector<string> tok_pattern = camel_tokenize(pattern);
		for (auto src:queries) {
			vector<string> tok_src = camel_tokenize(src);
			bool fnd;
			if (tok_pattern.size() == tok_src.size()) {
				fnd = true;
				for (int i=0; i<tok_pattern.size(); i++)
					fnd &= is_subseq(tok_src[i], tok_pattern[i]);
			} else {
				fnd = false;
			}
			res.push_back(fnd);
        }
        return res;
    }
};

int main(int argc, char **argv) {
	//cerr << Solution::is_subseq("Competitive", "Coo") << endl;
	for (bool r:Solution::camelMatch({{"FooBar","FooBarTest","FootBall","FrameBuffer","ForceFeedBack"}}, "FB"))
		cout << r << '\n';
	cout << "\n";
	for (bool r:Solution::camelMatch({{"CompetitiveProgramming","CounterPick","ControlPanel"}}, "CooP"))
		cout << r << '\n';
	cout << "\n";
	for (bool r:Solution::camelMatch({{"FooBar","FooBarTest","FootBall","FrameBuffer","ForceFeedBack"}}, "FoBa"))
		cout << r << '\n';
	return 0;
}
