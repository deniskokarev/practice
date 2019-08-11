#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

/* https://leetcode.com/contest/weekly-contest-142/problems/statistics-from-a-large-sample/ */

using namespace std;

class Solution {
public:
	static vector<double> sampleStats(const vector<int>& count) {
		int n = accumulate(count.begin(), count.end(), 0L);
		int mn = INT_MAX;
		int mx = INT_MIN;
		int mode = 0;
		int s = 0;
		int med = -1;
		int64_t sm = 0;
		for (int i=0; i<count.size(); i++) {
			sm += count[i]*i;
			if (count[i]) {
				if (med == -1) {
					if (s*2 == n) {
						med = mx + i;
					} else if (s*2 > n) {
						med = mx + mx;
					}
				}
				mn = min(mn, i);
				mx = max(mx, i);
				if (count[mode] < count[i])
					mode = i;
				s += count[i];
			}
		}
		if (med == -1)
			med = mx;
		return {(double)mn, (double)mx, ((double)sm)/n, ((double)med)/2, (double)mode};
	}
};

int main(int argc, char **argv) {
	return 0;
}
