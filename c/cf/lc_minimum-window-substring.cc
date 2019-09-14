#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <queue>
// https://leetcode.com/problems/minimum-window-substring/

using namespace std;

class Solution {
	using uchar = unsigned char;
public:
	static string minWindow(const string &s, const string &t) {
		int th[256] {0};
		for (uchar c:t)
			th[c]++;
		vector<deque<int>> qq(256);
		vector<vector<int>> lb(256, vector<int>(s.size()+1, -1));
		for (int i=1; i<=s.size(); i++) {
			for (int c=0; c<256; c++)
				lb[c][i] = lb[c][i-1];
			uchar c = s[i-1];
			qq[c].push_back(i);
			if (qq[c].size() > th[c])
				qq[c].pop_front();
			if (qq[c].size() == th[c])
				lb[c][i] = qq[c].front();
		}
		for (uchar c:{'a', 'A', 'B', 'C'}) {
			cerr << c << ": ";
			for (int i=0; i<=s.size(); i++)
				cerr << lb[c][i] << ' ';
			cerr << endl;
		}
		cerr << endl;
		int mn = INT_MAX;
		int l=-1, r=INT_MAX;
		for (int i=1; i<=s.size(); i++) {
			int mnl = INT_MAX;
			for (int c=0; c<256; c++)
				if (th[c])
					mnl = min(mnl, lb[c][i]);
			if (mnl >= 0 && mnl < INT_MAX && i-mnl < mn) {
				mn = i-mnl;
				l = mnl;
				r = i;
			}
		}
		cerr << "[" << l << ", " << r << "]" << endl;
		if (mn < INT_MAX)
			return s.substr(l-1, r-l+1);
		else
			return "";
	}
};

int main(int argc, char **argv) {
	cout << Solution::minWindow("ADOBECODEBANC", "ABC") << endl;
	cout << Solution::minWindow("a", "aa") << endl;
	cout << Solution::minWindow("aa", "aa") << endl;
}
