package dk.comb;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.List;
import java.util.stream.Collectors;

interface MultisetCallback {
	public void callback(Object o[], int n);
}

class Multiset {
	protected static void run(Object from[], int fromN, Object to[], int toN, MultisetCallback c) {
		if (fromN < from.length) {
			run(from, fromN+1, to, toN, c);
			to[toN] = from[fromN];
			run(from, fromN+1, to, toN+1, c);
		} else {
			c.callback(to,  toN);
		}
	}
	public static void run(List<Object> s, MultisetCallback c) {
		Object f[] = s.toArray();
		Object t[] = new Object[f.length];
		run(f, 0, t, 0, c);
	}
}

public class MultisetMain implements MultisetCallback {
	int nrow;
	
	public MultisetMain() {
		nrow = 0;
	}
	public static void main(String argv[]) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		System.out.println("Generating multiset");
		System.out.println("Enter the set (in the form of a string):");
		String s = br.readLine();
		List<Object> o = s.chars().mapToObj(ch->new Character((char)ch)).collect(Collectors.toList());
		MultisetMain m = new MultisetMain();
		Multiset.run(o, m);
	}
	@Override
	public void callback(Object[] o, int n) {
		System.out.print(nrow+": [");
		int i;
		if (n>0) {
			for (i=0; i<n-1; i++) {
				System.out.print(o[i]);
				System.out.print(", ");
			}
			System.out.print(o[i]);
		}
		System.out.println("]");
		nrow++;
	}
}
