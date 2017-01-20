package dk.draft;

import java.util.LinkedList;
import java.util.List;
import java.util.Scanner;

public class CutTheRod {
	static class Plan {
		List<Integer> cuts;
		int sum;
		Plan() {
			cuts = new LinkedList<>();
			sum = 0;
		}
	}
	static Plan dpSolve2(int l, int p[], Plan s[]) {
		if (s[l].sum == 0) {
			int mx = p[l], mxi = l;
			Plan mxPlan = s[l];
			for (int i=l-1; i>0; i--) {
				Plan lc = dpSolve2(l-i, p, s);
				if (mx < lc.sum + p[i]) {
					mx = lc.sum + p[i];
					mxi = i;
					mxPlan = lc;
				}
			}
			s[l].cuts = new LinkedList<>(mxPlan.cuts);
			s[l].cuts.add(mxi);
			s[l].sum = mx;
		}
		return s[l];
	}
	static Plan dpSolve(int l, int p[]) {
		Plan s[] = new Plan[l+1];
		for (int i=0; i<s.length; i++)
			s[i] = new Plan();
		for (int i=1; i<=l; i++) {
			int j = 1;
			int mxj = j;
			int mx = s[i-j].sum+p[j];
			for (j=2; j<=i; j++) {
				if (mx < s[i-j].sum+p[j]) {
					mx = s[i-j].sum+p[j];
					mxj = j;
				}
			}
			s[i].sum = mx;
			s[i].cuts = new LinkedList<>(s[i-mxj].cuts);
			s[i].cuts.add(mxj);
		}
		return s[l];
	}
	public static void main(String args[]) {
		try (Scanner sc = new Scanner(System.in)) {
			int l = sc.nextInt();
			int p[] = new int[l+1];
			for (int i=1; i<=l; i++)
				p[i] = sc.nextInt();
			Plan mx = dpSolve(l, p);
			System.out.println(mx.sum);
			for (int i:mx.cuts)
				System.out.print(i+" ");
		}
	}
}
