import java.io.PrintStream;
import java.util.ArrayList;
import java.util.LinkedList;
import java.util.List;
import java.util.Scanner;

public class CF742B {
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

	/**
	 * input parser
	 */
	public static class Input {
		int n;
		int x;
		int a[];
		public Input(Scanner sc) {
			n = sc.nextInt();
			x = sc.nextInt();
			a = new int[n];
			for (int i=0; i<n; i++)
				a[i] = sc.nextInt();
		}
	};

	/**
	 * solver function
	 */
	public static Answer solve(Input in) {
		int idx[] = new int[1<<17]; // to allow all 17bits set +1
		for (int i=0; i<in.a.length; i++)
			idx[in.a[i]]++;
		long cnt = 0;
		for (int i=0; i<in.a.length; i++) {
			int xor = in.x^in.a[i];
			idx[in.a[i]]--;
			cnt += idx[xor];
		}
		Answer ans = new Answer(cnt);
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
