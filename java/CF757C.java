import java.io.PrintStream;
import java.util.HashMap;
import java.util.HashSet;
import java.util.LinkedList;
import java.util.List;
import java.util.ListIterator;
import java.util.Map;
import java.util.Queue;
import java.util.Scanner;
import java.util.Set;
import java.util.stream.Collectors;

public class CF757C {
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

	static class BoxInt {
		int n;
		BoxInt(int n) {
			this.n = n;
		}
		void inc() {
			n++;
		}
	}
	/**
	 * input parser
	 */
	public static class Input {
		int n, m;
		Map<Integer, Map<Integer, BoxInt>> gg;	// row->(type->cnt)
		public Input(Scanner sc) {
			n = sc.nextInt();
			m = sc.nextInt();
			gg = new HashMap<>();
			for (int i=0; i<n; i++) {
				Map<Integer,BoxInt> g = new HashMap<>();
				gg.put(i, g);
				int p = sc.nextInt();
				for (int j=0; j<p; j++) {
					int t = sc.nextInt();
					BoxInt bi = g.get(t);
					if (bi == null) {
						bi = new BoxInt(0);
						g.put(t,  bi);
					}
					bi.inc();
				}
			}
		}
	};
	
	// mm will get common arcs from v -> (chl1, chl2)
	static void doGraph(Map<Integer, BoxInt> row, Map<Integer, Set<Integer>> mm) {
		Map<Integer, Set<Integer>> hist = new HashMap<>();
		for (int k:row.keySet()) {
			int v = row.get(k).n;
			Set<Integer> s = hist.get(v);
			if (s == null) {
				s = new HashSet<>();
				hist.put(v, s);
			}
			s.add(k);
		}
		for (int cnt:hist.keySet()) {
			List<Integer> vv = hist.get(cnt).stream().sorted().collect(Collectors.toList());
			for (int v:vv) {
				Set<Integer> prior = mm.get(v); 
				if (prior == null) {
					prior = new HashSet<>(vv);
					mm.put(v, prior);
				}
				prior.retainAll(vv);
			}
		}
	}
	
	// connected component counts
	static List<Integer> doCluster(Map<Integer, Set<Integer>> mm, int nv) {
		List<Integer> rc = new LinkedList<>();
		boolean vis[] = new boolean[nv];
		List<Integer> vv = new LinkedList<>(mm.keySet());
		while (vv.size()>0) {
			int f = vv.remove(0);
			int cnt = 0;
			Set<Integer> cn = mm.get(f);
			if (cn != null) {
				for (int c:cn) {
					if (!vis[c]) {
						vis[c] = true;
						cnt++;
					}
				}
			}
			if (cnt > 1)
				rc.add(cnt);
		}
		return rc;
	}
	
	/**
	 * solver function
	 */
	public static Answer solve(Input in) {
		Map<Integer, Set<Integer>> mm = new HashMap<>();
		for (int i=0; i<in.n; i++) {
			doGraph(in.gg.get(i), mm);
			List<Integer> a = doCluster(mm, in.m+1);
			System.out.println("line: "+i);
			for (int n:a)
				System.out.println(n);
		}
		Answer ans = new Answer(-1);
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
