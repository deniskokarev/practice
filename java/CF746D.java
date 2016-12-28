import java.io.PrintStream;
import java.util.Scanner;
/**
 * http://codeforces.com/problemset/problem/746/D
 * @author kokarev
 *
 */
public class CF746D {
	/**
	 * solution result
	 */
	public static class Answer {
		String s;
		public Answer(String s) {
			this.s = s;
		}

		@Override
		public String toString() {
			return s;
		}
	};

	/**
	 * input parser
	 */
	public static class Input {
		int n, k, a, b;
		public Input(Scanner sc) {
			n = sc.nextInt();
			k = sc.nextInt();
			a = sc.nextInt();
			b = sc.nextInt();
		}
	};
	
	/**
	 * fill the string with qA and qB intervals of 'G' and 'B' letters respectively
	 * qA and qB may not differ by more than 1
	 * @param qA 'G' letter intervals
	 * @param qB 'B' letter intervals
	 * @param a total number of 'G' letters
	 * @param b total number of 'B' letters
	 * @return that filled string
	 */
	static String fill(int qA, int qB, int a, int b) {
		// upper estimate of letters in the interval
		int v[] = new int[]{(qA > 0) ? (a+qA-1)/qA : 0, (qB > 0) ? (b+qB-1)/qB : 0};
		// number of intervals we have to fill with v[] letters
		// after which we have to start filling with one letter less
		int r[] = new int[]{(qA > 0) ? a%qA : 0, (qB > 0) ? b%qB : 0};
		char c[] = new char[]{'G', 'B'};
		int go = (qB>qA) ? 1 : 0;	// what sequence do we start with
		char res[] = new char[a+b];
		int cnt = 0;
		while (cnt < res.length) {
			for (int i=0; i<v[go]; i++)
				res[cnt++] = c[go];
			if (r[go] > 0) {
				r[go]--;
				if (r[go] == 0)
					v[go]--;
			}
			go ^= 1;
		}
		return new String(res);
	}

	/**
	 * solver function
	 */
	public static Answer solve(Input in) {
		// number of a intervals has to be between (in.a+in.k-1)/in.k and in.a
		// number of b intervals has to be between (in.b+in.k-1)/in.k and in.b
		// need to find an overlapping count satisfying both within +-1 tolerance
		int qAMin = (in.a+in.k-1)/in.k;
		int qAMax = in.a;
		int qBMin = (in.b+in.k-1)/in.k;
		int qBMax = in.b;
		if (qAMin < qBMin) {
			if (qBMax<=qAMax) {
				// <---a--->
				//  <--b-->
				return new Answer(fill(qBMin, qBMin, in.a, in.b));
			} else if (qBMin<=qAMax) {
				// <--a-->
				//     <--b-->
				return new Answer(fill(qBMin, qBMin, in.a, in.b));
			} else if (qBMin==qAMax+1) {
				// <--a-->
				//        <--b-->
				return new Answer(fill(qAMax, qBMin, in.a, in.b));
			} else {
				// <--a-->
				//          <--b-->
				return new Answer("NO");
			}
		} else {
			if (qAMax<=qBMax) {
				//  <--a-->
				// <---b--->
				return new Answer(fill(qAMin, qAMin, in.a, in.b));
			} else if (qAMin<=qBMax) {
				//     <--a-->
				// <--b-->
				return new Answer(fill(qAMin, qAMin, in.a, in.b));
			} else if (qAMin==qBMax+1) {
				//        <--a-->
				// <--b-->
				return new Answer(fill(qAMin, qBMax, in.a, in.b));
			} else {
				//          <--a-->
				// <--b-->
				return new Answer("NO");
			}
		}
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
