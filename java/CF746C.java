import java.io.PrintStream;
import java.util.Scanner;

public class CF746C {
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
		int s;
		int x1, x2;
		int t1, t2;
		int p, d;
		public Input(Scanner sc) {
			s = sc.nextInt();
			x1 = sc.nextInt();
			x2 = sc.nextInt();
			t1 = sc.nextInt();
			t2 = sc.nextInt();
			p = sc.nextInt();
			d = sc.nextInt();
		}
	};

	/**
	 * solver function
	 */
	public static Answer solve(Input in) {
		int self = Math.abs((in.x2-in.x1)*in.t2);
		int t;
		if (in.x2 < in.x1) {
			in.d = -in.d;
			in.p = in.s-in.p;
			in.x1 = in.s-in.x1;
			in.x2 = in.s-in.x2;
		}
		if (in.p < in.x1) {
			t = (in.x1-in.p*in.d+(in.x2-in.x1))*in.t1;
		} else {
			if (in.d < 0) {
				t = (in.x1-in.p*in.d+(in.x2-in.x1))*in.t1;					
			} else {
				t = (in.x1-in.p+in.s*2+(in.x2-in.x1))*in.t1;					
			}
		}
		return new Answer(Math.min(self, t));
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
