import java.io.PrintStream;
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
		Result() {
			a = new int[101];
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

	static boolean tryAuth(Input in, int c, Result st, int prevAuth) {
		if (c >= in.nc)
			return true;
		if (in.c[c].auth == -1) {
			for (int i=0; i<in.na; i++) {
				if (i == prevAuth)
					continue;
				if (in.c[c].r.contains(i))
					continue;
				st.a[c] = i;
				if (tryAuth(in, c+1, st, i))
					return true;
			}
			return false;
		} else {
			if (in.c[c].auth == prevAuth) {
				return false;
			} else {
				st.a[c] = in.c[c].auth;
				return tryAuth(in, c+1, st, in.c[c].auth);
			}
		}
	}
	
	/**
	 * solver function
	 */
	public static Answer solve(Input in) {
		Result st = new Result();
		if (tryAuth(in, 0, st, -2))
			return new Answer(st, in);
		else
			return new Answer(null, null);
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
