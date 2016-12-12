import java.io.PrintStream;
import java.util.Arrays;
import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

public class CF731C {
	/**
	 * solution result
	 */
	public static class Answer {
		public int colors[];
		public int cnt;
		public int ans;
		public Answer(Input in) {
			colors = new int[in.ncolors];
			cnt = 0;
			ans = 0;
		}
		void clearColors() {
			colors = new int[colors.length];
			cnt = 0;
		}
		@Override
		public String toString() {
			return Integer.toString(ans);
		}
	};

	static class Pair {
		public int left, right;
		public Pair(int l, int r) {
			// order by sock #
			left = Math.min(l, r);
			right = Math.max(l, r);
		}
	}
	/**
	 * input parser
	 */
	public static class Input {
		public int nsocks;	// nsocks
		public int ndays;
		public int ncolors;
		public int color[];
		public Pair pair[];
		public Input(Scanner in) {
			nsocks = in.nextInt();
			ndays = in.nextInt();
			ncolors = in.nextInt();
			color = new int[nsocks];
			for (int i=0; i<nsocks; i++)
				color[i] = in.nextInt()-1;
			pair = new Pair[ndays];
			for (int i=0; i<ndays; i++)
				pair[i] = new Pair(in.nextInt()-1, in.nextInt()-1);
		}
	};

	static class DAGNode {
		public int sock;
		public int color;
		public Map<Integer,DAGNode> chld;
		public boolean marked;
		public void add(DAGNode c) {
			if (chld.get(c.sock) == null)
				chld.put(c.sock, c);
		}
		public DAGNode(int sock, int color) {
			this.sock = sock;
			this.color = color;
			chld = new HashMap<>();
		}
	}
	/**
	 * walk all nodes from the root (if we haven't visited root yet) and
	 * count colors 
	 * @param root
	 * @param colors
	 */
	static void walk(DAGNode root, Answer ans) {
		if (!root.marked) {
			root.marked = true;
			for (DAGNode c:root.chld.values())
				walk(c, ans);
			ans.colors[root.color]++;
			ans.cnt++;
		}
	}
	/**
	 * solver function
	 */
	public static Answer solve(Input in) {
		DAGNode socks[] = new DAGNode[in.nsocks];
		// build DAG of all socks
		Arrays.sort(in.pair,(Pair a, Pair b)->Integer.compare(a.left, b.left)*10+Integer.compare(a.right, b.right));
		for (Pair p:in.pair) {
			if (socks[p.left] == null)
				socks[p.left] = new DAGNode(p.left, in.color[p.left]);
			if (socks[p.right] == null)
				socks[p.right] = new DAGNode(p.right, in.color[p.right]);
			socks[p.left].add(socks[p.right]);
		}
		// walk the DAG and count colors
		Answer ans = new Answer(in);
		for (DAGNode root:socks) {
			ans.clearColors();
			walk(root, ans);
			// find dominant color in the unwalked subtree
			int maxC = ans.colors[0];
			for (int i=1; i<ans.colors.length; i++)
				if (ans.colors[i] > maxC)
					maxC = ans.colors[i];
			// each unwalked socks chain has to be painted to the dominant
			// color
			ans.ans += ans.cnt - maxC;
		}
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
