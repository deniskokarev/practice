import java.io.PrintStream;
import java.math.BigInteger;
import java.util.Scanner;

public class ACMP146 {
	/**
	 * solution result
	 */
	public static class Answer {
		BigInteger ans;
		public Answer(BigInteger a) {
			ans = a;
		}

		@Override
		public String toString() {
			return ans.toString();
		}
	};

	/**
	 * input parser
	 */
	public static class Input {
		BigInteger a;
		public Input(Scanner sc) {
			a = sc.nextBigInteger();
		}
	};

	/**
	 * solver function
	 */
	public static Answer solve(Input in) {
		BigInteger f = BigInteger.ONE;
		BigInteger t = in.a;
		BigInteger TWO = new BigInteger("2");
		while (f.compareTo(t) < 0) {
			BigInteger m = f.add(t).divide(TWO);
			BigInteger sq = m.multiply(m);
			if (sq.compareTo(in.a) < 0) {
				f = m.add(BigInteger.ONE);
			} else {
				t = m;
			}
		}
		if (f.multiply(f).compareTo(in.a) > 0)
			f = f.subtract(BigInteger.ONE);
		Answer ans = new Answer(f);
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
