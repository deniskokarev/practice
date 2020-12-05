class Solution {
public:
	static vector<int> mostCompetitive(const vector<int>& nums, int k) {
		int rsz = nums.size();
		vector<int> ans;
		for (int n:nums) {
			while (!ans.empty() && ans.back() > n && rsz + ans.size() > k)
				ans.pop_back();
			ans.push_back(n);
			rsz--;
		}
		ans.resize(k);
		return ans;
	}
};
