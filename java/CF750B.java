import java.io.PrintStream;
import java.util.Scanner;

public class CF750B {
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

	static class Step {
		int t;
		String dir;
		int dirX, dirY;
		Step(int t, String dir) {
			this.t = t;
			this.dir = dir;
			switch(dir.charAt(0)) {
			case 'N':
				dirY = -t;
				dirX = 0;
				break;
			case 'S':
				dirY = t;
				dirX = 0;
				break;
			case 'E':
				dirY = 0;
				dirX = t;
				break;
			case 'W':
				dirY = 0;
				dirX = -t;
				break;
			}
		}
	}
	
	/**
	 * input parser
	 */
	public static class Input {
		int n;
		Step step[];
		public Input(Scanner sc) {
			n = sc.nextInt();
			step = new Step[n];
			for (int i=0; i<n; i++) {
				int t = sc.nextInt();
				step[i] = new Step(t, sc.next());
				sc.nextLine();
			}
		}
	};

	/**
	 * solver function
	 */
	public static Answer solve(Input in) {
		int x = 0, y = 0;
		for (int i=0; i<in.step.length; i++) {
			if (y + in.step[i].dirY < 0)
				return new Answer("NO");
			if (y + in.step[i].dirY > 20000)
				return new Answer("NO");
			if (y % 40000 == 0 && (in.step[i].dirX != 0 || in.step[i].dirY < 0))
				return new Answer("NO");
			if ((y+20000) % 40000 == 0 && (in.step[i].dirX != 0 || in.step[i].dirY > 0))
				return new Answer("NO");
			x += in.step[i].dirX;
			y += in.step[i].dirY;
		}
		if (y % 40000 == 0)
			return new Answer("YES");
		else
			return new Answer("NO");
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
