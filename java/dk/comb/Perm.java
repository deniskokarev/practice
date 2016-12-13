package dk.comb;

import java.util.ArrayList;
import java.util.Collection;
import java.util.Collections;
import java.util.List;

interface PermCallback {
	public boolean callback(Collection<Object> i);
}

public class Perm {

	protected static boolean perm_r(List<Object> a, int idx, int permIdx, PermCallback pc) {
		boolean rc;
		if (idx < a.size()) {
			for (int i=0; i<idx; i++)
				if (!(rc=perm_r(a, idx+1, permIdx+i, pc)))
						return rc;
		} else {
			if ((permIdx & 1) != 0) {
				for (int i=0; i<a.size()-1; i++) {
					if (!(rc=pc.callback(a)))
						return rc;
					Collections.swap(a, i, i+1);
				}
				if (!(rc=pc.callback(a)))
					return rc;
				Collections.swap(a, 0, 1);
			} else {
				for (int i=a.size()-1; i>0; i--) {
					if (!(rc=pc.callback(a)))
						return rc;
					Collections.swap(a, i-1, i);
				}
				if (!(rc=pc.callback(a)))
					return rc;
				Collections.swap(a, a.size()-2, a.size()-1);
			}
		}
		return true;
	}
	
	public static boolean perm(Collection<?> src, PermCallback pc) {
		ArrayList<Object> csrc = new ArrayList<Object>(src);
		return perm_r(csrc, 1, 0, pc);
	}
	
	public static void main(String[] args) {
		ArrayList<Object> a = new ArrayList<>();
		a.add("1");
		a.add("2");
		a.add("3");
		a.add("4");
		perm(a, new PermCallback() {
			@Override
			public boolean callback(Collection<Object> row) {
				for (Object i:row) {
					System.out.print(i);
					System.out.print(" ");
				}
				System.out.println();
				return true;
			}
		}
		);
	}

}
