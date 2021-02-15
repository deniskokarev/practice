class Solution {
	static bool dfs(const vector<unsigned> &fits, unsigned taken, int dep) {
		if (!dep) {
			return true;
		} else {
			for (auto m:fits)
				if (!(m & taken) && dfs(fits, taken|m, dep-1))
					return true;
			return false;
		}
	}
public:
	static bool makesquare(const vector<int>& nums) {
		int sz = nums.size();
		int p = accumulate(nums.begin(), nums.end(), 0);
		int l = p/4;
		if (!sz || 4*l != p)
			return false;
		const unsigned ONES = (1<<sz)-1;
		vector<unsigned> fits; // collection of bitsets that add up to l
		for (unsigned i=1; i<=ONES; i++) {
			int sm = 0;
			for (int b=0; b<sz; b++)
				sm += nums[b] * ((i>>b) & 1);
			if (sm == l)
				fits.push_back(i);
		}
		return dfs(fits, 0, 4);
	}
};
