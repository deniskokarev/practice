import java.util.Arrays;
import java.util.Scanner;

/**
 * codeforces problem 149A
 * @author kokarev
 *
 *A. Business trip
time limit per test
2 seconds
memory limit per test
256 megabytes
input
standard input
output
standard output

What joy! Petya's parents went on a business trip for the whole year and the playful kid is left all by himself. Petya got absolutely happy. He jumped on the bed and threw pillows all day long, until...

Today Petya opened the cupboard and found a scary note there. His parents had left him with duties: he should water their favourite flower all year, each day, in the morning, in the afternoon and in the evening. "Wait a second!" — thought Petya. He know for a fact that if he fulfills the parents' task in the i-th (1 ≤ i ≤ 12) month of the year, then the flower will grow by ai centimeters, and if he doesn't water the flower in the i-th month, then the flower won't grow this month. Petya also knows that try as he might, his parents won't believe that he has been watering the flower if it grows strictly less than by k centimeters.

Help Petya choose the minimum number of months when he will water the flower, given that the flower should grow no less than by k centimeters.
Input

The first line contains exactly one integer k (0 ≤ k ≤ 100). The next line contains twelve space-separated integers: the i-th (1 ≤ i ≤ 12) number in the line represents ai (0 ≤ ai ≤ 100).
Output

Print the only integer — the minimum number of months when Petya has to water the flower so that the flower grows no less than by k centimeters. If the flower can't grow by k centimeters in a year, print -1.

 */
public class p149A {
	static void solve(Scanner sc) {
		long k = sc.nextLong();
		sc.nextLine();
		long a[] = new long[12];
		for (int i=0; i<a.length; i++)
			a[i] = sc.nextLong();
		long sA[] = new long[12];
		System.arraycopy(a, 0, sA, 0, 12);
		Arrays.sort(sA);
		int monCnt = 0;
		for (int i=sA.length-1; i>=0 && k>0; i--) {
			k -= sA[i];
			monCnt++;
		}
		if (k > 0)
			monCnt = -1;
		System.out.println(monCnt);		
	}
	
	public static void main(String[] args) {
		try (Scanner sc = new Scanner(System.in)) {
			solve(sc);
		}
	}
}
