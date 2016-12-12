package den.comb;

/**
 * compute Pi
 * @author kokarev
 *
 */
public class Pi {
	/**
	 * computing Pi via inverse square sequence which adds up to Pi^2/6
	 * @param args
	 */
	static double calcPi() {
		double res = 1.0;
		for (double  d=2.0; d<999999.9; d += 1.0)
			res += 1.0/(d*d);
		return Math.sqrt(res*6.0);
	}
	
	public static double Pi = calcPi();
	
	public static void main(String[] args) {
		System.out.printf("Pi = %.8f\n", Pi);
	}
}
