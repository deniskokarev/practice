import java.util.ArrayList;
import java.io.*;
import java.util.*;
import java.text.*;
import java.math.*;
import java.util.regex.*;

import java.util.ArrayList;
import java.util.Scanner;

enum Color {
    RED, GREEN
}

abstract class Tree {

    private int value;
    private Color color;
    private int depth;

    public Tree(int value, Color color, int depth) {
        this.value = value;
        this.color = color;
        this.depth = depth;
    }

    public int getValue() {
        return value;
    }

    public Color getColor() {
        return color;
    }

    public int getDepth() {
        return depth;
    }

    public abstract void accept(TreeVis visitor);
}

class TreeNode extends Tree {

    private ArrayList<Tree> children = new ArrayList<>();

    public TreeNode(int value, Color color, int depth) {
        super(value, color, depth);
    }

    public void accept(TreeVis visitor) {
        visitor.visitNode(this);

        for (Tree child : children) {
            child.accept(visitor);
        }
    }

    public void addChild(Tree child) {
        children.add(child);
    }
}

class TreeLeaf extends Tree {

    public TreeLeaf(int value, Color color, int depth) {
        super(value, color, depth);
    }

    public void accept(TreeVis visitor) {
        visitor.visitLeaf(this);
    }
}

abstract class TreeVis
{
    public abstract int getResult();
    public abstract void visitNode(TreeNode node);
    public abstract void visitLeaf(TreeLeaf leaf);

}

class SumInLeavesVisitor extends TreeVis {
	int res = 0;
    public int getResult() {
        return res;
    }

    public void visitNode(TreeNode node) {
    }

    public void visitLeaf(TreeLeaf leaf) {
    	res += leaf.getValue();
    }
}

class ProductOfRedNodesVisitor extends TreeVis {
	public final static int MOD = 1000000000+7;
	long res = 1;
    public int getResult() {
        return (int)res;
    }
    void visit(Tree node) {
      	if (node.getColor() == Color.RED) {
      		res *= node.getValue();
      		res %= MOD;
      	}
    }
    public void visitNode(TreeNode node) {
    	visit(node);
    }

    public void visitLeaf(TreeLeaf leaf) {
    	visit(leaf);
    }
}

class FancyVisitor extends TreeVis {
	long sm1 = 0, sm2 = 0;
    public int getResult() {
        return (int) java.lang.Math.abs(sm1-sm2);
    }

    public void visitNode(TreeNode node) {
    	if ((node.getDepth() & 1) == 0)
    		sm1 += node.getValue();
    }

    public void visitLeaf(TreeLeaf leaf) {
    	if (leaf.getColor() == Color.GREEN)
    		sm2 += leaf.getValue();
    }
}

public class HrJavaVisitorPattern {
	static class E {
		int t;
		E next;
		E(int t, E next) {
			this.t = t;
			this.next = next;
		}
	};
	static Tree dfs(int xx[], Color cc[], E ee[], int r, int par, int depth) {
		TreeNode node = new TreeNode(xx[r], cc[r], depth);
		int nchld = 0;
		for (E chld=ee[r]; chld!=null; chld=chld.next) {
			if (chld.t != par) {
				node.addChild(dfs(xx, cc, ee, chld.t, r, depth+1));
				nchld++;
			}
		}
		if (nchld > 0)
			return node;
		else
			return new TreeLeaf(xx[r], cc[r], depth);
	}
    public static Tree solve() {
    	int n;
		try (Scanner sc = new Scanner(System.in)) {
			n = sc.nextInt();
			int xx[] = new int[n+1];
			Color cc[] = new Color[n+1];
			for (int i=1; i<=n; i++)
				xx[i] = sc.nextInt();
			for (int i=1; i<=n; i++)
				cc[i] = (sc.nextInt()==0) ? Color.RED : Color.GREEN;
			E ee[] = new E[n+1];
			for (int i=0; i<n-1; i++) {
				int u = sc.nextInt();
				int v = sc.nextInt();
				ee[u] = new E(v, ee[u]);
				ee[v] = new E(u, ee[v]);
			}
			return dfs(xx, cc, ee, 1, -1, 0);
		}
	}


    public static void main(String[] args) {
      	Tree root = solve();
		SumInLeavesVisitor vis1 = new SumInLeavesVisitor();
      	ProductOfRedNodesVisitor vis2 = new ProductOfRedNodesVisitor();
      	FancyVisitor vis3 = new FancyVisitor();

      	root.accept(vis1);
      	root.accept(vis2);
      	root.accept(vis3);

      	int res1 = vis1.getResult();
      	int res2 = vis2.getResult();
      	int res3 = vis3.getResult();

      	System.out.println(res1);
     	System.out.println(res2);
    	System.out.println(res3);
	}
}