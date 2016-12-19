package dk.topcoder;
/**
 * https://arena.topcoder.com ABBADiv1 problem
 * https://arena.topcoder.com/#/u/practiceCode/16526/48829/13922/1/326682
 * @author kokarev
 * ..... copy-paste src from here .....
 * vvvvv                          vvvvv
 */

import java.io.PrintStream;
import java.util.Scanner;

public class ABBADiv1 {
	/**
	 * solution result
	 */
	public static class Answer {
		String rc;
		public Answer(String rc) {
			this.rc = rc;
		}

		@Override
		public String toString() {
			return rc;
		}
	};

	/**
	 * input parser
	 */
	public static class Input {
		String src;
		String tgt;
		public Input(Scanner sc) {
			src = sc.nextLine();
			tgt = sc.nextLine();
		}
	};
	/*
	 * BEGIN tc portion
	 */
	static void rev(char validData[], int sz) {
		for(int i = 0; i < sz / 2; i++) {
		    char temp = validData[i];
		    validData[i] = validData[sz - i - 1];
		    validData[sz - i - 1] = temp;
		}	
	}
    static boolean eq(char a[], int aSz, char b[], int bSz) {
        boolean rc = false;
        if (aSz == bSz) {
            int i;
            for (i=0; i<aSz && a[i] == b[i]; i++);
            rc = (i==aSz);
        }
        return rc;
    }
    static boolean ifPossible(char s[], int sSz, char tgt[], int tgtSz) {
        if (eq(s, sSz, tgt, tgtSz)) {
            return true;
        }
        if (sSz < tgtSz)
            return false;
        boolean rc = false;
        if (s[sSz-1] == 'A')
			rc = ifPossible(s, sSz-1, tgt, tgtSz);       
        if (!rc && s[0] == 'B') {
        	rev(s, sSz);
        	rc = ifPossible(s, sSz-1, tgt, tgtSz);
        	rev(s, sSz);
        }
        return rc;
    }
    static public String canObtain(String from, String to) {
    	char tgt[] = from.toCharArray();
    	char src[] = to.toCharArray(); 
        return ifPossible(src, src.length, tgt, tgt.length)?"Possible":"Impossible";
    }
	/*
	 * END tc portion
	 */


	/**
	 * solver function
	 */
	public static Answer solve(Input in) {
		Answer ans = new Answer(canObtain(in.src, in.tgt));
		return ans;
	}

	/**
	 * standard CodeForces executable mantra
	 */
	public static void proc(Scanner sc, PrintStream out) {
		Input in = new Input(sc);
		out.println(solve(in));
	}

	public static void main(String[] args) {
		try (Scanner sc = new Scanner(System.in)) {
			proc(sc, System.out);
		}
	}
}
