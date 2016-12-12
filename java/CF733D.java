import java.io.PrintStream;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.Scanner;


/**
 * http://codeforces.com/problemset/problem/733/D
Kostya is a genial sculptor, he has an idea: to carve a marble sculpture in the shape of a sphere. Kostya has a friend Zahar who works at a career. Zahar knows about Kostya's idea and wants to present him a rectangular parallelepiped of marble from which he can carve the sphere.

Zahar has n stones which are rectangular parallelepipeds. The edges sizes of the i-th of them are ai, bi and ci. He can take no more than two stones and present them to Kostya.

If Zahar takes two stones, he should glue them together on one of the faces in order to get a new piece of rectangular parallelepiped of marble. Thus, it is possible to glue a pair of stones together if and only if two faces on which they are glued together match as rectangles. In such gluing it is allowed to rotate and flip the stones in any way.

Help Zahar choose such a present so that Kostya can carve a sphere of the maximum possible volume and present it to Zahar.

Input
The first line contains the integer n (1 ≤ n ≤ 105).

n lines follow, in the i-th of which there are three integers ai, bi and ci (1 ≤ ai, bi, ci ≤ 109) — the lengths of edges of the i-th stone. Note, that two stones may have exactly the same sizes, but they still will be considered two different stones.

Output
In the first line print k (1 ≤ k ≤ 2) the number of stones which Zahar has chosen. In the second line print k distinct integers from 1 to n — the numbers of stones which Zahar needs to choose. Consider that stones are numbered from 1 to n in the order as they are given in the input data.

You can print the stones in arbitrary order. If there are several answers print any of them.

Examples
input
6
5 5 5
3 2 4
1 4 1
2 1 3
3 2 4
3 3 4
output
1
1
input
7
10 7 8
5 10 3
4 2 6
5 5 5
10 2 8
4 2 1
7 7 7
output
2
1 5
 * 
 * @author kokarev
 *
 */
public class CF733D {

	static class Block3D {
		public int i, x, y, z;
		public Block3D(int i, int x, int y, int z) {
			this.i = i;
			int a[] = {x,y,z};
			Arrays.sort(a);
			this.x = a[0];
			this.y = a[1];
			this.z = a[2];
		}
	};

	static class Answer {
		public int k;	// 1,2
		public int n[];
		public int maxDia;
		public Answer(int k, int maxDia, int... n) {
			this.k = k;
			this.maxDia = maxDia;
			this.n = n;
		}
		boolean replaceIfBetter(int k, int maxDia, int... n) {
			if (this.maxDia < maxDia) {
				this.k = k;
				this.maxDia = maxDia;
				this.n = n;
				return true;
			} else {
				return false;
			}
		}
		@Override
		public String toString() {
			StringBuffer sb = new StringBuffer(k+"\n");
			int i;
			for (i=0; i<k-1; i++) {
				sb.append(n[i]);
				sb.append(" ");
			}
			sb.append(n[i]);
			return sb.toString();
		}
	};

	static int min(int... n) {
		int minEl = n[0];
		for (int el:n) {
			if (minEl > el)
				minEl = el;
		}
		return minEl;
	}
	
	static Answer solve(List<Block3D> blocks) {
		Map<String,Block3D> rot = new HashMap<>();
		Answer ans = new Answer(-1, Integer.MIN_VALUE, 0);
		// join by X
		for (Block3D el:blocks) {
			String key = el.y + ":" + el.z;
			Block3D prev = rot.get(key);
			if (prev == null) {
				ans.replaceIfBetter(1, el.x, el.i);
				rot.put(key, el);
			} else {
				int minSide = min(prev.x+el.x, el.y, el.z);
				ans.replaceIfBetter(2, minSide, el.i, prev.i);
				if (el.x > prev.x)
					rot.put(key, el);
			}
		}
		// join by Y
		for (Block3D el:blocks) {
			String key = el.x + ":" + el.z;
			Block3D prev = rot.get(key);
			if (prev == null) {
				ans.replaceIfBetter(1, el.x, el.i);
				rot.put(key, el);
			} else {
				int minSide = min(el.x, prev.y+el.y, el.z);
				ans.replaceIfBetter(2, minSide, el.i, prev.i);
				if (el.y > prev.y)
					rot.put(key, el);
			}
		}
		// join by Z
		for (Block3D el:blocks) {
			String key = el.x + ":" + el.y;
			Block3D prev = rot.get(key);
			if (prev == null) {
				ans.replaceIfBetter(1, el.x, el.i);
				rot.put(key, el);
			} else {
				int minSide = min(el.x, el.y, prev.z+el.z);
				ans.replaceIfBetter(2, minSide, el.i, prev.i);
				if (el.z > prev.z)
					rot.put(key, el);
			}
		}
		return ans;
	}
	
	public static void proc(Scanner sc, PrintStream out) {
		long n = sc.nextInt();
		List<Block3D> b = new ArrayList<>();
		for (int i=0; i<n; i++) {
			int x = sc.nextInt();
			int y = sc.nextInt();
			int z = sc.nextInt();
			b.add(new Block3D(i+1,x,y,z));
		}
		out.println(solve(b));
	}
	
	public static void main(String[] args) {
		try (Scanner sc = new Scanner(System.in)) {
			proc(sc, System.out);
		}
	}
}
