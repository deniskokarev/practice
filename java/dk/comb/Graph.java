package dk.comb;

import java.util.Arrays;

public class Graph {
	/**
	 * FIFO ringbuffer of ints
	 * sz should be 1 greater of what you want to store
	 * @author kokarev
	 */
	static class FifoQInt {
		int head, tail;
		int sz;
		int emptyInd;	// special value that we return if our Q is empty
		int buf[];
		
		FifoQInt(int sz) {
			this(sz, -1);
		}
		FifoQInt(int sz, int emptyInd) {
			this.emptyInd = emptyInd;
			this.sz = sz;
			buf = new int[sz];
		}
		int size() {
			return (head+sz-tail)%sz;
		}
		int avail() {
			return sz-size()-1;
		}
		boolean put(int v) {
			int n = (head+1)%sz; 
			if (n != tail) {
				buf[head] = v;
				head = n;
				return true;
			} else {
				return false;
			}
		}
		int get() {
			if (tail != head) {
				int v = buf[tail];
				tail = (tail+1)%sz;
				return v;
			} else {
				return emptyInd;
			}
		}
	}

	/**
	 * Take a graph and return list of its connected components
	 * @param graph is given as a list of edges where graph[i][?] == j denotes edge i->j
	 * @return list of connected components meaning [n][v] - vertice v belongs to connected component number n 
	 */
	static int[][] connectedComponents(int graph[][]) {
		final int EMPTY = -1;
		FifoQInt q = new FifoQInt(graph.length+1, EMPTY);
		int vis[] = new int[graph.length];
		int cnts[] = new int[graph.length+1];
		int cnt = 0;
		for (int p=0; p<graph.length; p++) {
			if (vis[p] == 0) {
				cnt++;
				q.put(p);
				for (int v = q.get(); v != EMPTY; v = q.get()) {
					if (vis[v] == 0) {
						vis[v] = cnt;
						cnts[cnt]++;
						if (graph[v] != null)
							for (int c:graph[v])
								q.put(c);
					}
				}
			}
		}
		int res[][] = new int[cnt][];
		for (int i=0; i<res.length; i++)
			res[i] = new int[cnts[i+1]];
		Arrays.fill(cnts, 0);
		int c;
		for (int p=0; p<graph.length; p++) {
			c = vis[p]-1; 
			res[c][cnts[c]++] = p;
		}
		return res;
	}
}
