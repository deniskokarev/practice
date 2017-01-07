import java.io.PrintStream;
import java.util.Arrays;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Map;
import java.util.Scanner;
import java.util.Set;
import java.util.StringTokenizer;

public class CF754C {
	static class Chat {
		int auth;
		Set<Integer> r;
		String s;
	}
	
	/**
	 * input parser
	 */
	public static class Input {
		int na;
		String auth[];
		int nc;
		Chat c[];
		public Input(Scanner sc) {
			Map<String, Integer> nauth = new HashMap<>();
			na = sc.nextInt();
			auth = new String[na];
			for (int i=0; i<na; i++) {
				auth[i] = sc.next();
				nauth.put(auth[i], i);
			}
			nc = sc.nextInt();
			c = new Chat[nc];
			sc.nextLine();
			for (int i=0; i<nc; i++) {
				String l = sc.nextLine();
				c[i] = new Chat();
				int posSC = l.indexOf(':');
				c[i].s = l.substring(posSC+1);
				StringTokenizer st = new StringTokenizer(c[i].s, ".,!? ");
				String a = l.substring(0, posSC);
				if ("?".equals(a)) {
					c[i].auth = -1;
				} else {
					c[i].auth = nauth.get(a);
				}
				c[i].r = new HashSet<>();
				while (st.hasMoreTokens()) {
					String s = st.nextToken();
					if (nauth.get(s) != null) {
						c[i].r.add(nauth.get(s));
					}
				}
			}
		}
	};

	static class Result {
		int a[];
		Result(Chat c[]) {
			a = new int[c.length];
			for (int i=0; i<c.length; i++)
				a[i] = c[i].auth;
		}
	}
	
	/**
	 * solution result
	 */
	public static class Answer {
		Result r;
		Input in;
		public Answer(Result r, Input in) {
			this.r = r;
			this.in = in;
		}

		@Override
		public String toString() {
			if (r == null) {
				return "Impossible\n";
			} else {
				StringBuffer sb = new StringBuffer();
				for (int i=0; i<in.nc; i++) {
					sb.append(in.auth[r.a[i]]);
					sb.append(':');
					sb.append(in.c[i].s);
					sb.append('\n');
				}
				return sb.toString();
			}
		}
	};

	static class Pair implements Comparable<Pair> {
		int n, idx;
		Pair(int n, int idx) {
			this.n = n;
			this.idx = idx;
		}
		@Override
		public int compareTo(Pair o) {
			return n-o.n;
		}
	}
	
	static boolean tryAuth(Input in, Pair c[], int nc, Result st) {
		if (nc < 0)
			return true;
		int j = c[nc].idx;
		for (int i=0; i<in.na; i++) {
			if (j < st.a.length-1 && st.a[j+1] == i)
				continue;
			if (j > 0 && st.a[j-1] == i)
				continue;
			if (in.c[j].r.contains(i))
				continue;
			st.a[j] = i;
			if (tryAuth(in, c, nc-1, st))
				return true;
		}
		return false;
	}

	/**
	 * solver function
	 */
	public static Answer solve(Input in) {
		Result st = new Result(in.c);
		Pair c[] = new Pair[in.c.length];
		int nc = 0;
		for (int i=0; i<in.c.length; i++)
			if (in.c[i].auth == -1)
				c[nc++] = new Pair(in.c[i].r.size(), i);
		if (nc > 0) {
			nc--;
			Arrays.sort(c, 0, nc);
			if (tryAuth(in, c, nc, st))
				return new Answer(st, in);
			else
				return new Answer(null, null);
		} else {
			return new Answer(st, in);
		}
	}

	/**
	 * standard CodeForces executable mantra
	 */
	public static void proc(Scanner sc, PrintStream out) {
		Input in;
		int c = sc.nextInt();
		for (int i=0; i<c; i++) {
			in = new Input(sc);
			out.print(solve(in));
		}
	}

	public static void main(String[] args) {
		try (Scanner sc = new Scanner(System.in)) {
			proc(sc, System.out);
		}
	}
}
