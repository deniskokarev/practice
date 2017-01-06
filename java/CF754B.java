import java.io.PrintStream;
import java.util.Scanner;

public class CF754B {
	/**
	 * solution result
	 */
	public static class Answer {
		String s;
		public Answer(String s) {
			this.s = s;
		}

		@Override
		public String toString() {
			return s;
		}
	};

	/**
	 * input parser
	 */
	public static class Input {
		int board[][];
		public Input(Scanner sc) {
			board = new int[4][4];
			for (int y=0; y<4; y++) {
				String l = sc.next();
				for (int x=0; x<4; x++) {
					switch(l.charAt(x)) {
					case 'x':
						board[y][x] = 1;
						break;
					case 'o':
						board[y][x] = -1;
						break;
					default:
						board[y][x] = 0;
					}
				}
			}
		}
	};

	/**
	 * solver function
	 */
	static class State {
		int x, y;
		int p;
		void zero() {
			p = 0;
		}
	}
	
	static boolean check3(State st, Input in) {
		if (in.board[st.y][st.x] == 1) {
			st.p++;
			if (st.p > 2)
				return true;
		} else {
			st.p = 0;
		}
		return false;
	}

	static boolean check(Input in) {
		State st = new State();
		for (st.y=0; st.y<4; st.y++) {
			for (st.x=0; st.x<4; st.x++)
				if (check3(st, in))
					return true;
			st.zero();
		}
		st.zero();
		for (st.x=0; st.x<4; st.x++) {
			for (st.y=0; st.y<4; st.y++)
				if (check3(st, in))
					return true;
			st.zero();
		}
		st.zero();
		for (int d=-3; d<4; d++) {
			for (st.y=0; st.y<4; st.y++) {
				st.x = d+st.y;
				if (st.x >= 0 && st.x < 4)
					if (check3(st, in))
						return true;
			}
			st.zero();
		}
		st.zero();
		for (int d=6; d>=0; d--) {
			for (st.y=0; st.y<4; st.y++) {
				st.x = d-st.y;
				if (st.x >= 0 && st.x < 4)
					if (check3(st, in))
						return true;
			}
			st.zero();
		}
		return false;
	}
	
	public static Answer solve(Input in) {
		if (check(in))
			return new Answer("YES");
		for (int y=0; y<4; y++) {
			for (int x=0; x<4; x++) {
				if (in.board[y][x] == 0) {
					in.board[y][x] = 1;
					boolean rc = check(in);
					in.board[y][x] = 0;
					if (rc)
						return new Answer("YES");
				}
			}
		}
		return new Answer("NO");
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
