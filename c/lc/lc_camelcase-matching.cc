#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
/* https://leetcode.com/problems/camelcase-matching/ */
using namespace std;

class Solution {
	static bool has_subseq(const string &src, const string &pattern) {
		int si = 0, pi = 0;
		while (si < src.size() && pi < pattern.size()) {
			if (src[si] == pattern[pi])
				pi++;
			si++;
		}
		return (pi == pattern.size());
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
					fnd &= has_subseq(tok_src[i], tok_pattern[i]);
			} else if (tok_pattern.size()+1 == tok_src.size() && islower(tok_src[0][0])) {
				fnd = true;
				for (int i=0; i<tok_pattern.size(); i++)
					fnd &= has_subseq(tok_src[i+1], tok_pattern[i]);
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
