#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
/* https://leetcode.com/problems/camelcase-matching/ */
using namespace std;

class Solution {
public:
    static vector<bool> camelMatch(const vector<string>& queries, const string &pattern) {
        vector<bool> res;
        vector<string> pp;
        int p = 0;
        for (int i=1; i<pattern.size(); i++) {
            if (isupper(pattern[i])) {
                pp.push_back(pattern.substr(p,i-p));
				p = i;
			}
		}
        pp.push_back(pattern.substr(p, pattern.size()-p));
		for (auto &p:pp)
			cerr << "p=" << p << endl;
        for (auto src:queries) {
            for (auto &p:pp) {
                int idx = idx=src.find(p, 0);
                while (idx != string::npos) {
                    for (int i=idx+p.size(); i<src.size() && islower(src[i]); i++)
                        src[i] = '_';
                    idx = src.find(p, idx+p.size());
                }
            }
            string s;
            for (auto c:src)
                if (c != '_')
                    s.push_back(c);
            res.push_back(s == pattern);
        }
        return res;
    }
};

int main(int argc, char **argv) {
	for (bool r:Solution::camelMatch({{"FooBar","FooBarTest","FootBall","FrameBuffer","ForceFeedBack"}}, "FB"))
		cout << r << '\n';
	return 0;
}
