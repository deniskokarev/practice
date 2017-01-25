import java.io.PrintStream;
import java.util.Scanner;

public class CF762A {
	/**
	 * solution result
	 */
	public static class Answer {
		long n;
		public Answer(long n) {
			this.n = n;
		}

		@Override
		public String toString() {
			return Long.toString(n);
		}
	};

	/**
	 * input parser
	 */
	public static class Input {
		long n;
		int k;
		public Input(Scanner sc) {
			n = sc.nextLong();
			k = sc.nextInt();
		}
	};

	/**
	 * Naive prime number factorization in O(sqrt(N))
	 * @param n - number greater than that you want to factorize
	 * @param p[] - preallocated recipient array where the of ordered
	 *   prime numbers of n will be placed
	 * 	p.length >= 32
	 * @return number of populated primes in p[]
	 */
	public static int primeFactors(long n, long p[]) {
		assert(n > 1);
		int np = 0;
		for (long i = 2; i <= n / i; i++) {
			while (n % i == 0) {
				p[np++] = i;
				n /= i;
			}
		}
		if (n > 1)
			p[np++] = n;
		return np;
	}

	public static long factorsMul(long n, boolean mask[], long minFact) {
		long res = 1;
		int np = 1;
		for (long i = 2; i <= n / i; i++) {
			while (n % i == 0) {
				if (mask[np++])
					res *= i;
				n /= i;
			}
		}
		if (n > 1)
			if (mask[np++])
				res *= n;
		if (minFact > (1L << np))
			return -1;
		else
			return res;
	}

	/**
	 * solver function
	 */
	public static Answer solve(Input in) {
		int k = in.k;
		boolean mask[] = new boolean[32];
		int i = 0;
		while (k!=0) {
			if ((k & 1) == 1)
				mask[i] = true;
			else
				mask[i] = false;
			i++;
			k = (k >> 1);
		}
		return new Answer(factorsMul(in.n, mask, in.k));
	}

	/**
	 * standard executable mantra
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
