package den.comb;

import java.util.Iterator;

public class ChooseIterable implements Iterable<int[]> {
	protected int n, k;	

	public ChooseIterable(int n, int k) {
		this.n = n;
		this.k = k;
	}
	
	@Override
	public Iterator<int[]> iterator() {
		return new ChooseIterator(n, k);
	}
	
	public long count() {
		// r = n!/(n-k)!k!
		long r = 1;
		long u = n-k+1;
		for (long d=1; d<=k; d++,u++) {
			r *= u;
			r /= d;
		}
		return r;
	}
}

/**
 * Choose n, k iterator which returns int[] selections
 */
class ChooseIterator implements Iterator<int[]> {
	protected int[] kpos;
	protected int n, k, pos;	
	public ChooseIterator(int n, int k) {
		int i;
		this.n = n;
		this.k = k;
		kpos = new int[k];
		for (i=0; i<k-1; i++)
			kpos[i] = i;
		// set the last idx one less, so the very first next() would inc it
		kpos[i] = i-1; 
		pos = k-1;
	}
	
	@Override
	public boolean hasNext() {
		return kpos[0]<n-k;
	}
	
	@Override
	public int[] next() {
		if (pos < 0) {
			return null;
		} else if (kpos[pos] < n-(k-pos)) {
				int p = kpos[pos]+1; 
				for (int i=pos; i<k; i++)
					kpos[i] = p++;
				pos = k-1;
				return kpos;
		} else {
			pos--;
			return next();
		}
	}
}