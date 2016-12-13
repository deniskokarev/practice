package dk.comb;

import java.util.Arrays;
import java.util.Iterator;
import java.util.LinkedList;
import java.util.List;
import java.util.stream.Collectors;

public class LLQsort<T> {
	protected static <T> void splitList(Iterator<T> src, Comparable<T> m, List<T> lo, List<T> hi) {
		while (src.hasNext()) {
			T el = src.next();
			if (m.compareTo(el) > 0)
				lo.add(el);
			else
				hi.add(el);
		}
	}
	protected static <T extends Comparable<T>> List<T> pivot(List<T> src) {
		Iterator<T> i = src.iterator();
		if (i.hasNext()) {
			T o = i.next();
			List<T> lo = new LinkedList<T>();
			List<T> hi = new LinkedList<T>();
			splitList(i, o, lo, hi);
			List<T> r = qsort(lo);
			r.add(o);
			r.addAll(qsort(hi));
			return r;
		} else {
			return src;
		}
	}
	public static <T extends Comparable<T>> List<T> qsort(List<T> src) {
		return pivot(src);
	}
	public static void main(String args[]) {
		List<String> src = Arrays.asList("1","3","2","5","4");
		System.out.println(qsort(src).stream().collect(Collectors.joining(" ")));
	}
}
