class Solution {
public:
	static int maximumUniqueSubarray(const vector<int>& nums) {
		int cnt_uq = 1;
		vector<int> cnt(1e4+1);
		int sz = nums.size();
		int f = 0;
		cnt[nums[f]]++;
		int sms = nums[f];
		int mx = sms;
		for (int t=1; t<sz; t++) {
			cnt_uq -= (cnt[nums[t]] == 1);
			cnt[nums[t]]++;
			cnt_uq += (cnt[nums[t]] == 1);
			sms += nums[t];
			while (cnt_uq < (t-f+1)) {
				cnt_uq -= (cnt[nums[f]] == 1);
				cnt[nums[f]]--;
				cnt_uq += (cnt[nums[f]] == 1);
				sms -= nums[f];
				f++;
			}
			mx = max(mx, sms);
		}
		return mx;
	}
};
