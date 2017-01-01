import java.io.PrintStream;
import java.util.Scanner;

public class CF743B {
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
		int n;
		long k;
		public Input(Scanner sc) {
			n = sc.nextInt();
			k = sc.nextLong();
		}
	};
	
	static int mid(int n, long k) {
		if (k == (1L<<(n-1)))
			return n;
		else if (k > (1L<<(n-1)))
			k = (1L<<n)-k;
		return mid(n-1, k);
	}
	
	/**
	 * solver function
	 */
	public static Answer solve(Input in) {
		Answer ans = new Answer(mid(in.n, in.k));
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
