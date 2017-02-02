package dk.alg.test;

import static org.junit.Assert.*;

import java.util.Arrays;

import org.junit.Test;

import dk.alg.Heap;

public class HeapTest {
	static void reverse(long a[]) {
		int i=0, j=a.length-1;
		while (i<j) {
			long c = a[i];
			a[i] = a[j];
			a[j] = c;
			i++; j--;
		}
		
	}
	
	void test(long a[]) {
		int sz = a.length;
		long b[] = new long[sz];
		System.arraycopy(a, 0, b, 0, sz);
		Heap.heapsort(a);
		Arrays.sort(b);
		reverse(b);
		StringBuffer sa = new StringBuffer();
		StringBuffer sb = new StringBuffer();
		for (int i=0; i<sz; i++) {
			sa.append(Long.toString(a[i]));
			sa.append(' ');
			sb.append(Long.toString(b[i]));
			sb.append(' ');
		}
		assertEquals("a[]==b[]", sa.toString(), sb.toString());
	}
	
	@Test
	public void test0() {
		long a[] = {1, 2, 3, 4, 5};
		test(a);
	}
	
	@Test
	public void test1() {
		long a[] = {5, 4, 3, 2, 1};
		test(a);
	}
	
	@Test
	public void test2() {
		long a[] = {1, 2};
		test(a);
	}

	@Test
	public void test3() {
		long a[] = {2, 1};
		test(a);
	}

	@Test
	public void test4() {
		long a[] = {1};
		test(a);
	}

	@Test
	public void testRand() {
		for (int sz=1; sz<1024; sz++) {
			long a[] = new long[sz];
			for (int i=0; i<sz; i++)
				a[i] = (int)(Math.random()*Integer.MAX_VALUE);
			test(a);
		}
	}

	@Test
	public void testPerformance() {
		int sz = 1<<25;	// 32M
		long a[] = new long[sz];
		for (int i=0; i<sz; i++)
			a[i] = sz-i;
		long b1 = System.currentTimeMillis();
		Arrays.sort(a);
		long e1 = System.currentTimeMillis();
		System.out.println("Arrays.sort(): "+(e1-b1)+" msec");
		for (int i=0; i<sz; i++)
			a[i] = sz-i;
		long b2 = System.currentTimeMillis();
		Heap.heapsort(a);
		long e2 = System.currentTimeMillis();
		System.out.println("Heap.heapsort(): "+(e2-b2)+" msec");
	}
}
