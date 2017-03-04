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
		long n;
		public Answer(long n) {
			this.n = n;
		}

		@Override
		public String toString() {
			return Long.toString(n);
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
		int ns, nt;
		Map<Integer, Map<Integer, BoxInt>> st;	// row->(type->cnt)
		public Input(Scanner sc) {
			ns = sc.nextInt();
			nt = sc.nextInt();
			st = new HashMap<>();
			for (int i=0; i<ns; i++) {
				Map<Integer,BoxInt> g = new HashMap<>();
				st.put(i, g);
				int p = sc.nextInt();
				for (int j=0; j<p; j++) {
					int t = sc.nextInt();
					BoxInt bi = g.get(t);
					if (bi == null) {
						bi = new BoxInt(0);
						g.put(t, bi);
					}
					bi.inc();
				}
			}
		}
	};
	
	// mm will get common arcs from v -> (chl1, chl2)
	static void aggrTypes(Map<Integer, BoxInt> sc, Map<Integer, Set<Integer>> mm, List<Set<Integer>> allSets) {
		Map<Integer, Set<Integer>> hist = new HashMap<>();
		for (int t:sc.keySet()) {
			int v = sc.get(t).n;
			Set<Integer> s = hist.get(v);
			if (s == null) {
				s = new HashSet<>();
				hist.put(v, s);
			}
			s.add(t);
		}
		for (Set<Integer> connTypes:hist.values()) {
			Set<Integer> ct = new HashSet<>(connTypes);
			allSets.add(ct);
			for (int t:connTypes) {
				Set<Integer> prior = mm.get(t); 
				if (prior == null) {
					mm.put(t, ct);
				} else {
					Set<Integer> joined = new HashSet<>(connTypes);
					joined.retainAll(prior);
					allSets.add(joined);
					for (int t1:joined)
						mm.put(t1, joined);
					ct.removeAll(prior);
					prior.removeAll(connTypes);
				}
			}
		}
	}
	
	/**
	 * solver function
	 */
	public static Answer solve(Input in) {
		Map<Integer, Set<Integer>> mm = new HashMap<>();
		List<Set<Integer>> allSets = new LinkedList<>();
		for (int i=0; i<in.ns; i++)
			aggrTypes(in.st.get(i), mm, allSets);
		for (int t=1; t<=in.nt; t++)
			System.out.println("type: "+t+" connected: "+mm.get(t));
		long cnt = 1;
		for (Set<Integer> s:allSets) {
			System.out.println("set: "+s);
			for (long i=2; i<=s.size(); i++) {
				cnt *= i;
				cnt %= 1000000007;
			}
		}
		return new Answer(cnt);
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
