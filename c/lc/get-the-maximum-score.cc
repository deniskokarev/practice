// https://leetcode.com/problems/get-the-maximum-score/
class Solution {
	static constexpr unsigned MOD = 1e9+7;
public:
	static unsigned maxSum(const vector<int>& nums0, const vector<int>& nums1) {
		vector<int> back {int(nums0.size())-1, int(nums1.size())-1};
		vector<uint64_t> edp {0, 0};
		vector<int> pt(nums0.size() + nums1.size());
		merge(nums0.begin(), nums0.end(), nums1.begin(), nums1.end(), pt.begin());
		unsigned pt_sz = unique(pt.begin(), pt.end()) - pt.begin();
		pt.resize(pt_sz);
		reverse(pt.begin(), pt.end());
		for (unsigned e:pt) {
			if (back[0] >= 0 && e == nums0[back[0]]) {
				if (back[1] >= 0 && e == nums1[back[1]]) {
					edp[0] = edp[1] = max(edp[0], edp[1]) + e;
					back[0]--, back[1]--;
				} else {
					edp[0] += e;
					back[0]--;
				}
			} else {
				if (back[1] >= 0 && e == nums1[back[1]]) {
					edp[1] += e;
					back[1]--;
				}
			}
		}
		return max(edp[0], edp[1]) % MOD;
	}
};

