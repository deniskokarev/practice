package dk.draft;

import static org.junit.Assert.*;

import org.junit.Test;

public class RangeTest {

	@Test
	public void test1() {
		int v[] = {-1, -2, 5 ,1, 2, 10, -1, 3, -10, -20};
		Range r = new Range();
		Range expected = new Range(2, 7);
		assertEquals(expected, Range.maxRange(v, r));
	}
	@Test
	public void test2() {
		int v[] = {-1};
		Range r = new Range();
		Range expected = new Range(0, 0);
		assertEquals(expected, Range.maxRange(v, r));
	}
	@Test
	public void test3() {
		int v[] = {-1, 1};
		Range r = new Range();
		Range expected = new Range(1, 1);
		assertEquals(expected, Range.maxRange(v, r));
	}
	@Test
	public void test4() {
		int v[] = {-1, 1, -1};
		Range r = new Range();
		Range expected = new Range(1, 1);
		assertEquals(expected, Range.maxRange(v, r));
	}
	@Test
	public void test5() {
		int v[] = {1, -1, 2};
		Range r = new Range();
		Range expected = new Range(0, 2);
		assertEquals(expected, Range.maxRange(v, r));
	}
	@Test
	public void test6() {
		int v[] = {-3, -2, -1};
		Range r = new Range();
		Range expected = new Range(2, 2);
		assertEquals(expected, Range.maxRange(v, r));
	}
	@Test
	public void test7() {
		int v[] = {1, 2, 3};
		Range r = new Range();
		Range expected = new Range(0, 2);
		assertEquals(expected, Range.maxRange(v, r));
	}
}
