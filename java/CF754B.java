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
		int p1, p2, b;
		void zero() {
			p1 = p2 = b = 0;
		}
	}
	
	static boolean check(State st, Input in) {
		switch (in.board[st.y][st.x]) {
		case 1:
			st.p2++;
			if (st.p1 > 0 && st.p1+st.p2>1)
				return true;
			else if (st.p2>1 && st.b>0)
				return true;
			break;
		case -1:
			st.p1 = st.p2 = 0;
			st.b = 0;
			break;
		case 0:
			if (st.p2 > 1)
				return true;
			if (st.b == 0) {
				st.p1 = st.p2;
			} else {
				st.p1 = 0;
			}
			st.p2 = 0;
			st.b++;
			break;
		}
		return false;
	}
	
	public static Answer solve(Input in) {
		State st = new State();
		for (st.y=0; st.y<4; st.y++) {
			for (st.x=0; st.x<4; st.x++)
				if (check(st, in))
					return new Answer("YES");
			st.zero();
		}
		st.zero();
		for (st.x=0; st.x<4; st.x++) {
			for (st.y=0; st.y<4; st.y++)
				if (check(st, in))
					return new Answer("YES");
			st.zero();
		}
		st.zero();
		for (int d=-3; d<4; d++) {
			for (st.y=0; st.y<4; st.y++) {
				st.x = d+st.y;
				if (st.x >= 0 && st.x < 4)
					if (check(st, in))
						return new Answer("YES");
			}
			st.zero();
		}
		st.zero();
		for (int d=6; d>=0; d--) {
			for (st.y=0; st.y<4; st.y++) {
				st.x = d-st.y;
				if (st.x >= 0 && st.x < 4)
					if (check(st, in))
						return new Answer("YES");
			}
			st.zero();
		}
		Answer ans = new Answer("NO");
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
