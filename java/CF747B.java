import java.io.PrintStream;
import java.util.Scanner;

public class CF747B {
	/**
	 * solution result
	 */
	public static class Answer {
		String a;
		public Answer(String a) {
			this.a = a;
		}

		@Override
		public String toString() {
			return a;
		}
	};

	/**
	 * input parser
	 */
	public static class Input {
		int n;
		char s[];
		public Input(Scanner sc) {
			n = sc.nextInt();
			sc.nextLine();
			s = sc.nextLine().toCharArray();
		}
	};

	static void replaceNQsWith(char s[], char c, int n) {
		for (int i=0; i<s.length; i++) {
			if (s[i] == '?') {
				if (n <= 0)
					break;
				s[i] = c;
				n--;
			}
		}
	}
	
	/**
	 * solver function
	 */
	public static Answer solve(Input in) {
		int cnt[] = new int[256];
		for (int i=0; i<in.s.length; i++)
			cnt[in.s[i]]++;
		int a = cnt['A'];
		int c = cnt['C'];
		int g = cnt['G'];
		int t = cnt['T'];
		int q = cnt['?'];
		int m = Math.max(Math.max(Math.max(a, c), g), t);
		int s = 0;
		s += m-a;
		s += m-c;
		s += m-g;
		s += m-t;
		if ((s <= q) && ((q-s)%4 == 0)) {
			replaceNQsWith(in.s, 'A', m-a+(q-s)/4);
			replaceNQsWith(in.s, 'C', m-c+(q-s)/4);
			replaceNQsWith(in.s, 'G', m-g+(q-s)/4);
			replaceNQsWith(in.s, 'T', m-t+(q-s)/4);
			return new Answer(new String(in.s));
		} else {
			return new Answer("===");
		}
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
