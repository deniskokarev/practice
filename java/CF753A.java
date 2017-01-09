import java.io.PrintStream;
import java.util.Scanner;

public class CF753A {
	/**
	 * solution result
	 */
	public static class Answer {
		int n;
		int k[];
		public Answer(int n, int k[]) {
			this.n = n;
			this.k = k;
		}

		@Override
		public String toString() {
			StringBuffer sb = new StringBuffer(Integer.toString(n));
			sb.append('\n');
			for (int i=0; i<k.length; i++) {
				sb.append(k[i]);
				sb.append(' ');
			}
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
		int n = (int)(Math.sqrt(0.25+2.0*in.n)-0.5);
		int k[] = new int[n];
		int i;
		for (i=0; i<n-1; i++)
			k[i] = i+1;
		k[i] = i+1+(in.n-(n*(n+1)/2));
		Answer ans = new Answer(n, k);
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
