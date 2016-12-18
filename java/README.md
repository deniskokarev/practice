#dk.struct.AttrTreap
is an attributive [Treap](https://en.wikipedia.org/wiki/Treap) - a binary search tree with randomly assigned node levels.
May become useful one day. 

#dk.struct.test
the related JUnit test cases

#Hints
For CodeForces tasks add this to your code autocompletion:
* <command>, - Preferences
* Java/Editor/Templates/New...
* use it by pressing <Alt>+/

```java
import java.io.PrintStream;
import java.util.Scanner;

public class ${enclosing_type} {
	/**
	 * solution result
	 */
	public static class Answer {
		public Answer() {
		}
		@Override
		public String toString() {
			return "place real answer here";
		}
	};

	/**
	 * input parser
	 */
	public static class Input {
		public Input(Scanner sc) {
		}
	};

	/**
	 * solver function
	 */
	public static Answer solve(Input in) {
		Answer ans = new Answer();
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
```
