import java.io.PrintStream;
import java.util.ArrayList;
import java.util.LinkedList;
import java.util.List;
import java.util.Scanner;

public class CF742B {
	/**
	 * solution result
	 */
	public static class Answer {
		int n;
		public Answer(int n) {
			this.n = n;
		}

		@Override
		public String toString() {
			return Integer.toString(n);
		}
	};

	/**
	 * input parser
	 */
	public static class Input {
		int n;
		int x;
		int a[];
		public Input(Scanner sc) {
			n = sc.nextInt();
			x = sc.nextInt();
			a = new int[n];
			for (int i=0; i<n; i++)
				a[i] = sc.nextInt();
		}
	};

	/**
	 * solver function
	 */
	public static Answer solve(Input in) {
		ArrayList<List<Integer>> idx = new ArrayList<>();
		for (int i=0; i<100001; i++)
			idx.add(null);
		for (int i=0; i<in.a.length; i++) {
			List<Integer> l = idx.get(in.a[i]);
			if (l == null) {
				l = new LinkedList<>();
				idx.set(in.a[i], l);
			}
			l.add(i);
		}
		int cnt = 0;
		for (int i=0; i<in.a.length; i++) {
			List<Integer> l;
			int xor = in.x^in.a[i];
			if (xor < 100000) {
				l = idx.get(xor);
				if (l != null) {
					for (int j:l)
						if (j>i)
							cnt++;
				}
			}
			l = idx.get(in.a[i]);
			l.remove(0);
		}
		Answer ans = new Answer(cnt);
		return ans;
	}

	/**
	 * standard CodeForces executable mantra
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
