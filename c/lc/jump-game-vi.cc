struct MX {
	int pos;
	int mx;
};

class Solution {
public:
	static int maxResult(const vector<int>& nums, int k) {
		deque<MX> qq;
		int sz = nums.size();
		qq.push_back({0, nums[0]});
		for (int i=1; i<sz; i++) {
			while (qq.front().pos < i-k)
				qq.pop_front();
			MX mx = qq.front();
			while (!qq.empty() && qq.back().mx <= mx.mx + nums[i])
				qq.pop_back();
			qq.push_back({i, mx.mx + nums[i]});
		}
		return qq.back().mx;
	}
};
