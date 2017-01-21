package dk.draft;

public class Mergesort {

	static int combine(int a[], int apf, int apt, int b[], int bpf, int bpt, int c[], int cp) {
		int ap = apf;
		int bp = bpf;
		while (ap < apt && bp < bpt)
			if (a[ap] < b[bp])
				c[cp++] = a[ap++];
			else
				c[cp++] = b[bp++];
		while (ap < apt)
			c[cp++] = a[ap++];
		while (bp < bpt)
			c[cp++] = b[bp++];
		return cp;
	}
	
	static int[] mergeSort(int src[], int dst[]) {
		assert(src.length == dst.length);
		int sz = src.length;
		int pass = 0;
		int a[][] = new int[][]{src, dst};
		int step;
		while((step = 1 << pass) < sz) {
			int i = 0;
			int p = 0;
			while ((i+2)*step <= sz) {
				p = combine(a[pass%2], i*step, (i+1)*step, a[pass%2], (i+1)*step, (i+2)*step, a[(pass+1)%2], p);
				i += 2;
			}
			p = combine(a[pass%2], Math.min(i*step,sz), Math.min((i+1)*step, sz), a[pass%2], Math.min((i+1)*step, sz), Math.min((i+2)*step, sz), a[(pass+1)%2], p);
			pass++;
		}
		return a[pass%2];
	}
	
	public static void main(String args[]) {
		int a[] = new int[]{3,5,6,2,8,4,0,9,4,1,7,8,9,6,3,8,1};
		//int a[] = new int[]{5,4,3,2,1,0};
		int b[] = new int[a.length];
		for (int v:mergeSort(a, b))
			System.out.print(v+ " ");
		System.out.println();
	}
}
