import java.io.PrintStream;
import java.util.HashSet;
import java.util.Scanner;
import java.util.Set;

public class CF755B {
	/**
	 * solution result
	 */
	public static class Answer {
		boolean r;
		public Answer(boolean r) {
			this.r = r;
		}

		@Override
		public String toString() {
			return (r)?"YES":"NO";
		}
	};

	/**
	 * input parser
	 */
	public static class Input {
		Set<String> p;
		Set<String> v;
		public Input(Scanner sc) {
			p = new HashSet<>();
			v = new HashSet<>();
			int pn = sc.nextInt();
			int vn = sc.nextInt();
			sc.nextLine();
			for (int i=0; i<pn; i++)
				p.add(sc.nextLine());
			for (int i=0; i<vn; i++)
				v.add(sc.nextLine());
		}
	};

	/**
	 * solver function
	 */
	public static Answer solve(Input in) {
		Set<String> cc = new HashSet<>(in.p);
		cc.retainAll(in.v);
		Answer ans = new Answer((in.p.size()+(cc.size()%2)) > in.v.size());
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
