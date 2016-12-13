package dk.comb;

interface TreapWalker {
	boolean walk(Comparable score, Comparable key, Object v);
}

public class Treap  {
	protected final static int LEFT = 0;
	protected final static int RIGHT = 1;
	
	Treap left, right;
	Comparable score;
	Comparable key;
	Object val;

	public Treap() {
		super();
	}
	
	public Treap(Comparable s, Comparable k, Object v, Treap l, Treap r) {
		super();
		this.score = s;
		this.key = k;
		this.val = v;
		this.left = l;
		this.right = r;
	}
	
	public static Treap merge(Treap l, Treap r) {
		if (l != null && r == null) {
			return l;
		} else if (l == null && r != null) {
			return r;
		} else if (l.score.compareTo(r.score) > 0) {
			l.right = merge(l.right, r);
			return l;
		} else {
			r.left = merge(l, r.left);
			return r;
		}
	}
	
	public void split(Comparable k, Treap lr[]) {
		Treap[] llrr = new Treap[2];
		if (k.compareTo(val) > 0) {
			if (lr[LEFT] != null) {
				left.split(k, llrr);
				lr[LEFT] = llrr[LEFT];
				left = llrr[RIGHT];
				lr[RIGHT] = this;
			} else {
				lr[LEFT] = null;
				lr[RIGHT] = this;
			}
		} else {
			if (lr[RIGHT] != null) {
				right.split(k, llrr);
				lr[LEFT] = this;
				right = llrr[LEFT];
				lr[RIGHT] = llrr[RIGHT];
			} else {
				lr[LEFT] = this;
				lr[RIGHT] = null;
			}
		}
	}

	public static Treap insert(Treap root, Comparable s, Comparable k, Object v) {
		if (root == null) {
			return new Treap(s, k, v, null, null);
		} else {
			if (s.compareTo(root.score) > 0) {
				// insert somewhere below
				if (k.compareTo(root.key) > 0) {
					// down to the left
					if (root.left == null) {
						root.left = new Treap(s, k, v, null, null);
					} else {
						root.left = insert(root.left, s, k, v);
					}
				} else {
					// down to the right
					if (root.right == null) {
						root.right = new Treap(s, k, v, null, null);
					} else {
						root.right = insert(root.right, s, k, v);
					}
				}
				return root;
			} else {
				// insert @ this leObjectel
				Treap[] llrr = new Treap[2];
				root.split(k, llrr);
				return new Treap(s, k, v, llrr[LEFT], llrr[RIGHT]);
			}
		}
	}
	
	public static boolean walk(Treap root, TreapWalker tw) {
		boolean rc;
		if (root != null) {
			if (root.left != null) {
				if (!(rc = walk(root.left, tw)))
					return rc;
			}
			if (!(rc = tw.walk(root.score, root.key, root.val)))
				return rc;
			if (root.right != null) {
				if (!(rc = walk(root.right, tw)))
					return rc;
			}
		}
		return true;
	}
	
	public static void main(String[] args) {
		Treap root = null;
		root = insert(root, new Integer((int)(Math.random()*1024.0)), "1", "1");
		root = insert(root, new Integer((int)(Math.random()*1024.0)), "2", "2");
		root = insert(root, new Integer((int)(Math.random()*1024.0)), "3", "3");
		root = insert(root, new Integer((int)(Math.random()*1024.0)), "4", "4");
		root = insert(root, new Integer((int)(Math.random()*1024.0)), "5", "5");
		walk(root, new TreapWalker() {
			public boolean walk(Comparable score, Comparable key, Object v) {
				System.out.println("score: "+score+" key: "+key+" val: "+v);
				return true;
			}
		});
	}
}
