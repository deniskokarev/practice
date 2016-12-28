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
		int na = (qA > 0) ? (in.a+qA-1)/qA : 0; 
		int nb = (qB > 0) ? (in.b+qB-1)/qB : 0;
		if (qB>qA) {
			int a, b;
			if (nb>0) {
				for (b=0; b<in.b/nb; b++)
					for (int j=0; j<nb; j++)
						res[b*(na+nb)+j] = 'B';
				for (int j=0; j<in.b%nb; j++)
					res[b*(na+nb)+j] = 'B';
			}
			if (na>0) {
				for (a=0; a<in.a/na; a++)
					for (int j=0; j<na; j++)
						res[a*(na+nb)+nb+j] = 'G';
				for (int j=0; j<in.a%na; j++)
					res[a*(na+nb)+nb+j] = 'G';
			}
		} else {
			int a, b;
			if (na>0) {
				for (a=0; a<in.a/na; a++)
					for (int j=0; j<na; j++)
						res[a*(na+nb)+j] = 'G';
				for (int j=0; j<in.a%na; j++)
					res[a*(na+nb)+j] = 'G';
			}
			if (nb>0) {
				for (b=0; b<in.b/nb; b++)
					for (int j=0; j<nb; j++)
						res[b*(na+nb)+na+j] = 'B';
				for (int j=0; j<in.b%nb; j++)
					res[b*(na+nb)+na+j] = 'B';
			}
		}
		return new String(res);
	}

	/**
	 * solver function
	 */
	public static Answer solve(Input in) {
		// number of a intervals has to be between (in.a+in.k-1)/in.k and in.a
		// number of b intervals has to be between (in.b+in.k-1)/in.k and in.b
		// need to find an interval count that is within +-1
		int qAMin = (in.a+in.k-1)/in.k;
		int qAMax = in.a;
		int qBMin = (in.b+in.k-1)/in.k;
		int qBMax = in.b;
		char res[] = new char[in.n];
		if (qAMin>qBMin && qAMax<qBMax) {
			//   <-a->
			// <---b--->
			int qA = qAMin;
			int qB = qAMin;
			return new Answer(fill(res, qA, qB, in));
		} else if (qBMin>qAMin && qBMax<qAMax) {
			// <---a--->
			//   <-b->
			int qA = qBMin;
			int qB = qBMin;
			return new Answer(fill(res, qA, qB, in));
		} else if (qBMax+1>=qAMin && qAMax>qBMin) {
			// <--b-->
			//        <--a-->
			int qA = qAMin;
			int qB = qBMax;
			return new Answer(fill(res, qA, qB, in));
		} else if (qAMax+1>=qBMin && qBMax>qAMin) {
			// <--a-->
			//        <--b-->
			int qA = qAMax;
			int qB = qBMin;
			return new Answer(fill(res, qA, qB, in));
		} else {
			return new Answer("NO");
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
