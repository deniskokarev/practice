class Solution {
	static int steps(const vector<int> &mv100, bitset<32> bb, int h) {
		if (h < 0) {
			return 0;
		} else {
			if (bb[h])
				return mv100[h+1] - steps(mv100, bb, h-1);
			else
				return steps(mv100, bb, h-1);
		}
	}
public:
	static int minimumOneBitOperations(int n) {
		vector<int> mv100(32); // steps to convert 0000 <-> 1000
		mv100[0] = 0;
		for (int i=1; i<32; i++) {
			mv100[i] = mv100[i-1]*2 + 1;
		}
		bitset<32> bb(n);
		return steps(mv100, bb, 31);
	}
};

