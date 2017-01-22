import java.io.PrintStream;
import java.util.Scanner;

public class CF760A {
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
		int m, d;
		public Input(Scanner sc) {
			m = sc.nextInt()-1;
			d = sc.nextInt()-1;
		}
	};

	final static int daysMon[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	
	/**
	 * solver function
	 */
	public static Answer solve(Input in) {
		int r = (daysMon[in.m]-(7-in.d)+6)/7+1;
		Answer ans = new Answer(r);
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
