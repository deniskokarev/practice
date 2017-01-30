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
		long sr = (long)Math.sqrt(n);
		int nd = 1;
		for (i=2; i<=sr; i++)
			if (n%i == 0)
				nd++;
		int all;
		if ((i-1)*(i-1)==n)
			all = 2*nd-1;
		else
			all = 2*nd;
		if (all < k) {
			return new Answer(-1);
		} else {
			long res;
			if (k>=nd) {
				res = 1;
				k = all+1-k;
				for (i=1; i<=sr; i++) {
					if (n%i == 0) {
						res = i;
						k--;
						if (k == 0)
							return new Answer(n/res); 
					}
				}
			} else {
				res = 1;
				for (i=1; i<=sr; i++) {
					if (n%i == 0) {
						res = i;
						k--;
						if (k == 0)
							return new Answer(res); 
					}
				}
			}
		}
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
