package dk.comb;

import java.util.Arrays;
import java.util.List;

public class TGen {

	static <T extends Number> long sumList(List<T> l) {
		long r = 0;
		for (T i : l) {
			r += i.longValue();
		}
		return r;
	}
	
	public static void main(String[] args) {
		System.out.println(sumList(Arrays.asList(1,2,3)));
		System.out.println(sumList(Arrays.asList(10.0,20.0,30.0)));
	}
}
