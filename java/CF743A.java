import java.io.PrintStream;
import java.util.Arrays;
import java.util.Scanner;
/**
 * http://codeforces.com/contest/743/problem/A
 * Vladik is a competitive programmer. This year he is going to win the International Olympiad in Informatics. But it is not as easy as it sounds: the question Vladik face now is to find the cheapest way to get to the olympiad.

Vladik knows n airports. All the airports are located on a straight line. Each airport has unique id from 1 to n, Vladik's house is situated next to the airport with id a, and the place of the olympiad is situated next to the airport with id b. It is possible that Vladik's house and the place of the olympiad are located near the same airport.

To get to the olympiad, Vladik can fly between any pair of airports any number of times, but he has to start his route at the airport a and finish it at the airport b.

Each airport belongs to one of two companies. The cost of flight from the airport i to the airport j is zero if both airports belong to the same company, and |i - j| if they belong to different companies.

Print the minimum cost Vladik has to pay to get to the olympiad.

Input
The first line contains three integers n, a, and b (1 ≤ n ≤ 105, 1 ≤ a, b ≤ n) — the number of airports, the id of the airport from which Vladik starts his route and the id of the airport which he has to reach.

The second line contains a string with length n, which consists only of characters 0 and 1. If the i-th character in this string is 0, then i-th airport belongs to first company, otherwise it belongs to the second.

Output
Print single integer — the minimum cost Vladik has to pay to get to the olympiad.

Examples
input
4 1 4
1010
output
1
input
5 5 2
10110
output
0
 * @author kokarev
 *
 */


public class CF743A {
	/**
	 * solution result
	 */
	public static class Answer {
		int rc;
		public Answer(int rc) {
			this.rc = rc;
		}

		@Override
		public String toString() {
			return Integer.toString(rc);
		}
	};

	/**
	 * input parser
	 */
	public static class Input {
		int n;
		int a;
		int b;
		char aport[];
		public Input(Scanner sc) {
			n = sc.nextInt();
			a = sc.nextInt();
			b = sc.nextInt();
			sc.nextLine();
			String s = sc.nextLine();
			aport = s.toCharArray();
		}
	};

	/**
	 * solver function
	 */
	public static Answer solve(Input in) {
		int rc;
		if (in.aport[in.a-1] == in.aport[in.b-1])
			rc = 0;
		else
			rc = 1;
		return new Answer(rc);
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
