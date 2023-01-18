#include <iostream>
#include <vector>
#include <queue>
/* https://leetcode.com/problems/maximum-sum-circular-subarray/ */
using namespace std;

class Solution {
    using M = struct {
        int mn;
        int p;
    };
public:
    static int maxSubarraySumCircular(const vector<int>& nums) {
        int sz = nums.size();
        deque<M> mn_sm {{INT_MAX/2, -1}};
        int sm = 0;
        int ans = INT_MIN;
        for (int i=0; i < 2*sz; i++) {
            int p = i % sz;
            while (mn_sm.front().p + sz < i)
                mn_sm.pop_front();
            sm += nums[p];
            ans = max(ans, sm - mn_sm.front().mn);
            while (!mn_sm.empty() && mn_sm.back().mn > sm)
                mn_sm.pop_back();
            mn_sm.push_back({sm, i});
        }
        return ans;
    }
};

class Solution_old {
	struct MN {
		int mn, pos;
	};
public:
	static int maxSubarraySumCircular(const vector<int>& aa) {
		int sz = aa.size();
		deque<MN> mnq;
		int sm = aa[0];
		mnq.push_back(MN{sm, 0});
		int mx = sm;
		for (int i=1; i<2*sz; i++) {
			int a = aa[i%sz];
			sm += a;
			while (mnq.size() && mnq.front().pos < i-sz)
				mnq.pop_front();
			mx = max(mx, sm-mnq.front().mn);
			while (mnq.size() && sm <= mnq.back().mn)
				mnq.pop_back();
			mnq.push_back(MN{sm, i});
		}
		return mx;
	}
};

int main(int argc, char **argv) {
	cout << Solution::maxSubarraySumCircular({3,-1,2,-1}) << endl;
	cout << Solution::maxSubarraySumCircular({-1}) << endl;
	return 0;
}
