import java.io.PrintStream;
import java.util.Scanner;

public class CF742A {
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
		public Input(Scanner sc) {
			n = sc.nextInt();
		}
	};

	static int powLastDig(int d, int p) {
		if (p>1) {
			int d1 = powLastDig(d, p>>1);
			if (p%2 == 0)
				return (d1*d1)%10;
			else
				return (d1*d1*d)%10;
		} else if (p == 1) {
			return d;
		} else {
			return 1;
		}
	}
	
	/**
	 * solver function
	 */
	public static Answer solve(Input in) {
		Answer ans = new Answer(powLastDig(8, in.n));
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
