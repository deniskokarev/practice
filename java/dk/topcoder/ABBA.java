package dk.topcoder;

/**
 * topcoder ABBA problem
 * 
 * Problem Statement

One day, Jamie noticed that many English words only use the letters A and B. Examples of such words include "AB" (short for abdominal), "BAA" (the noise a sheep makes), "AA" (a type of lava), and "ABBA" (a Swedish pop sensation).

Inspired by this observation, Jamie created a simple game. You are given two s: initial and target. The goal of the game is to find a sequence of valid moves that will change initial into target. There are two types of valid moves:

    Add the letter A to the end of the string.
    Reverse the string and then add the letter B to the end of the string.

Return "Possible" (quotes for clarity) if there is a sequence of valid moves that will change initial into target. Otherwise, return "Impossible".
Definition
Class:
ABBA
Method:
canObtain
Parameters:
String, String
Returns:
String
Method signature:
String canObtain(String initial, String target)
(be sure your method is public)
Limits
Time limit (s):
2.000
Memory limit (MB):
256
Constraints
- The length of initial will be between 1 and 999, inclusive.
- The length of target will be between 2 and 1000, inclusive.
- target will be longer than initial.
- Each character in initial and each character in target will be either 'A' or 'B'.
Examples
0)
"B"
"ABBA"
Returns: "Possible"
Jamie can perform the following moves:

    Initially, the string is "B".
    Jamie adds an 'A' to the end of the string. Now the string is "BA".
    Jamie reverses the string and then adds a 'B' to the end of the string. Now the string is "ABB".
    Jamie adds an 'A' to the end of the string. Now the string is "ABBA".

Since there is a sequence of moves which starts with "B" and creates the string "ABBA", the answer is "Possible".
1)
"AB"
"ABB"
Returns: "Impossible"
The only strings of length 3 Jamie can create are "ABA" and "BAB".
2)
"BBAB"
"ABABABABB"
Returns: "Impossible"
3)
"BBBBABABBBBBBA"
"BBBBABABBABBBBBBABABBBBBBBBABAABBBAA"
Returns: "Possible"
4)
"A"
"BB"
Returns: "Impossible"

 * @author kokarev
 *
 */

// copy-paste the following code into "Coding Area"
// ||||||||
// VVVVVVVV

public class ABBA {
	static void rev(char validData[], int sz) {
		for (int i = 0; i < sz / 2; i++) {
			char temp = validData[i];
			validData[i] = validData[sz - i - 1];
			validData[sz - i - 1] = temp;
		}
	}

	static boolean eq(char a[], int aSz, char b[], int bSz) {
		boolean rc = false;
		if (aSz == bSz) {
			int i;
			for (i = 0; i < aSz && a[i] == b[i]; i++)
				;
			rc = (i == aSz);
		}
		return rc;
	}

	static boolean ifPossible(char s[], int sSz, char tgt[], int tgtSz) {
		if (eq(s, sSz, tgt, tgtSz))
			return true;
		if (sSz < tgtSz)
			return false;
		boolean rc;
		if (s[sSz - 1] == 'A') {
			rc = ifPossible(s, sSz - 1, tgt, tgtSz);
		} else if (s[sSz - 1] == 'B') {
			rev(s, sSz-1);
			rc = ifPossible(s, sSz - 1, tgt, tgtSz);
			rev(s, sSz-1);
		} else {
			rc = false;
		}
		return rc;
	}

	static public String canObtain(String from, String to) {
		char tgt[] = from.toCharArray();
		char src[] = to.toCharArray();
		return ifPossible(src, src.length, tgt, tgt.length) ? "Possible" : "Impossible";
	}
}
