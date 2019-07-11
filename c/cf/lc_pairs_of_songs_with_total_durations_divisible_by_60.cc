#include <iostream>
#include <vector>
/* https://leetcode.com/problems/pairs-of-songs-with-total-durations-divisible-by-60/ */
using namespace std;

class Solution {
public:
    static int numPairsDivisibleBy60(const vector<int>& time) {
		vector<int> rr(60);
		int ans = 0;
		for (auto t:time) {
			int r = t%60;
			ans += rr[(60-r)%60];
			rr[t%60]++;
		}
		return ans;
    }
};

int main(int argc, char **argv) {
	cout << Solution::numPairsDivisibleBy60({30,20,150,100,40}) << endl;
	cout << Solution::numPairsDivisibleBy60({60,60,60}) << endl;
	return 0;
}
