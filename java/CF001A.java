import java.io.PrintStream;
import java.util.Scanner;

public class CF001A {
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
		int n, m, a;
		public Input(Scanner sc) {
			n = sc.nextInt();
			m = sc.nextInt();
			a = sc.nextInt();
		}
	};

	/**
	 * solver function
	 */
	public static Answer solve(Input in) {
		long h = (in.n+in.a-1)/in.a;
		long w = (in.m+in.a-1)/in.a;
		Answer ans = new Answer(h*w);
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
