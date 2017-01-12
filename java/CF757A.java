import java.io.PrintStream;
import java.util.Scanner;

public class CF757A {
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
		String s;
		public Input(Scanner sc) {
			s = sc.nextLine();
		}
	};

	static class CCpair {
		char c;
		int n;
		CCpair(char c, int n) {
			this.c = c;
			this.n = n;
		}
	}
	/**
	 * solver function
	 */
	public static Answer solve(Input in) {
		int cc[] = new int[256];
		for (char c:in.s.toCharArray()) {
			cc[c]++;
		}
//		B - 1
//		u - 2
//		l - 1
//		b - 1
//		a - 2
//		r - 1
		CCpair pp[] = new CCpair[]{new CCpair('B', 1), new CCpair('u', 2), new CCpair('l', 1), new CCpair('b', 1), new CCpair('a', 2), new CCpair('r', 1)};
		int n = Integer.MAX_VALUE;
		for (CCpair cp:pp)
			n = Math.min(cc[cp.c]/cp.n, n);
		if (n == Integer.MAX_VALUE)
			n = 0;
		Answer ans = new Answer(n);
		return ans;
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
