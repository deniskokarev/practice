package dk.comb;

/**
 * common combinatorics formulas
 * @author kokarev
 *
 */
public class Comb {

	/**
	 * GCD(a, b) - greatest common divisor
	 * @param a
	 * @param b
	 * @return
	 */
	public static long gcd(long a, long b)	{
	    while (b > 0) {
	        long temp = b;
	        b = a % b;
	        a = temp;
	    }
	    return a;
	}

	/**
	 * LCM(a, b) - least common multiple
	 * @param a
	 * @param b
	 * @return
	 */
	public static long lcm(long a, long b)	{
	    return a * (b / gcd(a, b));
	}
	
	/**
	 * Binomial coefficient (choose n, k)
	 * @param n
	 * @param k
	 * @return
	 */
	public static long choose(int n, int k) {
		assert(k <= n);
		long res = 1;
		for (long i=n,j=1; j<=k; i--,j++) {
			res *= i;
			res /= j;
		}
		return res;
	}
	
	/**
	 * factorial n!
	 * @param n
	 * @return
	 */
	public static long fact(int n) {
		long res = 1;
		while (n>1)
			res *= n--;
		return res;
	}

}
