package dk.draft;
/**
 * compute E
 * exp(x) = 1+x+x^2/2!+x^3/3!+...
 * @author kokarev
 *
 */
public class E {

	public static void main(String[] args) {
		double tcaf = 1;	// 1/i!
		double e = 2;
		for (int i=2; i<18; i++) {
			tcaf /= i;
			e += tcaf;
		}
		System.out.println(e);
	}
}
