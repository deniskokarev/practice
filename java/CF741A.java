import java.io.PrintStream;
import java.util.Arrays;
import java.util.Scanner;

public class CF741A {
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
		int a[];
		public Input(Scanner sc) {
			n = sc.nextInt();
			a = new int[n];
			for (int i=0; i<n; i++)
				a[i] = sc.nextInt()-1;
		}
	};

	static long gcd(long a, long b)	{
	    while (b > 0) {
	        long temp = b;
	        b = a % b;
	        a = temp;
	    }
	    return a;
	}

	static long lcm(long a, long b)	{
	    return a * (b / gcd(a, b));
	}
	
	/**
	 * solver function
	 */
	public static Answer solve(Input in) {
		boolean v[] = new boolean[in.a.length];
		int loop[] = new int[in.a.length];
		int nl = 0;
		for (int i=0; i<in.a.length; i++) {
			int j = i;
			int cnt = 0; 
			while (!v[j]) {
				cnt++;
				v[j] = true;
				j = in.a[j];
			}
			if (cnt > 0) {
				if (j != i)
					return new Answer(-1);
				if (cnt%2 == 0)
					loop[nl++] = cnt/2;
				else
					loop[nl++] = cnt;
			}
		}
		if (nl > 0) {
			// uniq+lcm
			Arrays.sort(loop, 0, nl-1);
			int prev = loop[0]; 
			long lcm = prev;
			for (int i=1; i<nl; i++) {
				if (loop[i] != prev) {
					prev = loop[i];
					lcm = lcm(lcm, prev);
				}
			}
			return new Answer(lcm);
		} else {
			return new Answer(1);
		}
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
