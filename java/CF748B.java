import java.io.PrintStream;
import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;
/**
 * http://codeforces.com/problemset/problem/748/B
 * B. Santa Claus and Keyboard Check
time limit per test
2 seconds
memory limit per test
256 megabytes
input
standard input
output
standard output

Santa Claus decided to disassemble his keyboard to clean it. After he returned all the keys back, he suddenly realized that some pairs of keys took each other's place! That is, Santa suspects that each key is either on its place, or on the place of another key, which is located exactly where the first key should be.

In order to make sure that he's right and restore the correct order of keys, Santa typed his favorite patter looking only to his keyboard.

You are given the Santa's favorite patter and the string he actually typed. Determine which pairs of keys could be mixed. Each key must occur in pairs at most once.
Input

The input consists of only two strings s and t denoting the favorite Santa's patter and the resulting string. s and t are not empty and have the same length, which is at most 1000. Both strings consist only of lowercase English letters.
Output

If Santa is wrong, and there is no way to divide some of keys into pairs and swap keys in each pair so that the keyboard will be fixed, print «-1» (without quotes).

Otherwise, the first line of output should contain the only integer k (k ≥ 0) — the number of pairs of keys that should be swapped. The following k lines should contain two space-separated letters each, denoting the keys which should be swapped. All printed letters must be distinct.

If there are several possible answers, print any of them. You are free to choose the order of the pairs and the order of keys in a pair.

Each letter must occur at most once. Santa considers the keyboard to be fixed if he can print his favorite patter without mistakes.
Examples
Input

helloworld
ehoolwlroz

Output

3
h e
l o
d z

Input

hastalavistababy
hastalavistababy

Output

0

Input

merrychristmas
christmasmerry

Output

-1
 * 
 * @author kokarev
 *
 */

public class CF748B {
	/**
	 * solution result
	 */
	public static class Answer {
		Map<Character, Character> a;
		boolean valid;
		public Answer(Map<Character, Character> a, boolean v) {
			this.a = a;
			this.valid = v;
		}

		@Override
		public String toString() {
			StringBuffer sb;
			if (valid) {
				sb = new StringBuffer(Integer.toString(a.size()));
				sb.append('\n');
				for (Character k:a.keySet()) {
					sb.append(k);
					sb.append(' ');
					sb.append(a.get(k));
					sb.append('\n');
				}
			} else {
				sb = new StringBuffer("-1\n");
			}
			return sb.toString();
		}
	};

	/**
	 * input parser
	 */
	public static class Input {
		String s1, s2;
		public Input(Scanner sc) {
			s1 = sc.nextLine();
			s2 = sc.nextLine();
		}
	};

	static char max(char a, char b) {
		return (a>b)?a:b;
	}
	
	static char min(char a, char b) {
		return (a<b)?a:b;
	}
	
	/**
	 * solver function
	 */
	public static Answer solve(Input in) {
		Map<Character, Character> m = new HashMap<>();
		for (int i=0; i<in.s1.length(); i++) {
			char c1 = min(in.s1.charAt(i), in.s2.charAt(i));
			char c2 = max(in.s1.charAt(i), in.s2.charAt(i));
			if (c1 != c2) {
				if (!m.containsKey(c1))
					m.put(c1, c2);
				else if (m.get(c1) != c2)
					return new Answer(null, false);
			}
		}
		Answer ans = new Answer(m, true);
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
