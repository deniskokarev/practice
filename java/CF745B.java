import java.io.PrintStream;
import java.util.Scanner;

public class CF745B {
	/**
	 * solution result
	 */
	public static class Answer {
		boolean b;
		public Answer(boolean b) {
			this.b = b;
		}

		@Override
		public String toString() {
			return b?"YES":"NO";
		}
	};

	/**
	 * input parser
	 */
	public static class Input {
		int n, m;
		byte p[][];
		int xcnt;
		public Input(Scanner sc) {
			n = sc.nextInt();
			m = sc.nextInt();
			sc.nextLine();
			p = new byte[n][m];
			for (int i=0; i<n; i++) {
				String s = sc.nextLine();
				char c[] = s.toCharArray();
				for (int j=0; j<m; j++) {
					if (c[j] == 'X') {
						p[i][j] = 1;
						xcnt++;
					}
				}
			}
		}
	};

	/**
	 * solver function
	 */
	public static Answer solve(Input in) {
		int xmn = Integer.MAX_VALUE, xmx = Integer.MIN_VALUE;
		int ymn = Integer.MAX_VALUE, ymx = Integer.MIN_VALUE;
		boolean rc = false;
		for (int y=0; y<in.p.length; y++) {
			for (int x=0; x<in.p[y].length; x++) {
				if (in.p[y][x] == 1) {
					xmn = Math.min(xmn, x);
					xmx = Math.max(xmx, x);
					ymn = Math.min(ymn, y);
					ymx = Math.max(ymx, y);
					rc = true;
				}
			}
		}
		Answer ans = new Answer(rc && (in.xcnt == (xmx-xmn+1)*(ymx-ymn+1)));
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
