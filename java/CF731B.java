import java.io.PrintStream;
import java.util.Scanner;

/**
 * http://codeforces.com/contest/731/problem/B
 * The programming competition season has already started and it's time to train for ICPC. Sereja coaches his teams for a number of year and he knows that to get ready for the training session it's not enough to prepare only problems and editorial. As the training sessions lasts for several hours, teams become hungry. Thus, Sereja orders a number of pizzas so they can eat right after the end of the competition.

Teams plan to train for n times during n consecutive days. During the training session Sereja orders exactly one pizza for each team that is present this day. He already knows that there will be ai teams on the i-th day.

There are two types of discounts in Sereja's favourite pizzeria. The first discount works if one buys two pizzas at one day, while the second is a coupon that allows to buy one pizza during two consecutive days (two pizzas in total).

As Sereja orders really a lot of pizza at this place, he is the golden client and can use the unlimited number of discounts and coupons of any type at any days.

Sereja wants to order exactly ai pizzas on the i-th day while using only discounts and coupons. Note, that he will never buy more pizzas than he need for this particular day. Help him determine, whether he can buy the proper amount of pizzas each day if he is allowed to use only coupons and discounts. Note, that it's also prohibited to have any active coupons after the end of the day n.

Input
The first line of input contains a single integer n (1 ≤ n ≤ 200 000) — the number of training sessions.

The second line contains n integers a1, a2, ..., an (0 ≤ ai ≤ 10 000) — the number of teams that will be present on each of the days.

Output
If there is a way to order pizzas using only coupons and discounts and do not buy any extra pizzas on any of the days, then print "YES" (without quotes) in the only line of output. Otherwise, print "NO" (without quotes).

Examples
input
4
1 2 1 2
output
YES
input
3
1 0 1
output
NO
 * @author kokarev
 *
 */

public class CF731B {
	/**
	 * solution result
	 */
	public static class Answer {
		boolean ans;
		public Answer(boolean ans) {
			this.ans = ans;
		}

		@Override
		public String toString() {
			return (ans)?"YES":"NO";
		}
	};

	/**
	 * input parser
	 */
	public static class Input {
		public int ndays;
		public int team[];
		public Input(Scanner sc) {
			ndays = sc.nextInt();
			team = new int[ndays];
			for (int i=0; i<ndays; i++)
				team[i] = sc.nextInt();
		}
	};

	/**
	 * solver function
	 */
	public static Answer solve(Input in) {
		int odd = 0;
		for (int i:in.team) {
			if (odd != 0 && i < 1)
				break;
			odd = (odd+i%2)%2;
		}
		Answer ans = new Answer((odd%2) == 0);
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
