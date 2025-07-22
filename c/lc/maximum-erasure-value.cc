// https://leetcode.com/problems/maximum-erasure-value

class Solution {
public:
	static int maximumUniqueSubarray(const vector<int> &nums) {
		static constexpr int MX = 1e4;
		int sz = nums.size();
		int f = 0, t = 0;
		vector<bool> s(MX + 1);
		int sm = 0, mx = 0;
		while (t < sz) {
			int el = nums[t++];
			if (s[el]) {
				while (nums[f] != el) {
					s[nums[f]] = false;
					sm -= nums[f++];
				}
				s[nums[f]] = false;
				sm -= nums[f++];
			}
			s[el] = true;
			sm += el;
			mx = max(mx, sm);
		}
		return mx;
	}
};

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
