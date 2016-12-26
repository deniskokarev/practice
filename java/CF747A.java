import java.io.PrintStream;
import java.util.Scanner;

public class CF747A {
	/**
	 * solution result
	 */
	public static class Answer {
		int r, d;
		public Answer(int r, int d) {
			this.r = r;
			this.d = d;
		}

		@Override
		public String toString() {
			return r+" "+(r+d);
		}
	};

	/**
	 * input parser
	 */
	public static class Input {
		int n;
		public Input(Scanner sc) {
			n = sc.nextInt();
		}
	};

	/**
	 * solver function
	 */
	public static Answer solve(Input in) {
		int d = 0;
		int r;
		while (true) {
			int us = d*d/4+in.n;
			int s = (int)Math.sqrt(us);
			if (s*s == us) {
				r = s-d/2;
				break;
			}
			d += 2;
		}
		Answer ans = new Answer(r, d);
		return ans;
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
