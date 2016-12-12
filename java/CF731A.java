import java.io.PrintStream;
import java.util.Scanner;

public class CF731A {
	/**
	 * solution result
	 */
	public static class Answer {
		int score;
		public Answer(int score) {
			this.score = score;
		}

		@Override
		public String toString() {
			return Integer.toString(score);
		}
	};

	/**
	 * input parser
	 */
	public static class Input {
		String s;
		public Input(Scanner in) {
			s = in.nextLine();
		}
	};

	/**
	 * solver function
	 */
	public static Answer solve(Input in) {
		int score = 0;
		int currPos = 0;
		for (char ch:in.s.toCharArray()) {
			int chIdx = ch-'a';
			score += Math.min((chIdx+26-currPos)%26, (currPos+26-chIdx)%26);
			currPos = chIdx;
		}
		Answer ans = new Answer(score);
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
