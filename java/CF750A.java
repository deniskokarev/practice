import java.io.PrintStream;
import java.util.Scanner;

public class CF750A {
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
		int n, k;
		public Input(Scanner sc) {
			n = sc.nextInt();
			k = sc.nextInt();
		}
	};

	/**
	 * solver function
	 */
	public static Answer solve(Input in) {
		int t = 240-in.k;
		int n = (int)(Math.sqrt(2.0*t/5.0+1/4.0)-0.5);
		Answer ans = new Answer(Math.min(n, in.n));
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
