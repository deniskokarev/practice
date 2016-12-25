import java.io.PrintStream;
import java.util.Scanner;
/**
 * http://codeforces.com/problemset/problem/748/A
 * A. Santa Claus and a Place in a Class
time limit per test
2 seconds
memory limit per test
256 megabytes
input
standard input
output
standard output

Santa Claus is the first who came to the Christmas Olympiad, and he is going to be the first to take his place at a desk! In the classroom there are n lanes of m desks each, and there are two working places at each of the desks. The lanes are numbered from 1 to n from the left to the right, the desks in a lane are numbered from 1 to m starting from the blackboard. Note that the lanes go perpendicularly to the blackboard, not along it (see picture).

The organizers numbered all the working places from 1 to 2nm. The places are numbered by lanes (i. e. all the places of the first lane go first, then all the places of the second lane, and so on), in a lane the places are numbered starting from the nearest to the blackboard (i. e. from the first desk in the lane), at each desk, the place on the left is numbered before the place on the right.
The picture illustrates the first and the second samples.

Santa Clause knows that his place has number k. Help him to determine at which lane at which desk he should sit, and whether his place is on the left or on the right!
Input

The only line contains three integers n, m and k (1 ≤ n, m ≤ 10 000, 1 ≤ k ≤ 2nm) — the number of lanes, the number of desks in each lane and the number of Santa Claus' place.
Output

Print two integers: the number of lane r, the number of desk d, and a character s, which stands for the side of the desk Santa Claus. The character s should be "L", if Santa Clause should sit on the left, and "R" if his place is on the right.
Examples
Input

4 3 9

Output

2 2 L

Input

4 3 24

Output

4 3 R

Input

2 4 4

Output

1 2 R

Note

The first and the second samples are shown on the picture. The green place corresponds to Santa Claus' place in the first example, the blue place corresponds to Santa Claus' place in the second example.

In the third sample there are two lanes with four desks in each, and Santa Claus has the fourth place. Thus, his place is in the first lane at the second desk on the right.
 * @author kokarev
 *
 */
public class CF748A {
	/**
	 * solution result
	 */
	public static class Answer {
		int lane, row;
		char side;
		public Answer(int l, int r, char s) {
			lane = l;
			row = r;
			side = s;
		}

		@Override
		public String toString() {
			return lane+" "+row+" "+side;
		}
	};

	/**
	 * input parser
	 */
	public static class Input {
		int lanes, rows, place;
		public Input(Scanner sc) {
			lanes = sc.nextInt();
			rows = sc.nextInt();
			place = sc.nextInt();
		}
	};

	/**
	 * solver function
	 */
	public static Answer solve(Input in) {
		int lane = (in.place-1) / (in.rows*2) + 1;
		int row = ((in.place-1) % (in.rows*2))/2 + 1;
		char side = ((in.place-1)%2==0)?'L':'R';
		Answer ans = new Answer(lane, row, side);
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
