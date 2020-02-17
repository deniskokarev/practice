#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
/* https://leetcode.com/contest/biweekly-contest-9/problems/find-smallest-common-element-in-all-rows/ */
using namespace std;

class Solution {
public:
    static int smallestCommonElement(const vector<vector<int>>& mat) {
        vector<int> cnt(1e4+1);
		for (auto &row:mat) {
			cnt[row[0]]++;
			for (int i=1; i<row.size(); i++)
				if (row[i] > row[i-1])
					cnt[row[i]]++;
		}
		for (int i=0; i<1e4+1; i++)
			if (cnt[i] == mat.size())
				return i;
		return -1;
    }
};

int main(int argc, char **argv) {
	cout << Solution::smallestCommonElement({{1,2,3,4,5},{2,4,5,8,10},{3,5,7,9,11},{1,3,5,7,9}}) << endl;
	return 0;
}
