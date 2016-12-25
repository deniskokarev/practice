import java.io.PrintStream;
import java.util.Scanner;
/**
 * http://codeforces.com/problemset/problem/748/C
 * C. Santa Claus and Robot
time limit per test
2 seconds
memory limit per test
256 megabytes
input
standard input
output
standard output

Santa Claus has Robot which lives on the infinite grid and can move along its lines. He can also, having a sequence of m points p1, p2, ..., pm with integer coordinates, do the following: denote its initial location by p0. First, the robot will move from p0 to p1 along one of the shortest paths between them (please notice that since the robot moves only along the grid lines, there can be several shortest paths). Then, after it reaches p1, it'll move to p2, again, choosing one of the shortest ways, then to p3, and so on, until he has visited all points in the given order. Some of the points in the sequence may coincide, in that case Robot will visit that point several times according to the sequence order.

While Santa was away, someone gave a sequence of points to Robot. This sequence is now lost, but Robot saved the protocol of its unit movements. Please, find the minimum possible length of the sequence.
Input

The first line of input contains the only positive integer n (1 ≤ n ≤ 2·105) which equals the number of unit segments the robot traveled. The second line contains the movements protocol, which consists of n letters, each being equal either L, or R, or U, or D. k-th letter stands for the direction which Robot traveled the k-th unit segment in: L means that it moved to the left, R — to the right, U — to the top and D — to the bottom. Have a look at the illustrations for better explanation.
Output

The only line of input should contain the minimum possible length of the sequence.
Examples
Input

4
RURD

Output

2

Input

6
RRULDD

Output

2

Input

26
RRRULURURUULULLLDLDDRDRDLD

Output

7

Input

3
RLL

Output

2

Input

4
LRLR

Output

4
 * @author kokarev
 *
 */

public class CF748C {
	/**
	 * solution result
	 */
	public static class Answer {
		int cnt;
		public Answer(int cnt) {
			this.cnt = cnt;
		}

		@Override
		public String toString() {
			return Integer.toString(cnt);
		}
	};

	static class Dir implements Cloneable {
		int x, y;
		Dir(int x, int y) {
			this.x = x;
			this.y = y;
		}
	}
	
	/**
	 * input parser
	 */
	public static class Input {
		int ndir;
		Dir dir[];
		public Input(Scanner sc) {
			ndir = sc.nextInt();
			sc.nextLine();
			String ln = sc.nextLine();
			dir = new Dir[ln.length()];
			int i = 0;
			for (char c:ln.toCharArray()) {
				switch (c) {
				case 'R':
					dir[i] = new Dir(1, 0);
					break;
				case 'U':
					dir[i] = new Dir(0, 1);
					break;
				case 'L':
					dir[i] = new Dir(-1, 0);
					break;
				case 'D':
					dir[i] = new Dir(0, -1);
					break;
				}
				i++;
			}
		}
	};
	
	static int canMoveMonoFrom(Input in, int i) {
		Dir d[] = in.dir;
		int dX = 0;
		int dY = 0;
		while (i < d.length && dX * d[i].x >= 0 && dY * d[i].y >= 0) {
			if (d[i].x != 0)
				dX = d[i].x;
			if (d[i].y != 0)
				dY = d[i].y;
			i++;
		};
		return i;
	}

	/**
	 * solver function
	 */
	public static Answer solve(Input in) {
		int i = 0;
		int j;
		int cnt = 0;
		while ((j = canMoveMonoFrom(in, i)) > 0 && j < in.ndir) {
			i = j;
			cnt++;
		}
		Answer ans = new Answer(cnt+1);
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
