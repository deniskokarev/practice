import java.io.PrintStream;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;
import java.util.stream.Collectors;

public class CF757B {
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

	/**
	 * input parser
	 */
	public static class Input {
		int n;
		int ss[];
		public Input(Scanner sc) {
			n = sc.nextInt();
			ss = new int[n];
			for (int i=0; i<n; i++)
				ss[i] = sc.nextInt();
		}
	};

    public static List<Integer> primeFactors(int numbers) {
        int n = numbers;
        List<Integer> factors = new ArrayList<Integer>();
        for (int i = 2; i <= n / i; i++) {
                while (n % i == 0) {
                        factors.add(i);
                        n /= i;
                }
        }
        if (n > 1) {
                factors.add(n);
        }
        return factors;
    }

	/**
	 * solver function
	 */
	public static Answer solve(Input in) {
		int cnt[] = new int[100002];
		for (int i=0; i<in.n; i++) {
			if (in.ss[i] > 1) {
				List<Integer> pl = primeFactors(in.ss[i]).stream().sorted().collect(Collectors.toList());
				int p2 = pl.remove(0);
				while (pl.size() > 0) {
					int p1 = pl.remove(0);
					if (p2 != p1) {
						cnt[p2]++;
						p2 = p1;
					}
				}
				cnt[p2]++;
			}
		}
		int mx = 1;
		for (int i=2; i<cnt.length; i++) {
			mx = Math.max(mx, cnt[i]);
		}
		Answer ans = new Answer(mx);
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
