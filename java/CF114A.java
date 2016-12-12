import java.util.Scanner;

/**
 * 
 * http://codeforces.com/problemset/problem/114/A
When Petya went to school, he got interested in large numbers and what they were called in ancient times. For instance, he learned that the Russian word "tma" (which now means "too much to be counted") used to stand for a thousand and "tma tmyschaya" (which literally means "the tma of tmas") used to stand for a million.

Petya wanted to modernize the words we use for numbers and invented a word petricium that represents number k. Moreover, petricium la petricium stands for number k2, petricium la petricium la petricium stands for k3 and so on. All numbers of this form are called petriciumus cifera, and the number's importance is the number of articles la in its title.

Petya's invention brought on a challenge that needed to be solved quickly: does some number l belong to the set petriciumus cifera? As Petya is a very busy schoolboy he needs to automate the process, he asked you to solve it.

Input
The first input line contains integer number k, the second line contains integer number l (2 ≤ k, l ≤ 231 - 1).

Output
You should print in the first line of the output "YES", if the number belongs to the set petriciumus cifera and otherwise print "NO". If the number belongs to the set, then print on the seconds line the only number — the importance of number l.

 * @author kokarev
 *
 */

public class CF114A {
	/**
	 * Chk if l is a power of k and if so find this power
	 * @param k
	 * @param l
	 * @return n, where k^n==l
	 */
	static int intLogK(long k, long l) {
		// don't bother with binary search over multiplication/comparison
		long r = 0;
		int p = 0;
		while (l>1) {
			r = l%k;
			if (r > 0) {
				p = -1;
				break;
			}
			l /= k;
			p++;
		}
		return p;
	}
	static void printAnsw(int n) {
		if (n >= 0) {
			System.out.println("YES");
			System.out.println(n);			
		} else {
			System.out.println("NO");
		}
	}
	static void proc(Scanner sc) {
		long k = sc.nextLong();
		long l = sc.nextLong();
		if (k <= 1) {
			printAnsw(-1);
		} else if (l<k) {
			printAnsw(-1);
		} else {
			printAnsw(intLogK(k, l)-1);
		}
	}
	public static void main(String[] args) {
		try (Scanner sc = new Scanner(System.in)) {
			proc(sc);
		}
	}
}
