import java.io.PrintStream;
import java.util.LinkedList;
import java.util.List;
import java.util.Scanner;

/**
 * http://codeforces.com/problemset/problem/727/A
 * @author kokarev
 *Vasily has a number a, which he wants to turn into a number b. For this purpose, he can do two types of operations:

multiply the current number by 2 (that is, replace the number x by 2·x);
append the digit 1 to the right of current number (that is, replace the number x by 10·x + 1).
You need to help Vasily to transform the number a into the number b using only the operations described above, or find that it is impossible.

Note that in this task you are not required to minimize the number of operations. It suffices to find any way to transform a into b.

Input
The first line contains two positive integers a and b (1 ≤ a < b ≤ 109) — the number which Vasily has and the number he wants to have.

Output
If there is no way to get b from a, print "NO" (without quotes).

Otherwise print three lines. On the first line print "YES" (without quotes). The second line should contain single integer k — the length of the transformation sequence. On the third line print the sequence of transformations x1, x2, ..., xk, where:

x1 should be equal to a,
xk should be equal to b,
xi should be obtained from xi - 1 using any of two described operations (1 < i ≤ k).
If there are multiple answers, print any of them.

Examples
input
2 162
output
YES
5
2 4 8 81 162 
input
4 42
output
NO
 */

public class CF727A {
	/**
	 * solution result
	 */
	public static class Answer {
		boolean rc;
		List<Long> steps;
		public Answer() {
			rc = false;
			steps = new LinkedList<>();
		}

		@Override
		public String toString() {
			StringBuffer sb = new StringBuffer();
			if (rc) {
				sb.append("YES\n");
				for (Long i:steps) {
					sb.append(i);
					sb.append(" ");
				}
			} else {
				sb.append("NO");
			}
			return sb.toString();
		}
	};

	/**
	 * input parser
	 */
	public static class Input {
		long from, to;
		public Input(Scanner sc) {
			from = sc.nextLong();
			to = sc.nextLong();
		}
	};

	/**
	 * solver function
	 */
	public static Answer solve(Input in) {
		Answer ans = new Answer();
		long v = in.to;
		long last = -1;
		while (v > in.from) {
			last = v;
			ans.steps.add(0, v);
			if (v%2 == 0) {
				v /= 2;
			} else {
				v = (v-1)/10;
			}
		}
		if (v == in.from && (in.from*2 == last || in.from*10+1 == last)) {
			ans.rc = true;
			ans.steps.add(0, in.from);
		}
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
