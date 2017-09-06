import java.io.PrintStream;
import java.math.BigInteger;
import java.util.Scanner;

public class ACMP146 {
//public class Main { // ACMP requirement
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

	static String repeatZero(int n) {
		return new String(new char[n]).replace("\0", "0");
	}
	
	/**
	 * solver function
	 */
	public static Answer solve(Input in) {
		final BigInteger TWO = new BigInteger("2");
		String sa = in.a.toString();
		BigInteger x = new BigInteger("1"+repeatZero((sa.length()+1)/2));
		BigInteger d = BigInteger.ZERO;
		do {
			x = x.subtract(d);
			d = x.subtract(in.a.divide(x)).divide(TWO);
		} while(d.compareTo(BigInteger.ZERO)>0);
		if (x.multiply(x).compareTo(in.a)>0)
			x = x.subtract(BigInteger.ONE);
		Answer ans = new Answer(x);
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
