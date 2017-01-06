import java.io.PrintStream;
import java.util.LinkedList;
import java.util.List;
import java.util.Scanner;

public class CF754A {

	static class Pair {
		int l, r;
		Pair(int l, int r) {
			this.l = l;
			this.r = r;
		}
	}
	/**
	 * solution result
	 */
	public static class Answer {
		List<Pair> p;
		public Answer(List<Pair> p) {
			this.p = p;
		}

		@Override
		public String toString() {
			StringBuffer sb = new StringBuffer();
			if (p!=null) {
				sb.append("YES\n");
				sb.append(Integer.toString(p.size()));
				sb.append('\n');
				for (Pair ip:p) {
					sb.append(Integer.toString(ip.l));
					sb.append(' ');
					sb.append(Integer.toString(ip.r));
					sb.append('\n');
				}
			} else {
				sb.append("NO");
			}
			return sb.toString();
		}
	};

	/**
	 * input parser
	 */
	public static class Input {
		int n;
		int a[];
		public Input(Scanner sc) {
			n = sc.nextInt();
			a = new int[n];
			for (int i=0; i<n; i++) {
				a[i] = sc.nextInt();
			}
		}
	};


	static int partSum(int a[], int l, int r) {
		int sum = 0;
		for (int i=l; i<r; i++)
			sum += a[i];
		return sum;
	}
	
	/**
	 * solver function
	 */
	public static Answer solve(Input in) {
		List<Pair> p = new LinkedList<>();
		if (partSum(in.a, 0, in.a.length) != 0) {
			p.add(new Pair(1, in.a.length));
		} else {
			int l=0;
			while (l<in.a.length && in.a[l] == 0)
				l++;
			if (l<in.a.length) {
				p.add(new Pair(1, l+1));
				p.add(new Pair(l+2, in.a.length));
			}
				
		}
		if (p.size() > 0)
			return new Answer(p);
		else
			return new Answer(null);
	}

	/**
	 * standard executable mantra
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
