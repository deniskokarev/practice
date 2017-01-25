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
			return c < o.c?(-1):(c==o.c)?0:1;
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
		ni[0] = ni[1] = 0;
		long cost = 0;
		int n = 0;
		for (int t=Mouse.U; t<=Mouse.P; t++) {
			for (int i=0; i<in.upb[t] && i<up[t].length; i++) {
				cost += up[t][i].c;
				n++;
				ni[t]++;
			}
		}
		int tot = in.upb[0]+in.upb[1]+in.upb[2];
		for (int i=0; i<in.upb[Mouse.B] && (ni[Mouse.U] < up[Mouse.U].length || ni[Mouse.P] < up[Mouse.P].length) ; i++) {
			for (int t=Mouse.U; t<=Mouse.P; t++) {
				if (ni[t] < up[t].length) {
					if (ni[t^1] >= up[t^1].length || up[t][ni[t]].c < up[t^1][ni[t^1]].c) {
						cost += up[t][ni[t]++].c;
						n++;
						if (n >= tot)
							return new Answer(n, cost);
					}
				}
			}
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
