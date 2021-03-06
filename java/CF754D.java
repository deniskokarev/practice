import java.io.PrintStream;
import java.util.Arrays;
import java.util.Scanner;

public class CF754D {
	
	static class Range {
		int i, l, r;
		Range(int i, int l, int r) {
			this.i = i;
			this.l = l;
			this.r = r;
		}
	}
	
	/**
	 * solution result
	 */
	public static class Answer {
		int n;
		boolean rr[];
		public Answer(int n, boolean rr[]) {
			this.n = n;
			this.rr = rr;
		}
		@Override
		public String toString() {
			StringBuffer sb = new StringBuffer(Integer.toString(n));
			sb.append('\n');
			for (int i=0; i<rr.length; i++) {
				if (rr[i]) {
					sb.append(Integer.toString(i+1));
					sb.append(' ');
				}
			}
			sb.append('\n');
			return sb.toString();
		}
	};

	/**
	 * input parser
	 */
	public static class Input {
		int k;
		Range rr[];
		public Input(Scanner sc) {
			int n = sc.nextInt();
			k = sc.nextInt();
			sc.nextLine();
			rr = new Range[n];
			for (int i=0; i<rr.length; i++)
				rr[i] = new Range(i, sc.nextInt(), sc.nextInt());
		}
	};
	
	static class Point {
		int lr;
		int x;
		int i;
		Point(int lr, int x, int i) {
			this.lr = lr;
			this.x = x;
			this.i = i;
		}
	}
	
	/**
	 * Max number of ranges that would still overlap if all left borders change by lr and right borders change by dr
	 * @param r - ranges
	 * @param dl - change to all .l points (+ or -)
	 * @param dr - change to all .r points (+ or -)
	 * @param mxmm - boolean vector where the chosen range numbers will be stored
	 * @return
	 */
	static int overlappingRanges(Point pp[], Range rr[], int dl, int dr, boolean mxmm[]) {
		int np = 0;
		for (int i=0; i<rr.length; i++) {
			if (rr[i].l+dl < rr[i].r+dr) {
				Point p;
				p = pp[np++];
				p.lr = 1;
				p.x = rr[i].l+dl;
				p.i = i;
				p = pp[np++];
				p.lr = -1;
				p.x = rr[i].r+dr;
				p.i = i;
			}
		}
		if (np > 0) {
			Arrays.sort(pp, 0, np, (Point a, Point b) -> (a.x<b.x)?-1:((a.x>b.x)?1:(b.lr-a.lr)));
			int n = 0, mx = 0, mxi = 0;
			for (int i=0; i<np; i++) {
				n += pp[i].lr;
				if (n > mx) {
					mx = n;
					mxi = i;
				}
			}
			if (mxmm != null)
				for (int i=0; i<=mxi; i++)
					mxmm[pp[i].i] = !mxmm[pp[i].i];
			return mx;
		} else {
			return 0;
		}
	}
	
	/**
	 * find the difference between min r and max r of all rr[] ranges that are selected in sel
	 * @param rr all ranges
	 * @param sel consider only these ranges
	 * @return
	 */
	static int overlap(Range rr[], boolean sel[]) {
		int mxl = Integer.MIN_VALUE, mnr = Integer.MAX_VALUE;
		for (int j=0; j<sel.length; j++) {
			if (sel[j]) {
				mxl = Math.max(rr[j].l, mxl);
				mnr = Math.min(rr[j].r, mnr);
			}
		}
		if (mnr>=mxl)
			return mnr-mxl+1;
		else
			return 0;
	}

	/**
	 * solver function
	 */
	public static Answer solve(Input in) {
		int mn = 0;
		int mx = 2*1000000000+1;
		int mid;
		int k = 0;
		int maxcover = -1;
		Point pp[] = new Point[in.rr.length*2];
		for (int i=0; i<pp.length; i++)
			pp[i] = new Point(-1, -1, -1);
		while (mn<mx) {
			mid = mn + (mx-mn)/2;
			k = overlappingRanges(pp, in.rr, 0, -mid, null);
			if (k<in.k) {
				mx = mid;
			} else if (k == in.k) {
				maxcover = mid;
				mn = mid+1;
			} else {
				mn = mid+1;
			}
		};
		if (maxcover >= 0) {
			boolean sel[] = new boolean[in.rr.length];
			overlappingRanges(pp, in.rr, 0, -maxcover, sel);
			return new Answer(overlap(in.rr, sel), sel);
		} else {
			boolean sel[] = new boolean[in.rr.length];
			for (int i=0; i<in.k; i++) {
				sel[i] = true;
			}
			return new Answer(0, sel);
		}
	}

	/**
	 * standard CodeForces executable mantra
	 */
	public static void proc(Scanner sc, PrintStream out) {
		Input in = new Input(sc);
		out.print(solve(in));
	}

	public static void main(String[] args) {
		try (Scanner sc = new Scanner(System.in)) {
			proc(sc, System.out);
		}
	}
}
