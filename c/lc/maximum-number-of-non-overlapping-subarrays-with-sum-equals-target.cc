class Solution {
public:
	static int maxNonOverlapping(const vector<int>& nums, int tgt) {
		int sz = nums.size();
		unordered_map<int,int> sm2pos;
		sm2pos[0] = -1;
		int sm = 0;
		int barrier = -1;
		int cnt = 0;
		for (int i=0; i<sz; i++) {
			sm += nums[i];
			if (sm2pos.count(sm-tgt) && sm2pos[sm-tgt]>=barrier) {
				barrier = i;
				cnt++;
			}
			sm2pos[sm] = i;
		}
		return cnt;
	}
};

