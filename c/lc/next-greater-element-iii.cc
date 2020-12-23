class Solution {
public:
	static int nextGreaterElement(int n) {
		string dd = to_string(n);
		int sz = dd.size();
		if (sz < 2) {
			return -1;
		} else {
			// going backwards until suffix is in desc order
			// when first asc pair is met we find replacement candidate in the suffix, replacing,
			// inverting suffix and printing result
			for (int pos=sz-2; pos>=0; pos--) {
				if (dd[pos] < dd[pos+1]) {
					auto fnd = lower_bound(dd.begin()+pos+1, dd.end(), dd[pos], std::greater<char>());
					--fnd;
					swap(dd[pos], *fnd);
					reverse(dd.begin()+pos+1, dd.end());
					int64_t ans = stoll(dd);
					if (ans < INT_MAX)
						return ans;
					else
						return -1;
				}
			}
			return -1;
		}
	}
};
