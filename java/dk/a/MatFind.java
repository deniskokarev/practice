package dk.a;
import java.util.Arrays;
/**
 * Find any word from the dictionary in the NxN matrix (rectangular mat would work too)
 * The word may be traversed in any order, even in repetitive loop
 * The worst-case complexity is NxNx4^M, where M is the longest word in dict
 * @author kokarev
 */
public class MatFind {
	
	static class Trie {
		final static int SZ = 128;
		Trie chld[];
		boolean end;
		Trie() {
			chld = new Trie[SZ];
			end = false;
		}
		Trie goDown(char c) {
			return chld[c%SZ];
		}
		private void append(String s, int pos) {
			int c = s.charAt(pos)%SZ;
			Trie n = chld[c];
			if (n == null) {
				n = new Trie();
				chld[c] = n;
			}
			if (pos < s.length()-1)
				n.append(s, pos+1);
			else
				n.end = true;
		}
		static Trie mkTrie(String dict[]) {
			Trie root = new Trie();
			for (String s:dict)
				root.append(s, 0);
			return root;
		}
	}
	
	static class Point {
		int i, j;
	}
	
	/**
	 * Try to find any word from Trie dictionary in mat[][] array starting at point (i,j)
	 * If the traversal path exists we will populate the visited points
	 * and return their count.
	 * If nothing can be found return 0
	 * @param mat - matrix where we're looking the words
	 * @param i - staring row
	 * @param j - staring col
	 * @param root - trie dictionary
	 * @param loc - the output buffer must be preallocated to hold the biggest word
	 * @param li - should be 0
	 * @return - points count if the result was found or 0 if not
	 */
	static int find(char mat[][], int i, int j, Trie root, Point loc[], int li) {
		if (i<0 || i>=mat.length || j<0 || j>=mat[i].length)
			return 0;
		Trie down = root.goDown(mat[i][j]);
		if (down != null) {
			loc[li].i = i;
			loc[li].j = j;
			if (down.end) {
				return li+1; 
			} else {
				int rc;
				if ((rc=find(mat, i, j+1, down, loc, li+1)) > 0)
					return rc;
				if ((rc=find(mat, i, j-1, down, loc, li+1)) > 0)
					return rc;
				if ((rc=find(mat, i+1, j, down, loc, li+1)) > 0)
					return rc;
				if ((rc=find(mat, i-1, j, down, loc, li+1)) > 0)
					return rc;
				return 0;
			}
		} else {
			return 0;
		}
	}
	
	static void prn(char mat[][], Point p[], int sz) {
		for (int i=0; i<sz; i++)
			System.out.println("["+p[i].i+","+p[i].j+"]='"+mat[p[i].i][p[i].j]+"'");
	}
	
	public static void main(String argv[]) {
		// what to look
		String dict[] = {"122", "125", "987212354"};
		Trie trie = Trie.mkTrie(dict);
		// where to look
		char mat[][] = {
			{'1','2','3'},
			{'2','4','5'},
			{'7','8','9'}
		};
		// the output buffer must be preallocated
		int maxWordLen = Arrays.stream(dict).mapToInt((s)->(s.length())).max().getAsInt();
		Point output[] = new Point[maxWordLen];
		for (int i=0; i<output.length; i++)
			output[i] = new Point();
		// go find
		int rc = -1;
		loop: for (int i=0; i<mat.length; i++) {
			for (int j=0; j<mat[i].length; j++) {
				if ((rc=find(mat, i, j, trie, output, 0)) > 0) {
					prn(mat, output, rc);
					break loop;
				}
			}
		}
		if (rc <= 0)
			System.out.println("Nothing was found");
	}
}
