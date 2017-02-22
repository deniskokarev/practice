package dk.draft;
// vvvv copy from below vvvv
// http://ideone.com/rkvASk
/**
 * Template for a problem
 */
import java.util.*;
import java.util.stream.StreamSupport;
import java.lang.*;
import java.io.*;

class Ideone {
	/* our input is guaranteed to be a vector of integers */
	static class Input {
		int a[];
		public Input(Scanner sc) {
			a = StreamSupport.stream(Spliterators.spliteratorUnknownSize(sc, Spliterator.ORDERED), false)
				.mapToInt(s->Integer.parseInt(s))
				.toArray();
		}
	}
	/* our solution  */
	static String result(Input in) {
		// actual answer suppose to be here
		// for example let's return the input as-is
		StringBuffer sb = new StringBuffer();
		for (int n : in.a) {
			sb.append(n);
			sb.append(' ');
		}
		return sb.toString();
	}
	public static void main (String[] args) throws java.lang.Exception {
		try (Scanner sc = new Scanner(System.in)) {
			System.out.println(result(new Input(sc)));
		}
	}
}
