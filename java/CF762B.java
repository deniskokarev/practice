import java.io.PrintStream;
import java.util.Arrays;
import java.util.Scanner;

public class CF762B {
	/**
	 * solution result
	 */
	public static class Answer {
		long n, c;
		public Answer(long n, long c) {
			this.n = n;
			this.c = c;
		}

		@Override
		public String toString() {
			return Long.toString(n) + " " + Long.toString(c);
		}
	};

	static class Mouse implements Comparable<Mouse>{
		final static int U = 0;
		final static int P = 1;
		final static int B = 2;
		long c;
		int t;
		Mouse(int c, int t) {
			this.c = c;
			this.t = t;
		}
		@Override
		public int compareTo(Mouse o) {
			return Long.compare(c, o.c);
		}
	}
	/**
	 * input parser
	 */
	public static class Input {
		Mouse m[];
		int nm[];
		int upb[];
		public Input(Scanner sc) {
			upb = new int[3];
			upb[Mouse.U] = sc.nextInt();
			upb[Mouse.P] = sc.nextInt();
			upb[Mouse.B] = sc.nextInt();
			int n = sc.nextInt();
			m = new Mouse[n];
			nm = new int[2];
			for (int i=0; i<n; i++) {
				int cost = sc.nextInt();
				String s = sc.nextLine().trim();
				m[i] = new Mouse(cost, s.startsWith("U")?Mouse.U:Mouse.P);
				nm[m[i].t]++;
			}
		}
	};

	/**
	 * solver function
	 */
	public static Answer solve(Input in) {
		Mouse u[] = new Mouse[in.nm[Mouse.U]];
		Mouse p[] = new Mouse[in.nm[Mouse.P]];
		Mouse up[][] = new Mouse[][]{u, p};
		int ni[] = new int[2];
		for (Mouse m:in.m)
			up[m.t][ni[m.t]++] = m;
		Arrays.sort(u);
		Arrays.sort(p);
		int iu = 0;
		int ip = 0;
		long cost = 0;
		int n = 0;
		int t = Mouse.U;
		for (int i=0; i<in.upb[t] && i<up[t].length; i++) {
			cost += up[t][i].c;
			n++;
			iu++;
		}
		t = Mouse.P;
		for (int i=0; i<in.upb[t] && i<up[t].length; i++) {
			cost += up[t][i].c;
			n++;
			ip++;
		}
		Mouse rem[] = new Mouse[u.length-iu + p.length-ip];
		System.arraycopy(u, iu, rem, 0, u.length-iu);
		System.arraycopy(p, ip, rem, u.length-iu, p.length-ip);
		Arrays.sort(rem);
		for (int i=0; i<rem.length && i<in.upb[Mouse.B]; i++) {
			cost += rem[i].c;
			n++;
		}
		return new Answer(n, cost);
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
