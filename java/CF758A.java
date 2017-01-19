import java.io.PrintStream;
import java.util.Scanner;

public class CF758A {
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
		int n;
		int a[];
		int mn, mx, sum;
		public Input(Scanner sc) {
			n = sc.nextInt();
			a = new int[n];
			mn = Integer.MAX_VALUE;
			mx = Integer.MIN_VALUE;
			sum = 0;
			for (int i=0; i<n; i++) {
				a[i] = sc.nextInt();
				mn = Math.min(mn,  a[i]);
				mx = Math.max(mx,  a[i]);
				sum += a[i];
			}
				
		}
	};

	/**
	 * solver function
	 */
	public static Answer solve(Input in) {
		Answer ans = new Answer(in.mx*in.n-in.sum);
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
