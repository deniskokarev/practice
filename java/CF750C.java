import java.io.PrintStream;
import java.util.Scanner;

public class CF750C {
	/**
	 * solution result
	 */
	public static class Answer {
		String s;
		public Answer(String s) {
			this.s = s;
		}

		@Override
		public String toString() {
			return s;
		}
	};

	static class Res {
		int score;
		int div;
		Res(int score, int div) {
			this.div = div;
			this.score = score;
		}
	}
	/**
	 * input parser
	 */
	public static class Input {
		int n;
		Res r[];
		public Input(Scanner sc) {
			n = sc.nextInt();
			r = new Res[n];
			for (int i=0; i<n; i++)
				r[i] = new Res(sc.nextInt(), sc.nextInt());
		}
	};

	/**
	 * solver function
	 */
	public static Answer solve(Input in) {
		long mx, mn;
		int div = in.r[0].div;
		if (div == 1) {
			mn = 1900;
			mx = Integer.MAX_VALUE;
		} else {
			mn = Integer.MIN_VALUE;
			mx = 1899;
		}
		int score = in.r[0].score;
		for (int i=1; i<in.r.length; i++) {
			mx += score;
			mn += score;
			if (div != in.r[i].div) {
				if (div == 1) {
					// 1->2
					if (mn > 1899)
						return new Answer("Impossible");
					mx = Math.min(1899, mx);
				} else {
					// 2->1
					if (mx < 1900)
						return new Answer("Impossible");
					mn = Math.max(1900, mn);
				}
				div = in.r[i].div;
			} else {
				if (div == 1) {
					if (mx < 1900)
						return new Answer("Impossible");
					mn = Math.max(1900, mn);
				} else {
					if (mn > 1899)
						return new Answer("Impossible");
					mx = Math.min(1899, mx);
				}
			}
			score = in.r[i].score;
		}
		mx += score;
		mn += score;
		if (mx > Integer.MAX_VALUE/2) {
			return new Answer("Infinity");
		} else {
			return new Answer(Long.toString(mx));
		}
	}

	/**
	 * standard CodeForces executable mantra
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
