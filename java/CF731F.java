import java.io.PrintStream;
import java.util.Arrays;
import java.util.Scanner;

public class CF731F {
	/**
	 * solution result
	 */
	public static class Answer {
		int tot;
		public Answer() {
			tot = Integer.MIN_VALUE;
		}
		@Override
		public String toString() {
			return Integer.toString(tot);
		}
		public boolean setMax(int v) {
			if (v > tot) {
				tot = v;
				return true;
			} else {
				return false;
			}
		}
	};

	static class Num implements Comparable<Num> {
		int num;
		boolean mark;
		long tot2right;
		int n2right;
		@Override
		public int compareTo(Num o) {
			return num-o.num;
		}
		public Num(int n) {
			num = n;
			mark = false;
			tot2right = -1;
			n2right = -1;
		}
	}
	/**
	 * input parser
	 */
	public static class Input {
		public int n;
		public Num a[];
		public Input(Scanner sc) {
			n = sc.nextInt();
			a = new Num[n];
			for (int i=0; i<n; i++)
				a[i] = new Num(sc.nextInt());
		}
	};

	/**
	 * solver function
	 */
	public static Answer solve(Input in) {
		Arrays.sort(in.a);
		long tot2right = 0;
		for (int i=in.a.length-1; i>=0; i--) {
			in.a[i].tot2right = tot2right;
			tot2right += in.a[i].num;
			in.a[i].n2right = in.a.length-1-i;
		}
		Answer ans = new Answer();
		for (int i=0; i<in.a.length; i++) {
			if (!in.a[i].mark) {
				int el = in.a[i].num;
				int sum = el;
				for (int j=i+1; j<in.a.length; j++) {
					int rem = in.a[j].num%el;
					sum += in.a[j].num-rem;
					if (rem == 0)
						in.a[j].mark = true;
				}
				ans.setMax(sum);
			}
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
