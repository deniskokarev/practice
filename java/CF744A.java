import java.io.PrintStream;
import java.util.Scanner;

public class CF744A {
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

	static class Arc {
		int i, j;
		Arc(int i, int j) {
			this.i = i;
			this.j = j;
		}
	}
	
	/**
	 * input parser
	 */
	public static class Input {
		int n, m, k;
		int c[];
		Arc a[];
		int neigh[][]; // neight[n][0] - number of neighbors for node n
		int leftovers;
		int leftover_conn;
		boolean isc[]; // is capital
		public Input(Scanner sc) {
			n = sc.nextInt();
			m = sc.nextInt();
			k = sc.nextInt();
			c = new int[k];
			isc = new boolean[n];
			for (int i=0; i<k; i++) {
				c[i] = sc.nextInt()-1;
				isc[c[i]] = true;
			}
			a = new Arc[m];
			neigh = new int[n][n+1];
			for (int ai=0; ai<m; ai++) {
				a[ai] = new Arc(sc.nextInt()-1, sc.nextInt()-1);
				int n;
				n = neigh[a[ai].i][0]++;
				neigh[a[ai].i][n+1] = a[ai].j;
				n = neigh[a[ai].j][0]++;
				neigh[a[ai].j][n+1] = a[ai].i;
			}
			calcUnconnectedNodes(this);
		}
	};

	
	static void calcUnconnectedNodes(Input in) {
		int visited[] = new int[in.n];
		for (int i=0; i<in.k; i++)
			allNeigh(visited, in.c[i], in.neigh);
		for (int i=0; i<in.n; i++) {
			if (visited[i] == 0) {
				in.leftovers++;
				in.leftover_conn += in.neigh[i][0];
			}
		}
		in.leftover_conn /= 2;
	}
	
	static int allNeigh(int visited[], int root, int neigh[][]) {
		if (visited[root] > 0)
			return 0;
		visited[root]++;
		int rc = 1;
		for (int j=1; j<=neigh[root][0]; j++)
			if (visited[neigh[root][j]] <= 0)
				rc += allNeigh(visited, neigh[root][j], neigh);
		return rc;
	}
	
	static long choose(int n, int k) {
		assert(k <= n);
		long res = 1;
		for (long i=n,j=1; j<=k; i--,j++) {
			res *= i;
			res /= j;
		}
		return res;
	}
	
	/**
	 * solver function
	 */
	public static Answer solve(Input in) {
		int visited[];
		long rc = 0;
		long maxAug = 0;
		for (int i=0; i<in.k; i++) {
			visited = new int[in.n];
			int n = allNeigh(visited, in.c[i], in.neigh);
			int m = 0;
			for (int j=0; j<in.n; j++)
				if (visited[j] > 0)
					m += in.neigh[j][0];
			m /= 2;
			long add = 0;
			if (n>1)
				add = choose(n, 2)-m;
			long aug = 0;
			if (n+in.leftovers > 1)
				aug = (choose(n+in.leftovers, 2)-m-in.leftover_conn)-add;
			if (aug > maxAug)
				maxAug = aug;
			rc += add;
		}
		rc += maxAug;
		Answer ans = new Answer(rc);
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
