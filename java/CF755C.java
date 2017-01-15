import java.io.PrintStream;
import java.util.HashMap;
import java.util.HashSet;
import java.util.LinkedList;
import java.util.Map;
import java.util.Queue;
import java.util.Scanner;
import java.util.Set;

public class CF755C {
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
		int pp[];
		public Input(Scanner sc) {
			n = sc.nextInt();
			pp = new int[n];
			for (int i=0; i<n; i++)
				pp[i] = sc.nextInt()-1;
		}
	};

	static int[][] graph(int pp[]) {
		Map<Integer, Set<Integer>> gg = new HashMap<>();
		for (int p=0; p<pp.length; p++) {
			Set<Integer> cf = gg.get(p);
			if (cf == null) {
				cf = new HashSet<>();
				gg.put(p, cf);
			}
			Set<Integer> cr = gg.get(pp[p]);
			if (cr == null) {
				cr = new HashSet<>();
				gg.put(pp[p], cr);
			}
			cf.add(pp[p]);
			cr.add(p);
		}
		int res[][] = new int[gg.size()][];
		for (int p=0; p<pp.length; p++) {
			int l = gg.get(p).size();
			res[p] = new int[l];
			int i = 0;
			for (int c:gg.get(p))
				res[p][i++] = c;
		}
		return res;
	}
	
	/**
	 * solver function
	 */
	public static Answer solve(Input in) {
		Queue<Integer> q = new LinkedList<>();
		boolean vis[] = new boolean[in.pp.length];
		int gg[][] = graph(in.pp);
		int cnt = 0;
		for (int p=0; p<in.pp.length; p++) {
			if (!vis[p]) {
				cnt++;
				q.clear();
				q.add(p);
				while (q.size() > 0) {
					int v = q.remove();
					if (!vis[v]) {
						vis[v] = true;
						for (int c:gg[v])
							q.add(c);
					}
				}
			}
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
