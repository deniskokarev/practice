import java.io.PrintStream;
import java.util.HashMap;
import java.util.Map;
import java.util.PriorityQueue;
import java.util.Scanner;

public class CF762A {
	/**
	 * solution result
	 */
	public static class Answer {
		long n;
		public Answer(long n) {
			this.n = n;
		}

		@Override
		public String toString() {
			return Long.toString(n);
		}
	};

	/**
	 * input parser
	 */
	public static class Input {
		long n;
		int k;
		public Input(Scanner sc) {
			n = sc.nextLong();
			k = sc.nextInt();
		}
	};

	static int uPrimeFactors(long n, long p[], int pc[]) {
		assert(n > 1);
		int np = 0;
		for (long i = 2; i <= n / i; i++) {
			if (n % i == 0) {
				pc[np] = 1;
				p[np] = i;
				n /= i;
				while (n % i == 0) {
					n /= i;
					pc[np]++;
				}
				np++;
			}
		}
		if (n > 1) {
			pc[np] = 1;
			p[np++] = n;
		}
		return np;
	}

	static class Val implements Comparable<Val> {
		long v;
		int fc[];
		
		Val(int fc[], int fcSz, long v) {
			this.fc = new int[fcSz];
			System.arraycopy(fc, 0, this.fc, 0, fcSz);
			this.v = v;
		}
		@Override
		public int compareTo(Val o) {
			return Long.compare(v,  o.v);
		}
		
	}
	/**
	 * solver function
	 */
	public static Answer solve(Input in) {
		int k = in.k;
		long f[] = new long[64];
		int fc[] = new int[64];
		int nf = uPrimeFactors(in.n, f, fc);
		PriorityQueue<Val> q = new PriorityQueue<>();
		Map<Long, Boolean> m = new HashMap<>();
		q.add(new Val(fc, nf, 1L));
		m.put(1L, true);
		long prev = 0;
		Val v = null;
		while (k>0) {
			if (q.size() < 1)
				return new Answer(-1);
			v = q.remove();
			m.remove(v.v);
			for (int i=0; i<nf; i++) {
				long lv = v.v*f[i];
				if (v.fc[i] > 0 && m.get(lv) == null) {
					Val nv = new Val(v.fc, v.fc.length, lv);
					nv.fc[i]--;
					q.add(nv);
					m.put(lv, true);
				}
			}
			if (v.v != prev)
				k--;
			prev = v.v;
		}
		return new Answer(v.v);
	}

	/**
	 * standard executable mantra
	 */
	public static void proc(Scanner sc, PrintStream out) {
		Input in = new Input(sc);
		out.println(solve(in));
	}

	public static void main(String[] args) {
		try (Scanner sc = new Scanner(System.in)) {
			proc(sc, System.out);
		}
	}
}
