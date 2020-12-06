class Solution {
public:
	static int concatenatedBinary(int n) {
		constexpr int MOD = 1e9+7;
		constexpr int BT = 17;
		constexpr int MSK = 1<<(BT-1);
		int64_t rem=0;
		for (int i=1; i<=n; i++) {
			unsigned b = i;
			int j=0;
			while (!(b&MSK)) {
				b <<= 1;
				j++;
			}
			while (j<BT) {
				rem <<= 1;
				rem += ((b&MSK) != 0);
				rem %= MOD;
				b <<= 1;
				j++;
			}
		}
		return rem;
	}
};

