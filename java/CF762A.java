import java.io.PrintStream;
import java.util.Scanner;

public class CF762A {
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
		long n;
		int k;
		public Input(Scanner sc) {
			n = sc.nextLong();
			k = sc.nextInt();
		}
	};

	/**
	 * solver function
	 */
	public static Answer solve(Input in) {
		int k = in.k;
		long n = in.n;
		long i;
		long sq = (long)Math.sqrt(n);
		long res = 1;
		for (i=1; i<=sq+1 && k>0; i++) {
			if (n%i == 0) {
				k--;
				res = i;
			}
		}
		i--;
		for (; i>=1 && k>0; i--) {
			if (n%i == 0) {
				if (-sq+1+i <= 0)
					return new Answer(-1);
				k--;
				res = n/(-sq+1+i);
			}
		}
		if (k <= 0)
			return new Answer(res);
		else
			return new Answer(-1);
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
