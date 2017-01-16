import java.io.PrintStream;
import java.util.Arrays;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Map;
import java.util.Scanner;
import java.util.Set;

public class CF731C {
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

	static class Pair {
		int l, r;
		int cc[];
		Pair(int l, int r, int cc[]) {
			this.l = Math.min(l, r);
			this.r = Math.max(l, r);
			this.cc = cc;
		}
	}

	/**
	 * input parser
	 */
	public static class Input {
		int ns;
		int nc;
		int cc[];
		Pair ss[];

		public Input(Scanner sc) {
			ns = sc.nextInt();
			int np = sc.nextInt();
			nc = sc.nextInt();
			cc = new int[ns];
			for (int i = 0; i < ns; i++)
				cc[i] = sc.nextInt()-1;
			ss = new Pair[np];
			for (int i = 0; i < np; i++)
				ss[i] = new Pair(sc.nextInt() - 1, sc.nextInt() - 1, cc); // assert<s
		}
	};

	static int[][] mkGraph(Pair ss[], int nv) {
		Map<Integer, Set<Integer>> gg = new HashMap<>();
		for (int p=0; p<ss.length; p++) {
			Set<Integer> cf = gg.get(ss[p].l);
			if (cf == null) {
				cf = new HashSet<>();
				gg.put(ss[p].l, cf);
			}
			Set<Integer> cr = gg.get(ss[p].r);
			if (cr == null) {
				cr = new HashSet<>();
				gg.put(ss[p].r, cr);
			}
			cf.add(ss[p].r);
			cr.add(ss[p].l);
		}
		int res[][] = new int[nv][];
		for (int p:gg.keySet()) {
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
	static class FifoQInt {
		int head, tail;
		int sz;
		int emptyInd;	// special value that we return if our Q is empty
		int buf[];
		
		FifoQInt(int sz) {
			this(sz, -1);
		}
		FifoQInt(int sz, int emptyInd) {
			this.emptyInd = emptyInd;
			this.sz = sz;
			buf = new int[sz];
		}
		int size() {
			return (head+sz-tail)%sz;
		}
		int avail() {
			return sz-size()-1;
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
		FifoQInt q = new FifoQInt(graph.length+1, EMPTY);
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
						if (graph[v] != null)
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
	
	static class BoxInt {
		int n;
		BoxInt(int n) {
			this.n = n;
		}
	}
	
	/**
	 * solver function
	 */
	public static Answer solve(Input in) {
		if (in.ss.length > 0) {
			int graph[][] = mkGraph(in.ss, in.cc.length);
			int cc[][] = connectedComponents(graph);
			int cnt = 0;
			for (int i=0; i<cc.length; i++) {
				int c[] = cc[i];
				if (c != null) {
					int mxColCnt = 0;
					Map<Integer, BoxInt> colors = new HashMap<>(); // color -> count
					for (int j=0; j<c.length; j++) {
						int col = in.cc[c[j]];
						BoxInt ccnt = colors.get(col);
						if (ccnt == null) {
							ccnt = new BoxInt(0);
							colors.put(col, ccnt);
						}
						ccnt.n++;
						if (ccnt.n > mxColCnt)
							mxColCnt = ccnt.n;
					}
					cnt += c.length - mxColCnt;
				}
			}
			return new Answer(cnt);
		} else {
			return new Answer(0);
		}
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
