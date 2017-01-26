package dk.draft;

public class Bsearch {
	static int bsearch_r(int a[], int el, int f, int t) {
		if (f<t) {
			int m = f+(t-f)/2;
			if (a[m] == el)
				return m;
			else if (a[m] < el)
				return bsearch_r(a, el, m+1, t);
			else
				return bsearch_r(a, el, f, m);
		} else {
			return -1;
		}
	}

	static int bsearch(int a[], int el) {
		return bsearch_r(a, el, 0, a.length);
	}
	
	public static void main(String[] args) {
		int cs = 0;
		int a[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
		for (int j=1; j<=a.length; j++) {
			int b[] = new int[j];
			cs = 0;
			System.arraycopy(a, 0, b, 0, j);
			for (int i:b)
				cs += bsearch(b, i);
			System.out.println("expected:"+(b.length*(b.length-1)/2)+" got:"+cs);
		}
	}
}
