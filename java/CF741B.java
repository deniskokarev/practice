import java.io.PrintStream;
import java.util.Arrays;
import java.util.LinkedList;
import java.util.List;
import java.util.Queue;
import java.util.Scanner;

public class CF741B {
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

	static class Girl {
		int b, w;
		Girl(int b, int w) {
			this.b = b;
			this.w = w;
		}
	}
	
	/**
	 * input parser
	 */
	public static class Input {
		int n, w;
		Girl gg[];
		int ff[][];
		public Input(Scanner sc) {
			n = sc.nextInt();
			int m = sc.nextInt();
			w = sc.nextInt();
			gg = new Girl[n];
			for (int i=0; i<n; i++)
				gg[i] = new Girl(0, sc.nextInt());
			for (int i=0; i<n; i++)
				gg[i].b = sc.nextInt();
			ff = new int[n][n+1];
			for (int i=0; i<m; i++) {
				int x = sc.nextInt()-1;
				int y = sc.nextInt()-1;
				ff[x][ff[x][0]+1] = y;
				ff[x][0]++;
				ff[y][ff[y][0]+1] = x;
				ff[y][0]++;
			}
		}
	};

	static Girl[][] buildGroups(Input in) {
		List<Girl> gg = new LinkedList<>();
		Queue<Integer> q = new LinkedList<>();
		boolean m[];
		m = new boolean[in.n];
		int grpcnt = 0;
		for (int i=0; i<in.n; i++) {
			if (m[i])
				continue;
			q.add(i);
			while (q.size() > 0) {
				int v = q.remove();
				if (!m[v]) {
					m[v] = true;
					for (int j=1; j<=in.ff[v][0]; j++)
						q.add(in.ff[v][j]);
				}
			}
			grpcnt++;
		}
		m = new boolean[in.n];
		Girl grp[][] = new Girl[grpcnt][];
		grpcnt--;
		for (int i=0; i<in.n; i++) {
			if (m[i])
				continue;
			gg.clear();
			int b = 0;
			int w = 0;
			q.add(i);
			while (q.size() > 0) {
				int v = q.remove();
				if (!m[v]) {
					m[v] = true;
					b += in.gg[v].b;
					w += in.gg[v].w;
					gg.add(in.gg[v]);
					for (int j=1; j<=in.ff[v][0]; j++)
						q.add(in.ff[v][j]);
				}
			}
			if (gg.size() > 1)
				gg.add(new Girl(b, w));
			grp[grpcnt--] = gg.toArray(new Girl[gg.size()]);
		}
		return grp;
	}
	
	/**
	 * solver function
	 */
	public static Answer solve(Input in) {
		Girl gg[][] = buildGroups(in);
		int mm[][] = new int[gg.length+2][in.w+1];
		int mx = 0;
		for (int gp=0; gp<gg.length; gp++) {
			for (int w=0; w<=in.w; w++) {
				for (int g=0; g<gg[gp].length; g++) {
					Girl girl = gg[gp][g];
					if (girl.w > w) {
						mm[gp+1][w] = Math.max(mm[gp][w], mm[gp+1][w]);
					} else {
						mm[gp+1][w] = Math.max(mm[gp][w], Math.max(mm[gp][w-girl.w] + girl.b, mm[gp+1][w]));
					}
					mx = Math.max(mx, mm[gp+1][w]);
				}
			}
		}
		Answer ans = new Answer(mx);
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
