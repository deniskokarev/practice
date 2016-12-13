package dk.comb;

import java.util.Arrays;
import java.util.Iterator;
import java.util.LinkedList;
import java.util.List;
import java.util.ListIterator;

/**
 * remove duplicates in LL
 * assuming elements are non-null
 * @author kokarev
 */
public class LLRemoveDup {
	
	static boolean isIn(Object o, Iterator j) {
		boolean match = false;
		while (j.hasNext()) {
			if (o.equals(j.next())) {
				match = true;
				break;
			}
		}
		return match;
	}

	static List removeDup(List src) {
		List dst = new LinkedList();
		ListIterator i = src.listIterator();
		while (i.hasNext()) {
			Object o = i.next();
			if (!isIn(o, src.listIterator(i.nextIndex())))
				dst.add(o);
		}
		return dst;
	}

	public static void main(String[] args) {
		List l = Arrays.asList("1","1","2","3","4","3","2","1","1");
		for (Object e : removeDup(l)) {
			System.out.print(e);
			System.out.print(" ");
		}
		System.out.println();
	}
}
