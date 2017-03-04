import java.io.PrintStream;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.Scanner;

public class CF776C {
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
		int n, k;
		long aa[];
		public Input(Scanner sc) {
			n = sc.nextInt();
			k = sc.nextInt();
			aa = new long[n];
			for (int i=0; i<n; i++)
				aa[i] = sc.nextLong();
		}
	};

	static class BoxLong {
		long l;
	}
	
	static long cnt(long ss[], long vkp[]) {
		long sum = 0;
		Map<Long, BoxLong> r = new HashMap<>();
		for (int i=ss.length-1; i>=0; i--) {
			for (long kp:vkp) {
				BoxLong v = r.get(kp+ss[i]);
				if (v != null)
					sum += v.l;
			}
			BoxLong v = r.get(ss[i]);
			if (v == null) {
				v = new BoxLong();
				r.put(ss[i], v);
			}
			v.l++;
		}
		for (long kp:vkp) {
			BoxLong v = r.get(kp);
			if (v != null)
				sum += v.l;
		}
		return sum;
	}
	
	/**
	 * solver function
	 */
	public static Answer solve(Input in) {
		long ss[] = new long[in.aa.length];
		ss[0] = in.aa[0];
		for (int i=1; i<in.aa.length; i++)
			ss[i] = ss[i-1]+in.aa[i];
		long sum = 0;
		if (Math.abs(in.k) > 1) {
			List<Long> lkp = new ArrayList<>();
			for (long v=1; Math.abs(v)<=100000000000000L; v *= in.k)
				lkp.add(v);
			long kp[] = lkp.stream().mapToLong(i -> i).toArray();
			sum += cnt(ss, kp);
		} else if (in.k == -1) {
			sum += cnt(ss, new long[]{-1, 1});
		} else {
			sum += cnt(ss, new long[]{1});
		}
		Answer ans = new Answer(sum);
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
