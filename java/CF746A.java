import java.io.PrintStream;
import java.util.Scanner;
/**
 * http://codeforces.com/problemset/problem/746/A
 * @author kokarev
 *
 */

public class CF746A {
	/**
	 * solution result
	 */
	public static class Answer {
		int n;
		public Answer(int n) {
			this.n = n;
		}

		@Override
		public String toString() {
			return Integer.toString(n);
		}
	};

	/**
	 * input parser
	 */
	public static class Input {
		int l, a, p;
		public Input(Scanner sc) {
			l = sc.nextInt();
			a = sc.nextInt();
			p = sc.nextInt();
		}
	};

	/**
	 * solver function
	 */
	public static Answer solve(Input in) {
		int minL = Math.min(in.l, Math.min(in.p/4, in.a/2));
		Answer ans = new Answer(minL*7);
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
