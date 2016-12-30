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
		long mn, mx;
		Res(int score, int div) {
			this.div = div;
			this.score = score;
			if (div == 1) {
				mn = 1900+score;
				mx = Long.MAX_VALUE;
			} else {
				mn = Long.MIN_VALUE;
				mx = 1899+score;
			}
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
		long bestMx, bestMn;
		int div;
		bestMx = in.r[0].mx;
		bestMn = in.r[0].mn;
		div = in.r[0].div;
		for (int i=1; i<in.r.length; i++) {
			long mx = in.r[i].mx;
			long mn = in.r[i].mn;
			if (div != in.r[i].div) {
				if (div == 1) {
					// 1->2
					if (bestMn+in.r[i].score > 1899)
						return new Answer("Impossible");
				} else {
					// 2->1
					if (bestMx+in.r[i].score < 1900)
						return new Answer("Impossible");
				}
			}
			if (mx < Long.MAX_VALUE && bestMx > mx)
				bestMx = mx;
			if (mn > Long.MIN_VALUE && bestMn < mn)
				bestMn = mn;
			div = in.r[i].div;
		}
		if (bestMx == Long.MAX_VALUE) {
			return new Answer("Infinity");
		} else {
			return new Answer(Long.toString(bestMx));
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
