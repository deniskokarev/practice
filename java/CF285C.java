import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

/*
 * http://codeforces.com/problemset/problem/285/C?locale=en
 * 
Permutation p is an ordered set of integers p1,  p2,  ...,  pn, consisting of n distinct positive integers, each of them doesn't exceed n. We'll denote the i-th element of permutation p as pi. We'll call number n the size or the length of permutation p1,  p2,  ...,  pn.

You have a sequence of integers a1, a2, ..., an. In one move, you are allowed to decrease or increase any number by one. Count the minimum number of moves, needed to build a permutation from this sequence.

Input
The first line contains integer n (1 ≤ n ≤ 3·105) — the size of the sought permutation. The second line contains n integers a1, a2, ..., an ( - 109 ≤ ai ≤ 109).

Output
Print a single number — the minimum number of moves.

Please, do not use the %lld specifier to read or write 64-bit integers in С++. It is preferred to use the cin, cout streams or the %I64d specifier.

Examples
input
2
3 0
output
2
input
3
-1 -1 2
output
6

 */
public class CF285C {

	static long solve(int n, List<Integer> a) {
		long cnt = 0;
		List<Integer> sorted = new ArrayList<>(a);
		sorted.sort(null);
		long i = 1;
		for (long el:sorted) {
			cnt += Math.abs(el-i);
			i++;
		}
		return cnt;
	}
	
	static void proc(Scanner sc) {
		int n = sc.nextInt();
		List<Integer> a = new ArrayList<>();
		for (int i=0; i<n; i++)
			a.add(sc.nextInt());
		System.out.println(solve(n,a));
	}
	
	public static void main(String[] args) {
		try (Scanner sc = new Scanner(System.in)) {
			proc(sc);
		}
	}

}
