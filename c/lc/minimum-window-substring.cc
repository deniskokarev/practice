// https://leetcode.com/problems/minimum-window-substring
// faster solution 99%

constexpr int INF = INT_MAX / 2;

using uchar = unsigned char;

class Solution {
public:
    static string minWindow(const string &s, const string &t) {
        int lcnt[256] = {0}; // each char match cnt: when need --, when found ++
        int need[256] = {0}; // ignore other chars
        for (uchar c: t) {
            lcnt[c]--;
            need[c] = 1;
        }
        int tcnt = 0; // total char match cnt: when need --, when found ++
        for (int c: lcnt)
            tcnt -= (c < 0);
        int sz = s.size();
        int l = 0, r = INF;
        int i = 0, j = 0;
        while (i < sz) {
            while (j < sz && tcnt) {
                uchar c = s[j++];
                if (need[c] && !(++lcnt[c]))
                    tcnt++;
            }
            if (!tcnt && j - i < r - l) {
                l = i;
                r = j;
            }
            uchar c = s[i++];
            if (need[c] && !(lcnt[c]--))
                tcnt--;
        }
        if (r < INF)
            return s.substr(l, r - l);
        else
            return "";
    }
};



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
		vector<int> th(256, 0);
		for (uchar c:t)
			th[c]++;
		int cnt = 0;
		vector<deque<int>> qq(256);
		int mn = INT_MAX;
		int l=-1, r=INT_MAX;
		vector<int> hh(2*256, INT_MAX);
		for (int i=0; i<s.size(); i++) {
			uchar c = s[i];
			if (th[c]) {
				qq[c].push_back(i);
				if (qq[c].size() > th[c])
					qq[c].pop_front();
				else if (qq[c].size() == th[c])
					cnt += th[c];
				int j = 256+c;
				hh[j] = qq[c].front();
				for ( ; j>1; j>>=1) // 8 times
					hh[j >> 1] = min(hh[j], hh[j^1]);
				int tl = hh[1];
				if (cnt == t.size() && mn > i-tl) {
					mn = i-tl;
					l = tl;
					r = i;
				}
			}
		}
		if (mn < INT_MAX)
			return s.substr(l, r-l+1);
		else
			return "";
	}
};

int main(int argc, char **argv) {
	cout << Solution::minWindow("ADOBECODEBANC", "ABC") << endl;
	cout << Solution::minWindow("a", "aa") << endl;
	cout << Solution::minWindow("aa", "aa") << endl;
	cout << Solution::minWindow("ABAB", "ABB") << endl;
}
