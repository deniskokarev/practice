import java.io.PrintStream;
import java.util.Arrays;
import java.util.LinkedList;
import java.util.Queue;
import java.util.Scanner;

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

	static void mkg(int nnv, Pair ss[], int g[][]) {
		int ll[] = new int[nnv];
		Arrays.sort(ss, (Pair a, Pair b) -> (a.l - b.l));
		int s;
		int cnt;
		s = ss[0].l;
		cnt = 1;
		for (int i=1; i < ss.length; i++) {
			if (s != ss[i].l) {
				ll[s] += cnt;
				s = ss[i].l;
				cnt = 0;
			}
			cnt++;
		}
		ll[s] += cnt;
		Arrays.sort(ss, (Pair a, Pair b) -> (a.r - b.r));
		s = ss[0].r;
		cnt = 1;
		for (int i=1; i < ss.length; i++) {
			if (s != ss[i].r) {
				ll[s] += cnt;
				s = ss[i].r;
				cnt = 0;
			}
			cnt++;
		}
		ll[s] += cnt;
		for (int i=0; i<nnv; i++) 
			g[i] = new int[ll[i]];
		for (int i=0; i<ss.length; i++) {
			int l = ss[i].l;
			int r = ss[i].r;
			ll[l]--;
			g[l][ll[l]] = r;
			ll[r]--;
			g[r][ll[r]] = l;
		}
	}

	static int walkPart(int v, int g[][], int cc[], boolean vis[], int cht[]) {
		Queue<Integer> nodes = new LinkedList<>();
		nodes.add(v);
		int rc = 0;
		while (nodes.size() > 0) {
			v = nodes.remove();
			if (!vis[v]) {
				vis[v] = true;
				cht[cc[v]]++;
				rc++;
				for (int s:g[v])
					nodes.add(s);
			}
		}
		return rc;
	}
	
	/**
	 * solver function
	 */
	public static Answer solve(Input in) {
		int g[][] = new int[in.ns][];
		mkg(in.ns, in.ss, g);
		boolean vis[] = new boolean[g.length];
		int rc = 0;
		for (int i=0; i<in.ns; i++) {
			int cht[] = new int[in.nc];
			int cnt = walkPart(i, g, in.cc, vis, cht);
			if (cnt > 0) {
				int mxj = 0;
				for (int j=1; j<cht.length; j++)
					if (cht[mxj] < cht[j])
						mxj = j;
				rc += cnt-cht[mxj];
			}
		}
		Answer ans = new Answer(rc);
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
