package dk.draft;

import java.util.PriorityQueue;

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
		char place[] = new char[32];
		int sz = 3;
		for (sz=1; sz<=k; sz++) {
			for (int s=0; s<sz; s++) {
				for (int f=s; f<sz; f++) {
					for (int t=f; t<sz; t++) {
						place[t] = '3';
					}
					prn(place, sz);
					place[f] = '5';
				}
				prn(place, sz);
				place[s] = '7';
			}
			prn(place, sz);
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
		solve2(333);
	}
}
