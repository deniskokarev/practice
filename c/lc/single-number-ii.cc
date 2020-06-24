// https://leetcode.com/problems/single-number-ii/
class Solution {
public:
	static int singleNumber(const vector<int>& nums) {
		int bit_hist[32]{0};
		for (unsigned n:nums) {
			bitset<32> bb(n);
			for (int i=0; i<32; i++)
				bit_hist[i] += bb[i];
		}
		bitset<32> res(0);
		for (int i=0; i<32; i++)
			res[i] = (bit_hist[i] % 3);
		return res.to_ulong();
	}
};

