package dk.draft;

import java.util.Scanner;
import dk.alg.Comb;

/**
 * Shift an array by n positions to the right
 * Use in-place shifting
 * @author kokarev
 *
 */

public class Shift {

	/**
	 * in-place array shifting
	 * @param a
	 * @return
	 */
	public static char[] shift(char a[], int step) {
		int gcd = (int) Comb.gcd(a.length, step);
		int lenOverGCD = a.length/gcd;
		int p = 0;
		for (int s=0; s<gcd; s++) {
			char c = a[p];
			for (int i=0; i<lenOverGCD; i++) {
				int pn = (p+step)%a.length;
				char b = a[pn]; 
				a[pn] = c;
				c = b;
				p = pn;
			}
			p++;
		}
		return a;
	}
	
	public static void main(String[] args) {
		try (Scanner sc = new Scanner(System.in)) {
			String s = sc.nextLine();
			int pos = sc.nextInt();
			String result = new String(shift(s.toCharArray(), pos));
			System.out.println(result);
		}
	}

}
