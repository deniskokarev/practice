package dk.a;

/**
 * Intermix two strings so that the resulting string would contain both
 * original strings as its subsequences. I.e. char order in the original
 * strings must be preserved
 * I.e. ABC with DEF could result in
 * ABCDEF, ADBECF
 * but not CAEDFB 
 * @author kokarev
 */
public class SubseqTwo {
	static void prn(char s[], int sz) {
		for (int i=0; i<sz; i++)
			System.out.print(s[i]);
		System.out.println();
	}
	static void genR(char a[], int ai, char b[], int bi, char o[], int oi) {
		if (ai == a.length && bi == b.length)
			prn(o, oi);
		if (ai < a.length) {
			o[oi] = a[ai];
			genR(a, ai+1, b, bi, o, oi+1);
		}
		if (bi < b.length) {
			o[oi] = b[bi];
			genR(a, ai, b, bi+1, o, oi+1);
		}
	}
	static void gen(String a, String b) {
		char o[] = new char[a.length()+b.length()];
		genR(a.toCharArray(), 0, b.toCharArray(), 0, o, 0);
	}
	public static void main(String[] args) {
		gen("ABC", "DEF");
	}
}
