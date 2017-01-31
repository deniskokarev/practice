package dk.alg;

import static org.junit.Assert.*;

import java.util.Arrays;

import org.junit.Test;

public class HeapTest {
	static boolean headEqual(int a[], int b[], int n) {
		for (int i=0; i<n; i++)
			if (a[i] != b[i])
				return false;
		return true;
	}

	static void reverse(int a[]) {
		int i=0, j=a.length-1;
		while (i<j) {
			int c = a[i];
			a[i] = a[j];
			a[j] = c;
			i++; j--;
		}
		
	}
	
	@Test
	public void test0() {
		int a[] = {1, 2, 3, 4, 5};
		int sz = a.length;
		int b[] = new int[sz];
		System.arraycopy(a, 0, b, 0, sz);
		Heap.heapsort(a);
		Arrays.sort(b);
		reverse(b);
		StringBuffer sa = new StringBuffer();
		StringBuffer sb = new StringBuffer();
		for (int i=0; i<sz; i++) {
			sa.append(Integer.toString(a[i]));
			sa.append(' ');
			sb.append(Integer.toString(b[i]));
			sb.append(' ');
		}
		assertEquals("a[]==b[]", sa.toString(), sb.toString());
	}
	
	@Test
	public void test1() {
		int a[] = {5, 4, 3, 2, 1};
		int sz = a.length;
		int b[] = new int[sz];
		System.arraycopy(a, 0, b, 0, sz);
		Heap.heapsort(a);
		Arrays.sort(b);
		reverse(b);
		StringBuffer sa = new StringBuffer();
		StringBuffer sb = new StringBuffer();
		for (int i=0; i<sz; i++) {
			sa.append(Integer.toString(a[i]));
			sa.append(' ');
			sb.append(Integer.toString(b[i]));
			sb.append(' ');
		}
		assertEquals("a[]==b[]", sa.toString(), sb.toString());
	}
	
	@Test
	public void test2() {
		int a[] = {1235652972, 1149920128, 1136134975, 938664097, 18348731};
		int sz = a.length;
		int b[] = new int[sz];
		System.arraycopy(a, 0, b, 0, sz);
		Heap.heapsort(a);
		Arrays.sort(b);
		reverse(b);
		StringBuffer sa = new StringBuffer();
		StringBuffer sb = new StringBuffer();
		for (int i=0; i<sz; i++) {
			sa.append(Integer.toString(a[i]));
			sa.append(' ');
			sb.append(Integer.toString(b[i]));
			sb.append(' ');
		}
		assertEquals("a[]==b[]", sa.toString(), sb.toString());
	}

	@Test
	public void test3() {
		for (int sz=1; sz<64; sz++) {
			int a[] = new int[sz];
			int b[] = new int[sz];
			for (int i=0; i<sz; i++)
				a[i] = (int)(Math.random()*Integer.MAX_VALUE);
			System.arraycopy(a, 0, b, 0, sz);
			Heap.heapsort(a);
			Arrays.sort(b);
			reverse(b);
			StringBuffer sa = new StringBuffer();
			StringBuffer sb = new StringBuffer();
			for (int i=0; i<sz; i++) {
				sa.append(Integer.toString(a[i]));
				sa.append(' ');
				sb.append(Integer.toString(b[i]));
				sb.append(' ');
			}
			System.err.println(sa.toString());
			System.err.println(sb.toString());
			System.err.println(headEqual(a, b, sz));
			assertTrue("a[]==b[]", headEqual(a, b, sz));
		}
	}
}
