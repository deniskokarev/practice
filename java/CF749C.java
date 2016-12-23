import java.io.PrintStream;
import java.util.LinkedList;
import java.util.List;
import java.util.Scanner;

/**
 * http://codeforces.com/problemset/problem/749/C
 * 
C. Voting
time limit per test
1 second
memory limit per test
256 megabytes
input
standard input
output
standard output

There are n employees in Alternative Cake Manufacturing (ACM). They are now voting on some very important question and the leading world media are trying to predict the outcome of the vote.

Each of the employees belongs to one of two fractions: depublicans or remocrats, and these two fractions have opposite opinions on what should be the outcome of the vote. The voting procedure is rather complicated:

    Each of n employees makes a statement. They make statements one by one starting from employees 1 and finishing with employee n. If at the moment when it's time for the i-th employee to make a statement he no longer has the right to vote, he just skips his turn (and no longer takes part in this voting).
    When employee makes a statement, he can do nothing or declare that one of the other employees no longer has a right to vote. It's allowed to deny from voting people who already made the statement or people who are only waiting to do so. If someone is denied from voting he no longer participates in the voting till the very end.
    When all employees are done with their statements, the procedure repeats: again, each employees starting from 1 and finishing with n who are still eligible to vote make their statements.
    The process repeats until there is only one employee eligible to vote remaining and he determines the outcome of the whole voting. Of course, he votes for the decision suitable for his fraction. 

You know the order employees are going to vote and that they behave optimal (and they also know the order and who belongs to which fraction). Predict the outcome of the vote.
Input

The first line of the input contains a single integer n (1 ≤ n ≤ 200 000) — the number of employees.

The next line contains n characters. The i-th character is 'D' if the i-th employee is from depublicans fraction or 'R' if he is from remocrats.
Output

Print 'D' if the outcome of the vote will be suitable for depublicans and 'R' if remocrats will win.
Examples
Input

5
DDRRR

Output

D

Input

6
DDRRRR

Output

R

Note

Consider one of the voting scenarios for the first sample:

    Employee 1 denies employee 5 to vote.
    Employee 2 denies employee 3 to vote.
    Employee 3 has no right to vote and skips his turn (he was denied by employee 2).
    Employee 4 denies employee 2 to vote.
    Employee 5 has no right to vote and skips his turn (he was denied by employee 1).
    Employee 1 denies employee 4.
    Only employee 1 now has the right to vote so the voting ends with the victory of depublicans. 


 * @author kokarev
 *
 */
public class CF749C {
	/**
	 * solution result
	 */
	public static class Answer {
		char winner;
		public Answer(char w) {
			winner = w;
		}

		@Override
		public String toString() {
			return Character.toString(winner);
		}
	};

	/**
	 * input parser
	 */
	public static class Input {
		int n;
		String in;
		public Input(Scanner sc) {
			n = sc.nextInt();
			sc.nextLine();
			in = sc.nextLine();
		}
	};
	
	static char oppositeParty(char p) {
		switch(p) {
		case 'R':
			return 'D';
		case 'D':
			return 'R';
		default:
			return ' ';
		}
	}

	static int findFirst(byte where[], int from, byte what) {
		int sz = where.length;
		for (int i=0; i<sz; i++)
			if (where[(from+i)%sz] == what)
				return (from+i)%sz;
		return -1;
	}
	
	static class GraphNode {
		char party;		// R or D
		int selfNext;
		int oppositeNext;
		public GraphNode(char p) {
			party = p;
			selfNext = -1;
			oppositeNext = -1;
		}
	}
	
	static GraphNode[] buildGraph(String in) {
		int sz = in.length();
		GraphNode g[] = new GraphNode[sz];
		List<Integer> rq = new LinkedList<>();
		List<Integer> dq = new LinkedList<>();
		int lastR = -1;
		int lastD = -1;
		for (int j=0; j<2*sz; j++) {
			int i = j%sz;
			switch(in.charAt(i)) {
			case 'R':
				if (g[i] == null)
					g[i] = new GraphNode('R');
				if (dq.size() > 0) {
					if (g[dq.get(0)].oppositeNext == -1)
						g[dq.get(0)].oppositeNext = i;
					dq.remove(0);
				}
				if (lastR >= 0)
					g[lastR].selfNext = i;
				rq.add(i);
				lastR = i;
				break;
			case 'D':
				if (g[i] == null)
					g[i] = new GraphNode('D');
				if (rq.size() > 0) {
					if (g[rq.get(0)].oppositeNext == -1)
						g[rq.get(0)].oppositeNext = i;
					rq.remove(0);
				}
				if (lastD >= 0)
					g[lastD].selfNext = i;
				dq.add(i);
				lastD = i;
				break;
			}
		}
		return g;
	}
	/**
	 * solver function
	 */
	public static Answer solve(Input in) {
		char winner = '-';
		GraphNode ring[] = buildGraph(in.in);
		System.out.println("DEBUG:");
		for (GraphNode g:ring)
			System.out.println(g.party+":"+g.selfNext+":"+g.oppositeNext);
		int sz = ring.length;
		vote: while (true) {
			for (int i=0; i<sz; i++) {
				GraphNode g = ring[i];
				if (g.party == ' ')
					continue;
				int on = g.oppositeNext;
				ring[on].party = ' ';
				g.oppositeNext = ring[on].selfNext;
				break vote;
			}
		}
		Answer ans = new Answer(winner);
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
