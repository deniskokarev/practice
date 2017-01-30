package dk.draft;

public class MatMulDPOptim {

	/**
	 * TODO add cache to bestMul to take advantage of DP
	 * @author kokarev
	 */
	static class Expr {
		Expr l, r;
		int x, y;
		int cost;
		Expr(int x, int y) {
			this.x = x;
			this.y = y;
		}
		Expr() {
		}
	}
	
	static Expr costMul(Expr l, Expr r, Expr res) {
		if (l.x == 0)
			return r;
		if (r.x == 0)
			return l;
		if (l.y != r.x)
			return null;
		res.x = l.x;
		res.y = r.y;
		res.cost = l.cost + r.cost + l.x*r.x*r.y;
		res.l = l;
		res.r = r;
		return res;
	}
	
	static Expr bestMul(Expr a[], int f, int t, Expr mn) {
		if (f+1 >= t) {
			return a[f];
		} else {
			mn.x = 0;
			mn.cost = Integer.MAX_VALUE;
			for (int i=f; i<t-1; i++) {
				Expr l = bestMul(a, f, i+1, new Expr());
				Expr r = bestMul(a, i+1, t, new Expr());
				Expr e = costMul(l, r, new Expr());
				if (mn.cost > e.cost)
					mn = e;
			}
			return mn;
		}
	}

	static void prn(Expr e, int ind) {
		if (e.l != null)
			prn(e.l, ind+1);
		for (int i=0; i<ind; i++)
			System.out.print("  ");
		System.out.println(e.x+":"+e.y+"(cost: "+e.cost+")");
		if (e.r != null)
			prn(e.r, ind+1);
	}
	public static void main(String[] args) {
		Expr m[] = new Expr[]{new Expr(30, 35), new Expr(35, 15), new Expr(15, 5), new Expr(5, 10), new Expr(10, 20), new Expr(20, 25)}; 
		prn(bestMul(m, 0, m.length, new Expr()), 0); 
	}
}
