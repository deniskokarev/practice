package dk.draft;

import java.util.Scanner;

/**
 * compute a square root
 * @author kokarev
 *
 */
public class Sqrt {

	/**
	 * use taylor (mclaren) sequence
	 * f(x) = f(1)*(x-1)+f'(1)*(1/2!)*(x-1)^2+f"(1)*(1/3!)*(x-1)^3
	 * @param sc
	 */
	static void process(Scanner sc) {
		double x = sc.nextDouble();
		x -= 1.0;
		double nxt = x/2.0;
		double result = 1.0+nxt;
		for (int i=2; i<1000; i++) {
			nxt *= x;
			nxt *= ((i-1.0)*2.0)-1.0;
			nxt *= -1.0;
			nxt /= 2.0;
			nxt /= i;
			result += nxt;
		}
		System.out.printf("%f\n", result);
	}
	public static void main(String[] args) {
		try (Scanner sc = new Scanner(System.in)) {
			process(sc);
		}
	}

}
