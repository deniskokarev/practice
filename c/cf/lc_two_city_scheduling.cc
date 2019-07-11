#include <iostream>
#include <vector>
#include <queue>
/* https://leetcode.com/problems/two-city-scheduling/ */
using namespace std;

class Solution {
public:
    static int twoCitySchedCost(const vector<const vector<int>>& costs) {
		int sz = costs.size();
		vector<pair<int, vector<int>>> srt(sz);
		for (int i=0; i<sz; i++)
			srt[i] = make_pair(abs(costs[i][0]-costs[i][1]), costs[i]);
		sort(srt.begin(), srt.end(), std::greater<pair<int, vector<int>>>());
		int nn[2] = {sz/2, sz/2};
		int tp = 0;
		int i;
		for (i=0; i<sz && nn[0]>0 && nn[1]>0; i++) {
			if (srt[i].second[0] < srt[i].second[1]) {
				tp += srt[i].second[0];
				nn[0]--;
			} else {
				tp += srt[i].second[1];
				nn[1]--;
			}
		}
		if (nn[1] > 0)
			for (;i<sz;i++)
				tp += srt[i].second[1];
		else
			for (;i<sz;i++)
				tp += srt[i].second[0];
		return tp;
    }
};

int main(int argc, char **argv) {
	cout << Solution::twoCitySchedCost({{10,20},{30,200},{400,50},{30,20}}) << endl;
	cout << Solution::twoCitySchedCost({{70,311},{74,927},{732,711},{126,583},{857,118},{97,928},{975,843},{175,221},{284,929},{816,602},{689,863},{721,888}}) << endl;
	return 0;
}
