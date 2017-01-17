package dk.alg.test;

import static org.junit.Assert.*;

import org.junit.Test;

import dk.alg.Comb;

public class CombTest {

	@Test
	public void testGcd() {
		assertEquals("GCD(45, 30) == 15", 15, Comb.gcd(45, 30));
		assertEquals("GCD(1, 1) == 1", 1, Comb.gcd(1, 1));
		assertEquals("GCD(2, 4) == 2", 2, Comb.gcd(2, 4));
		assertEquals("GCD(2^63, 2^16) == 2^16", 1<<16, Comb.gcd(1<<63, 1<<16));
		assertEquals("GCD(0xF000000000000000, 0x0F) == 0x0F", 0x0FL, Comb.gcd(0xF000000000000000L, 0x0FL));
	}

	@Test
	public void testLcm() {
		assertEquals("LCM(3, 5) == 15", 15, Comb.lcm(3, 5));
		assertEquals("LCM(1, 5) == 5", 5, Comb.lcm(1, 5));
		assertEquals("LCM(2, 1) == 2", 2, Comb.lcm(2, 1));
		assertEquals("LCM(2*3*4*5, 4*5*6) == 2*3*4*5*6", 2*3*4*5*6, Comb.lcm(2*3*4*5, 2*3*4*5*6));
		assertEquals("LCM(0xC000000000000000, 0x2000000000000000) == 0xC000000000000000", 0xC000000000000000L, Comb.lcm(0xC000000000000000L, 0x2000000000000000L));
	}

	@Test
	public void testChoose() {
		assertEquals("CHOOSE(5, 3) == 10", 10, Comb.choose(5, 3));
		assertEquals("CHOOSE(5, 3) == CHOOSE(5, 2)", Comb.choose(5, 2), Comb.choose(5, 3));
		assertEquals("CHOOSE(60, 30) == 118264581564861424", 118264581564861424L, Comb.choose(60, 30));
	}

	@Test
	public void testFact() {
		assertEquals("0! == 1", 1, Comb.fact(0));
		assertEquals("1! == 1", 1, Comb.fact(1));
		assertEquals("1! == 1", 1, Comb.fact(1));
		assertEquals("20! == 2432902008176640000", 2432902008176640000L, Comb.fact(20));
	}

	static boolean headEqual(int a[], int b[], int n) {
		for (int i=0; i<n; i++)
			if (a[i] != b[i])
				return false;
		return true;
	}
	
	@Test
	public void testPrimeFactors() {
		int pp[] = new int[32];
		assertTrue("2147483647==2147483647", headEqual(new int[]{2147483647}, pp, Comb.primeFactors(2147483647, pp)));
		assertTrue("6==2*3", headEqual(new int[]{2, 3}, pp, Comb.primeFactors(2*3, pp)));
		assertTrue("256==2*2*2*2*2*2*2*2", headEqual(new int[]{2, 2, 2, 2, 2, 2, 2, 2}, pp, Comb.primeFactors(256, pp)));
	}
}
