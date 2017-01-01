import java.io.PrintStream;
import java.util.Scanner;
/**
 * http://codeforces.com/problemset/problem/746/B
 * @author kokarev
 *
 */

public class CF746B {
	/**
	 * solution result
	 */
	public static class Answer {
		String a;
		public Answer(String a) {
			this.a = a;
		}

		@Override
		public String toString() {
			return a;
		}
	};

	/**
	 * input parser
	 */
	public static class Input {
		String s;
		public Input(Scanner sc) {
			sc.nextInt();
			sc.nextLine();
			s = sc.nextLine();
		}
	};

	/**
	 * solver function
	 */
	public static Answer solve(Input in) {
		char s[] = in.s.toCharArray();
		char d[] = new char[in.s.length()];
		int sz = d.length;
		int i;
		int j;
		i = sz-1;
		j = i;
		while (i>=sz/2) {
			d[i] = s[j];
			i -= 1;
			j -= 2;
		}
		i = 0;
		j = sz-2;
		while (i<sz/2) {
			d[i] = s[j];
			i += 1;
			j -= 2;
		}
		Answer ans = new Answer(new String(d));
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
