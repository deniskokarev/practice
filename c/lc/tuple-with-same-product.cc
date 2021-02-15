class Solution {
public:
	int tupleSameProduct(vector<int>& nums) {
		int sz = nums.size();
		unordered_map<int,int> prod;
		vector<int> nn(nums);
		sort(begin(nn), end(nn));
		nn.resize(unique(begin(nn),end(nn))-nn.begin());
		int ans = 0;
		for (int i=0; i<sz; i++) {
			for (int j=i+1; j<sz; j++) {
				ans += prod[nums[i]*nums[j]];
				prod[nums[i]*nums[j]]++;
			}
		}
		return ans*8;
	}
};
