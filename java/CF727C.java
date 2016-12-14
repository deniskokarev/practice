import java.io.PrintStream;
import java.util.Scanner;

/*
 * http://codeforces.com/contest/743/problem/C
 * Vladik and Chloe decided to determine who of them is better at math. Vladik claimed that for any positive integer n he can represent fraction  as a sum of three distinct positive fractions in form .

Help Vladik with that, i.e for a given n find three distinct positive integers x, y and z such that . Because Chloe can't check Vladik's answer if the numbers are large, he asks you to print numbers not exceeding 109.

If there is no such answer, print -1.

Input
The single line contains single integer n (1 ≤ n ≤ 104).

Output
If the answer exists, print 3 distinct numbers x, y and z (1 ≤ x, y, z ≤ 109, x ≠ y, x ≠ z, y ≠ z). Otherwise print -1.

If there are multiple answers, print any of them.

Examples
input
3
output
2 7 42
input
7
output
7 8 56

 */
public class CF727C {
	/**
	 * solution result
	 */
	public static class Answer {
		long x, y, z;
		public Answer() {
			this.z = Long.MAX_VALUE;
		}
		public Answer(long x, long y, long z) {
			this.x = x;
			this.y = y;
			this.z = z;
		}

		@Override
		public String toString() {
			StringBuffer sb = new StringBuffer();
			if (z <= 1000000000) {
				sb.append(x);
				sb.append(" ");
				sb.append(y);
				sb.append(" ");
				sb.append(z);
			} else {
				sb.append(-1);
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
	 * 1/n = 1/(n+k)+k/(n(n+k))
	 * k == 1 gives us solution
	 * 1/n = 1/(n+1)+1/((n*(n+1)))
	 */
	public static Answer solve(Input in) {
		long n = in.n;
		Answer ans;
		if (n > 1)
			ans = new Answer(n, n+1, n*(n+1));
		else
			ans = new Answer(); // no answer
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
