package dk.draft;

public class Range {
	int l, r, sum;
	Range() {
		this(0, 0);
	}
	Range(int l, int r) {
		this.l = l;
		this.r = r;
		sum = 0;
	}
	@Override
	public boolean equals(Object obj) {
	    if (obj == null)
	        return false;
	    if (!Range.class.isAssignableFrom(obj.getClass()))
	        return false;
	    final Range rb = (Range) obj;
	    return l == rb.l && r == rb.r;
	}

	/**
	 * taken from http://e-maxx.ru/algo/maximum_average_segment
	 * @param a - array
	 * @param rc - Range to populate 
	 * @return rc
	 */
	public static Range maxRange(int a[], Range rc) {
		int ans = a[0], ans_l = 0, ans_r = 0;
		int sum = 0, min_sum = 0, min_pos = -1;
		for (int r=0; r<a.length; ++r) {
			sum += a[r];
			int cur = sum - min_sum;
			if (cur > ans) {
				ans = cur;
				ans_l = min_pos + 1;
				ans_r = r;
			}
			if (sum < min_sum) {
				min_sum = sum;
				min_pos = r;
			}
		}
		rc.l = ans_l;
		rc.r = ans_r;
		rc.sum = ans;
		return rc;
	}
}
