import java.io.PrintStream;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.ListIterator;
import java.util.Scanner;
/*
 * http://codeforces.com/problemset/problem/676/A
 * Nicholas has an array a that contains n distinct integers from 1 to n. In other words, Nicholas has a permutation of size n.

Nicholas want the minimum element (integer 1) and the maximum element (integer n) to be as far as possible from each other. He wants to perform exactly one swap in order to maximize the distance between the minimum and the maximum elements. The distance between two elements is considered to be equal to the absolute difference between their positions.

Input
The first line of the input contains a single integer n (2 ≤ n ≤ 100) — the size of the permutation.

The second line of the input contains n distinct integers a1, a2, ..., an (1 ≤ ai ≤ n), where ai is equal to the element at the i-th position.

Output
Print a single integer — the maximum possible distance between the minimum and the maximum elements Nicholas can achieve by performing exactly one swap.
 */
public class CF676A {
	/**
	 * solution result
	 */
	public static class Answer {
		public int score;
		public Answer(int score) {
			this.score = score;
		}
		@Override
		public String toString() {
			return Integer.toString(score);
		}
	};

	/**
	 * input parser
	 */
	public static class Input {
		public int n;
		public List<Integer> a;
		public Input(Scanner in) {
			a = new ArrayList<>();
			n = in.nextInt();
			for (int i=0; i<n; i++)
				a.add(in.nextInt());
		}
	};

	/**
	 * solver function
	 */
	public static Answer solve(Input in) {
		ListIterator<Integer> i = in.a.listIterator();
		int minpos = 0, maxpos = 0;
		int min = i.next();
		int max = min;
		int pos;
		for (pos=1; i.hasNext(); pos++) {
			int el = i.next();
			if (el > max) {
				maxpos = pos;
				max = el;
			} else if (el < min) {
				minpos = pos;
				min = el;
			}
		}
		int p[] = new int[]{minpos, maxpos};
		Arrays.sort(p);
		int score = Math.max(p[1], in.n-p[0]-1);
		Answer ans = new Answer(score);
		return ans;
	}

	/**
	 * standard executable mantra
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
