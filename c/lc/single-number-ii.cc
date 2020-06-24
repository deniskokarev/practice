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
		int sel_bit = -1;
		for (sel_bit=0; sel_bit<32 && bit_hist[sel_bit] % 3 == 0; sel_bit++);
		if (sel_bit == 32)
			return 0;
		unsigned msk = 1U<<sel_bit;
		int bit_hist2[32]{0};
		for (auto &n:nums) {
			if (n & msk) {
				bitset<32> bb(n);
				for (int i=0; i<32; i++)
					bit_hist2[i] += bb[i];
			}
		}
		bitset<32> res(0);
		for (int i=0; i<32; i++)
			if (bit_hist2[i] % 3)
				res[i] = 1;
		return res.to_ulong();
	}
};

