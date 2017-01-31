package dk.draft;

import java.util.PriorityQueue;

import dk.alg.Heap;

/**
 * Find kth number in sequence devisible by only 3,5,7
 * @author kokarev
 *
 */
public class Mult357 {
	static void prn(char b[], int sz) {
		long p = 1;
		int i;
		for (i=sz-1; i>0; i--) {
			System.out.print(b[i]);
			System.out.print(" * ");
			p *= b[i]-'0';
		}
		System.out.print(b[i]);
		p *= b[i]-'0';
		System.out.println(" = "+p);
	}
	static void solve(int k) {
		long h[] = new long[2*k];
		long prev = 0;
		int sz = 0;
		h[sz++] = 1;
		while (k>0) {
			long v = h[0];
			if (sz > 1) {
				sz--;
				h[0] = h[sz];
				Heap.siftDown(h, 0, sz);
			}
			if (v == prev)
				continue;
			System.out.println(v);
			prev = v;
			h[sz++] = v*3; Heap.siftUp(h, sz-1);
			h[sz++] = v*5; Heap.siftUp(h, sz-1);
			h[sz++] = v*7; Heap.siftUp(h, sz-1);
			k--;
		}
	}
	static void solve2(int k) {
		PriorityQueue<Long> q = new PriorityQueue<>();
		q.add(1L);
		long prev = 0;
		while (k>0) {
			long v = q.remove();
			if (v == prev)
				continue;
			prev = v;
			q.add(v*3);
			q.add(v*5);
			q.add(v*7);
			System.out.println(v);
			k--;
		}
	}
	public static void main(String args[]) {
		solve(4138);
	}
}
