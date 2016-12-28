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
	
	static String fill(char res[], int qA, int qB, Input in) {
		int n[] = new int[]{in.a, in.b};
		// upper estimate of letters in interval
		int v[] = new int[]{(qA > 0) ? (in.a+qA-1)/qA : 0, (qB > 0) ? (in.b+qB-1)/qB : 0};
		// number of intervals we have to fill with v[] letters
		// after which we have to start filling with one letter less
		int o[] = new int[]{(qA > 0) ? in.a%qA : 0, (qB > 0) ? in.b%qB : 0};
		char c[] = new char[]{'G', 'B'};
		int go;
		if (qB>qA)
			go = 1;
		else
			go = 0;
		int cnt = 0;
		while (cnt < in.n) {
			for (int i=0; i<v[go] && n[go]>0; i++) {
				res[cnt++] = c[go];
				n[go]--;
			}
			if (o[go] > 0) {
				o[go]--;
				if (o[go] == 0)
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
		// need to find an overlapping interval within +-1
		int qAMin = (in.a+in.k-1)/in.k;
		int qAMax = in.a;
		int qBMin = (in.b+in.k-1)/in.k;
		int qBMax = in.b;
		char res[] = new char[in.n];
		if (qAMin < qBMin) {
			if (qBMax<=qAMax) {
				// <---a--->
				//  <--b-->
				int qA = qBMin;
				int qB = qBMin;
				return new Answer(fill(res, qA, qB, in));
			} else if (qBMin<=qAMax) {
				// <--a-->
				//     <--b-->
				int qA = qBMin;
				int qB = qBMin;
				return new Answer(fill(res, qA, qB, in));
			} else if (qBMin==qAMax+1) {
				// <--a-->
				//        <--b-->
				int qA = qAMax;
				int qB = qBMin;
				return new Answer(fill(res, qA, qB, in));
			} else {
				// <--a-->
				//          <--b-->
				return new Answer("NO");
			}
		} else {
			if (qAMax<=qBMax) {
				//  <--a-->
				// <---b--->
				int qA = qAMin;
				int qB = qAMin;
				return new Answer(fill(res, qA, qB, in));
			} else if (qAMin<=qBMax) {
				//     <--a-->
				// <--b-->
				int qA = qAMin;
				int qB = qAMin;
				return new Answer(fill(res, qA, qB, in));
			} else if (qAMin==qBMax+1) {
				//        <--a-->
				// <--b-->
				int qA = qAMin;
				int qB = qBMax;
				return new Answer(fill(res, qA, qB, in));
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
