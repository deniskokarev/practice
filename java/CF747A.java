import java.io.PrintStream;
import java.util.Scanner;

public class CF747A {
	/**
	 * solution result
	 */
	public static class Answer {
		long r, d;
		public Answer(long r, long d) {
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
		long d = 0;
		long r = -1;
		while (d < in.n) {
			r = (long)(Math.sqrt(d*d/4.0+in.n)-d/2.0);
			if (r*(r+d) == in.n)
				break;
			d++;
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
