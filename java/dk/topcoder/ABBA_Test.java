package dk.topcoder;

/**
 * test cases for ABBA topcoder problem
 */

import static org.junit.Assert.*;

import org.junit.Test;

public class ABBA_Test {

	@Test
	public void test0() {
		assertEquals(ABBA.canObtain("B", "ABBA"), "Possible");
	}
	@Test
	public void test1() {
		assertEquals(ABBA.canObtain("AB", "ABB"), "Impossible");
	}
	@Test
	public void test2() {
		assertEquals(ABBA.canObtain("BBAB", "ABABABABB"), "Impossible");
	}
	@Test
	public void test3() {
		assertEquals(ABBA.canObtain("BBBBABABBBBBBA", "BBBBABABBABBBBBBABABBBBBBBBABAABBBAA"), "Possible");
	}
	@Test
	public void test4() {
		assertEquals(ABBA.canObtain("A", "BB"), "Impossible");
	}

}
