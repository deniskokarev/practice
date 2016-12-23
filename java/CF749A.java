import java.io.PrintStream;
import java.util.Scanner;

public class CF749A {
	/**
	 * solution result
	 */
	public static class Answer {
		int n2;
		int n3;
		public Answer(int n2, int n3) {
			this.n2 = n2;
			this.n3 = n3;
		}

		@Override
		public String toString() {
			StringBuffer sb = new StringBuffer(Integer.toString(n2+n3));
			sb.append('\n');
			for (int i=0; i<n2; i++)
				sb.append("2 ");
			for (int i=0; i<n3; i++)
				sb.append("3 ");
			sb.append('\n');
			return sb.toString();
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
		int n2;
		int n3;
		if (in.n%2 == 0) {
			n2 = in.n/2;
			n3 = 0;
		} else {
			n3 = 1;
			n2 = (in.n-3)/2;
		}
		Answer ans = new Answer(n2, n3);
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
