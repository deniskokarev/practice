import java.io.PrintStream;
import java.util.Scanner;

public class CF755A {
	/**
	 * solution result
	 */
	public static class Answer {
		int n;
		public Answer(int n) {
			this.n = n;
		}

		@Override
		public String toString() {
			return Integer.toString(n);
		}
	};

	/**
	 * input parser
	 */
	public static class Input {
		int n;
		public Input(Scanner sc) {
			n = sc.nextInt();
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
	public static int primeFactors(int n, int p[]) {
		assert(n > 1);
		int np = 0;
		for (int i = 2; i <= n / i; i++) {
			while (n % i == 0) {
				p[np++] = i;
				n /= i;
			}
		}
		if (n > 1)
			p[np++] = n;
		return np;
	}
	/**
	 * solver function
	 */
	public static Answer solve(Input in) {
		int pp[] = new int[32];
		for (int m=1; m<=1000; m++) {
			if (primeFactors(m*in.n+1, pp) > 1)
				return new Answer(m);
		}
		return new Answer(-1);
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
