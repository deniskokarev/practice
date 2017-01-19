import java.io.PrintStream;
import java.util.Scanner;

public class CF758B {
	final static int R = 0;
	final static int B = 1;
	final static int Y = 2;
	final static int G = 3;
	final static int X = 4;
	/**
	 * solution result
	 */
	public static class Answer {
		int b[];
		public Answer(int b[]) {
			this.b = b;
		}

		@Override
		public String toString() {
			String s = "";
			int i;
			for (i=0; i<3; i++)
				s += Integer.toString(b[i])+" ";
			s += Integer.toString(b[i]);
			return s;
		}
	};

	/**
	 * input parser
	 */
	public static class Input {
		char c[];
		public Input(Scanner sc) {
			String s = sc.nextLine();
			c = s.toCharArray();
		}
	};

	/**
	 * solver function
	 */
	public static Answer solve(Input in) {
		int map[] = new int[4];
		int miss[] = new int[4];
		for (int i=0; i<in.c.length; i++) {
			switch(in.c[i]) {
			case 'R':
				map[R] = i%4;
				break;
			case 'B':
				map[B] = i%4;
				break;
			case 'Y':
				map[Y] = i%4;
				break;
			case 'G':
				map[G] = i%4;
				break;
			default:
				miss[i%4]++;
			}
		}
		int b[] = new int[4];
		for (int i=0; i<4; i++)
			b[i] = miss[map[i]];
		Answer ans = new Answer(b);
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
