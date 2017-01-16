import java.io.PrintStream;
import java.util.Arrays;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Map;
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
	 * FIFO ringbuffer of ints
	 * sz should be 1 greater of what you want to store
	 * @author kokarev
	 */
	static class FifoInt {
		int head, tail;
		int sz;
		int emptyInd;	// what do we return if our Q is empty
		int buf[];
		FifoInt(int sz) {
			this(sz, -1);
		}
		FifoInt(int sz, int emptyInd) {
			this.emptyInd = emptyInd;
			this.sz = sz;
			buf = new int[sz];
		}
		int size() {
			return (head+sz-tail)%sz;
		}
		int avail() {
			return sz-size();
		}
		boolean put(int v) {
			int n = (head+1)%sz; 
			if (n != tail) {
				buf[head] = v;
				head = n;
				return true;
			} else {
				return false;
			}
		}
		int get() {
			if (tail != head) {
				int v = buf[tail];
				tail = (tail+1)%sz;
				return v;
			} else {
				return emptyInd;
			}
		}
	}

	/**
	 * Take a graph and return list of its connected components
	 * @param graph is given as a list of edges where graph[i][?] == j denotes edge i->j
	 * @return list of connected components meaning [n][v] - vertice v belongs to connected component number n 
	 */
	static int[][] connectedComponents(int graph[][]) {
		final int EMPTY = -1;
		FifoInt q = new FifoInt(graph.length+1, EMPTY);
		int vis[] = new int[graph.length];
		int cnts[] = new int[graph.length+1];
		int cnt = 0;
		for (int p=0; p<graph.length; p++) {
			if (vis[p] == 0) {
				cnt++;
				q.put(p);
				for (int v = q.get(); v != EMPTY; v = q.get()) {
					if (vis[v] == 0) {
						vis[v] = cnt;
						cnts[cnt]++;
						for (int c:graph[v])
							q.put(c);
					}
				}
			}
		}
		int res[][] = new int[cnt][];
		for (int i=0; i<res.length; i++)
			res[i] = new int[cnts[i+1]];
		Arrays.fill(cnts, 0);
		int c;
		for (int p=0; p<graph.length; p++) {
			c = vis[p]-1; 
			res[c][cnts[c]++] = p;
		}
		return res;
	}

	/**
	 * solver function
	 */
	public static Answer solve(Input in) {
		Answer ans = new Answer(connectedComponents(graph(in.pp)).length);
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
