#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
/* https://leetcode.com/contest/weekly-contest-156/problems/get-equal-substrings-within-budget/ */
using namespace std;

class Solution {
public:
    static int equalSubstring(const string &s, const string &t, int cost) {
        int sz = s.size();
        int mx = 0;
        int prev_l = 1, prev_d = 0;
        for (int p = 0; p < sz; p++) {
            cost += prev_d;
            int l = prev_l - 1;
            for (int i = p + l; i < sz && abs(s[i] - t[i]) <= cost; i++) {
                l++;
                cost -= abs(s[i] - t[i]);
            }
            prev_l = l;
            prev_d = abs(s[p] - t[p]);
            mx = max(mx, l);
        }
        return mx;
    }
};

class Solution {
public:
	static int equalSubstring(const string &s, const string &t, int maxCost) {
		vector<int> cost(s.size()+1);
		for (int i=1; i<cost.size(); i++)
			cost[i] = cost[i-1] + std::abs(s[i-1]-t[i-1]);
		int mx = 0;
		for (int j=0,i=1; i<cost.size(); i++) {
			while (j<i && cost[i]-cost[j] > maxCost)
				j++;
			mx = max(mx, i-j);
		}
		return mx;
	}
};

int main(int argc, char **argv) {
	cout << Solution::equalSubstring("abcd", "bcdf", 3) << endl;
	cout << Solution::equalSubstring("abcd", "cdef", 3) << endl;
	cout << Solution::equalSubstring("abcd", "acde", 0) << endl;
	cout << Solution::equalSubstring("a", "b", 0) << endl;
	return 0;
}
