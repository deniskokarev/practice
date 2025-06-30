// https://leetcode.com/problems/longest-harmonious-subsequence
class Solution {
public:
	static int findLHS(const vector<int> &nums) {
		unordered_map<int, int> cnt;
		int mx = 0;
		for (auto num: nums) {
			cnt[num]++;
			if (cnt.find(num - 1) != cnt.end()) mx = max(mx, cnt[num] + cnt[num - 1]);
			if (cnt.find(num + 1) != cnt.end()) mx = max(mx, cnt[num] + cnt[num + 1]);
		}
		return mx;
	}
};


class Solution {
public:
	static int findLHS(const vector<int>& nums) {
		map<int,int> cnt;
		for (auto num : nums) {
			cnt[num]++;
		}
		auto it1 = cnt.begin();
		auto it2 = next(it1);
		int mx = 0;
		while (it2 != cnt.end()) {
			if (it1->first + 1 == it2->first) {
				mx = max(mx, it1->second + it2->second);
			}
			it1 = next(it1);
			it2 = next(it2);
		}
		return mx;
	}
};


class Solution {
public:
    int findLHS(vector<int>& nums) {
        map<int,int> val2cnt;
        for (auto n:nums)
            val2cnt[n]++;
        pair<int,int> lst(-1e9-3, 0);
        int mx = 0;
        for (auto kv:val2cnt) {
            if (kv.first-lst.first == 1)
                mx = max(mx, kv.second+lst.second);
            lst = kv;
        }
        return mx;
    }
};
