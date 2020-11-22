class Solution {
public:
	static int mirrorReflection(int p, int q) {
		int w = 0;
		int h = q;
		while (!(h == 0 && w == 0 ) && h != p) {
			h += q;
			if (h > p) {
				q = -q;
				h = 2*p - h;
			} else if (h < 0) {
				q = -q;
				h = -h;
			}
			w ^= 1;
		}
		return (w+1)*(h!=0);
	}
};

