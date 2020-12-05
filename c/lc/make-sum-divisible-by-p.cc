class Solution {
public:
	static int minSubarray(const vector<int>& nums, int p) {
		int sz = nums.size();
		int64_t sm = accumulate(nums.begin(), nums.end(), 0LL);
		int tgt_rem = sm % p;
		if (tgt_rem) {
			unordered_map<int,int> rem;
			rem[0] = -1;
			int sm = 0;
			int mn = INT_MAX;
			for (int i=0; i<sz; i++) {
				sm += nums[i];
				sm %= p;
				auto fnd = rem.find((p-tgt_rem+sm)%p);
				if (fnd != rem.end())
					mn = min(mn, i - fnd->second);
				rem[sm] = i;
			}
			if (mn >= sz)
				return -1;
			else
				return mn;
		} else {
			return 0;
		}
	}
};

