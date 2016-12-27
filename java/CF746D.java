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
	 * solver function
	 */
	public static Answer solve(Input in) {
		char res[] = new char[in.n];
		int qAMin = in.a/in.k-1;
		int qBMin = in.b/in.k-1;
		res[0] = 'N';
		res[1] = 'O';
		res[2] = 0;
		for (int q=Math.max(qAMin, qBMin); q<=Math.min(in.a, in.b); q++) {
			if (q < 1)
				continue;
			int na = in.a/q;
			int nb = in.b/q;
			if (na < 1 || na > in.k || nb < 1 || nb > in.k)
				continue;
			int qB = q;
			int qA = q;
			if (in.b%q > 0)
				qB++;
			if (in.a%q > 0)
				qA++;
			if (qB>qA) {
				// begin with B
				int cnt;
				cnt = 0;
				for (int i=0; i<qB && cnt<in.b; i++) {
					for (int j=0; j<nb && cnt<in.b; j++) {
						res[i*(na+nb)+j] = 'B';
						cnt++;
					}
				}
				cnt = 0;
				for (int i=0; i<qA && cnt<in.a; i++) {
					for (int j=0; j<na && cnt<in.a; j++) {
						res[i*(na+nb)+nb+j] = 'G';
						cnt++;
					}
				}
			} else {
				// begin with A
				int cnt;
				cnt = 0;
				for (int i=0; i<qA && cnt<in.a; i++) {
					for (int j=0; j<na && cnt<in.a; j++) {
						res[i*(na+nb)+j] = 'G';
						cnt++;
					}
				}
				cnt = 0;
				for (int i=0; i<qB && cnt<in.b; i++) {
					for (int j=0; j<nb && cnt<in.b; j++) {
						res[i*(na+nb)+na+j] = 'B';
						cnt++;
					}
				}
			}
		}
		return new Answer(new String(res));
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
