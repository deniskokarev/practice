package dk.comb;

import java.util.Arrays;

public class Choose {
	public static void main(String args[]) {
		ChooseIterable c = new ChooseIterable(10, 5);
		System.err.println("You should be getting "+c.count()+" selections");
		for (int r[] : c) {
			Arrays.stream(r).forEach(i -> {System.out.print(i); System.out.print(" ");});
			System.out.println();
		}
	}
}
