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
		int tramAtX1[] = new int[] {(in.x1 - in.p*in.d)*in.t1, (in.x1 - in.p*in.d + 2*(in.s-in.x1))*in.t1};
		int tramAtX2[] = new int[] {(in.x2 - in.p*in.d)*in.t1, (in.x2 - in.p*in.d + 2*(in.s-in.x2))*in.t1};
		if (tramAtX1[0]<tramAtX2[0]) {
			return new Answer(Math.min(self, tramAtX2[0]));
		} else {
			return new Answer(Math.min(self, tramAtX2[1]));
		}
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
