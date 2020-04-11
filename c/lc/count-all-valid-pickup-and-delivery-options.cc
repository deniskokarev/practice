class Solution {
	static constexpr int MOD = 1e9+7;
public:
	static int countOrders(int n) {
		if (n <= 1) {
			return 1;
		} else {
			int64_t an = countOrders(n-1);
			an *= (2*(n-1)+1);
			an *= (2*(n-1)+2);
			an /= 2;
			an %= MOD;
			return an;
		}
	}
};

