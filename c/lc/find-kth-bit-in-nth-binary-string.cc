class Solution {
public:
	static int get_size(int n) {
		if (n <= 1) {
			return 1;
		} else {
			int sz_1 = get_size(n-1);
			return 2*sz_1+1;
		}
	}
	static bool findKthBit(int n, int k, bool inv) {
		if (n == 1) {
			return inv;
		} else {
			int sz = get_size(n);
			int sz_h = (sz-1)/2;
			if (k == sz_h) {
				return !inv;
			} else if (k < sz_h) {
				return findKthBit(n-1, k, inv);
			} else {
				return findKthBit(n-1, sz-k-1, !inv);
			}
		}
	}
	static char findKthBit(int n, int k) {
		k--;
		return findKthBit(n, k, false)+'0';
	}
};
