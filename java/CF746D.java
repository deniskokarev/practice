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
		int qA = (in.a+in.k-1)/in.k;
		int qB = in.b;
		char res[] = new char[in.n];
		while (qA <= in.a && qB >=(in.b+in.k-1)/in.k) {
			int na = (qA > 0) ? in.a/qA : 0; 
			int nb = (qB > 0) ? in.b/qB : 0;
			if (qB-qA==1) {
				int a, b;
				for (b=0; b<qB; b++)
					for (int j=0; j<nb; j++)
						res[b*(na+nb)+j] = 'B';
				for (int j=0; j<in.b%nb; j++)
					res[b*(na+nb)+j] = 'B';
				for (a=0; a<qA; a++)
					for (int j=0; j<na; j++)
						res[a*(na+nb)+nb+j] = 'G';
				for (int j=0; j<in.a%na; j++)
					res[a*(na+nb)+nb+j] = 'G';
				return new Answer(new String(res));
			} else if (qA-qB==1 || qA==qB) {
				int a, b;
				for (a=0; a<qA; a++)
					for (int j=0; j<na; j++)
						res[a*(na+nb)+j] = 'G';
				for (int j=0; j<in.a%na; j++)
					res[a*(na+nb)+j] = 'G';
				for (b=0; b<qB; b++)
					for (int j=0; j<nb; j++)
						res[b*(na+nb)+na+j] = 'B';
				for (int j=0; j<in.b%nb; j++)
					res[b*(na+nb)+na+j] = 'B';
				return new Answer(new String(res));
			}
			qA++;
			qB--;
		}
		return new Answer("NO");
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
