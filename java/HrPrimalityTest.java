/* https://www.hackerrank.com/challenges/java-primality-test */
import java.math.BigInteger;
import java.util.Scanner;

public class HrPrimalityTest {

	public static void main(String[] args) {
		try (Scanner sc = new Scanner(System.in)) {
			String sn = sc.nextLine();
			BigInteger n = new BigInteger(sn);
			if (n.isProbablePrime(256))
				System.out.println("prime");
			else
				System.out.println("not prime");
		}
	}

}
