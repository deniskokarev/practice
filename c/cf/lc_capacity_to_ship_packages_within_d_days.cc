#include <iostream>
#include <vector>
#include <climits>
/* https://leetcode.com/problems/capacity-to-ship-packages-within-d-days/ */
using namespace std;

class Solution {
	static int needDays(const vector<int>& weights, int sc) {
		int d = 0;
		int sw = 0;
		for (auto w:weights) {
			if (w > sc)
				return INT_MAX;
			if (sw+w > sc) {
				d++;
				sw = w;
			} else {
				sw += w;
			}
		}
		return d+1;
	}
public:
    static int shipWithinDays(const vector<int>& weights, int D) {
		int f=0, t=INT_MAX/2;
		while (f<t) {
			int m = f+(t-f)/2;
			if (needDays(weights, m) > D)
				f = m+1;
			else
				t = m;
		}
		return f;
    }
};

int main(int argc, char **argv) {
	cout << Solution::shipWithinDays({1,2,3,4,5,6,7,8,9,10}, 5) << endl;
	cout << Solution::shipWithinDays({3,2,2,4,1,4}, 3) << endl;
	cout << Solution::shipWithinDays({1,2,3,1,1}, 4) << endl;
	return 0;
}
