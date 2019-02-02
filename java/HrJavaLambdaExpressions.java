/* https://www.hackerrank.com/challenges/java-lambda-expressions */
import java.io.*;
import java.util.*;

interface PerformOperation {
	boolean check(int a);
}

class MyMath {
	public boolean checker(PerformOperation p, int num) {
		return p.check(num);
	}
	// Write your code here
	public PerformOperation isOdd() {
		return new PerformOperation() {
			public boolean check(int a) {
				return ((a&1) == 1);
			}
		};
	}
	public PerformOperation isPrime() {
		return new PerformOperation() {
			public boolean check(int a) {
				for (int f=2; f*f<=a; f++)
					if (a % f == 0)
						return false;
				return true;
			}
		};
	}
	public PerformOperation isPalindrome() {
		return new PerformOperation() {
			public boolean check(int a) {
				char s[] = Integer.toString(a).toCharArray();
				boolean res = true;
				for (int i=0,j=s.length-1; i<j; i++,j--)
					res &= (s[i] == s[j]);
				return res;
			}
		};
	}
}
// Write your code here

public class HrJavaLambdaExpressions {

	public static void main(String[] args) throws IOException {
		MyMath ob = new MyMath();
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		int T = Integer.parseInt(br.readLine());
		PerformOperation op;
		boolean ret = false;
		String ans = null;
		while (T--> 0) {
			String s = br.readLine().trim();
			StringTokenizer st = new StringTokenizer(s);
			int ch = Integer.parseInt(st.nextToken());
			int num = Integer.parseInt(st.nextToken());
			if (ch == 1) {
				op = ob.isOdd();
				ret = ob.checker(op, num);
				ans = (ret) ? "ODD" : "EVEN";
			} else if (ch == 2) {
				op = ob.isPrime();
				ret = ob.checker(op, num);
				ans = (ret) ? "PRIME" : "COMPOSITE";
			} else if (ch == 3) {
				op = ob.isPalindrome();
				ret = ob.checker(op, num);
				ans = (ret) ? "PALINDROME" : "NOT PALINDROME";

			}
			System.out.println(ans);
		}
	}
}
