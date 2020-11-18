class Solution {
public:
	static int minOperations(const vector<int>& nums, int x) {
		int sz = nums.size();
		unordered_map<int,int> rsm;
		rsm[0] = sz;
		int sm = 0;
		for (int i=sz-1; i>=0; i--) {
			sm += nums[i];
			rsm[sm] = i;
		}
		int mn = INT_MAX;
		sm = 0;
		auto it = rsm.find(x-sm);
		if (it != rsm.end())
			mn = sz - it->second;
		for (int i=0; i<sz; i++) {
			sm += nums[i];
			it = rsm.find(x-sm);
			if (it != rsm.end() && i < it->second)
				mn = min(mn, i + 1 + sz - it->second);
		}
		if (mn != INT_MAX)
			return mn;
		else
			return -1;
	}
};
