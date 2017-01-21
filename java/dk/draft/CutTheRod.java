package dk.draft;

import java.util.LinkedList;
import java.util.List;
import java.util.Scanner;

public class CutTheRod {
	/**
	 * Cutting plan that we need to return together with cost
	 * @author kokarev
	 */
	static class Plan {
		List<Integer> cuts;
		int sum;
		Plan() {
			cuts = null;
			sum = 0;
		}
	}
	
	/**
	 * Intuitive recursive Top-to-bottom solution
	 * where natural 2^(l-1) complexity improves to l^2
	 * simply by using caching
	 * @param l
	 * @param p
	 * @return
	 */
	static Plan dpSolveTop2Bottom(int l, int p[]) {
		Plan s[] = new Plan[l+1];
		for (int i=0; i<s.length; i++)
			s[i] = new Plan();
		s[0].cuts = new LinkedList<>();
		return dpSolveRec(l, p, s);
	}
	static Plan dpSolveRec(int l, int p[], Plan s[]) {
		if (s[l].cuts == null) {
			int mxi = l, mx = p[l];
			Plan mxPlan = s[0];
			for (int i=l-1; i>0; i--) {
				Plan lc = dpSolveRec(l-i, p, s);
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
	/**
	 * Bottom-Up loop based solution where
	 * we iterate over each length i and for each i
	 * trying to remove piece of size j and check if that gives us
	 * best solution after adding p[j] back
	 * The optimal solution for smaller rod of length i-j should
	 * already be calculated prior
	 * @param l
	 * @param p
	 * @return
	 */
	static Plan dpSolveLoop(int l, int p[]) {
		Plan s[] = new Plan[l+1];
		for (int i=0; i<s.length; i++)
			s[i] = new Plan();
		s[0].cuts = new LinkedList<>();
		// iterate over all possible rod lengths in bottom up fashion
		for (int i=1; i<=l; i++) {
			// for each rod of length i we try to cut away j long piece
			// and see if that combined with p[j] gives us best solution.
			// i-j optimal solution is already known
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
	
	/**
	 * Input is two lines:
	 * 1) length
	 * 2) the correspondent cost of all pieces 1..length respectively
	 * E.g.:
	 * 10
	 * 1 5 8 9 10 17 17 20 24 25
	 * The output is the optimal cost and the 'cutting' plan - how many of each piece
	 * 27
	 * 2 2 6 
	 * @param args
	 */
	public static void main(String args[]) {
		try (Scanner sc = new Scanner(System.in)) {
			int l = sc.nextInt();
			int p[] = new int[l+1];
			for (int i=1; i<=l; i++)
				p[i] = sc.nextInt();
			Plan mx = dpSolveLoop(l, p);
			System.out.println(mx.sum);
			for (int i:mx.cuts)
				System.out.print(i+" ");
		}
	}
}
