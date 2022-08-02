package dk.leetcode;

import java.util.ArrayDeque;
import java.util.Deque;

/**
 To help yourself get to and from your bunk every day, write a function called solution(src, dest) which takes in two parameters: the source square, on which you start, and the destination square, which is where you need to land to solve the puzzle.  The function should return an integer representing the smallest number of moves it will take for you to travel from the source square to the destination square using a chess knight's moves (that is, two squares in any direction immediately followed by one square perpendicular to that direction, or vice versa, in an "L" shape).  Both the source and destination squares will be an integer between 0 and 63, inclusive, and are numbered like the example chessboard below:

 -------------------------
 | 0| 1| 2| 3| 4| 5| 6| 7|
 -------------------------
 | 8| 9|10|11|12|13|14|15|
 -------------------------
 |16|17|18|19|20|21|22|23|
 -------------------------
 |24|25|26|27|28|29|30|31|
 -------------------------
 |32|33|34|35|36|37|38|39|
 -------------------------
 |40|41|42|43|44|45|46|47|
 -------------------------
 |48|49|50|51|52|53|54|55|
 -------------------------
 |56|57|58|59|60|61|62|63|
 -------------------------
 */
public class FooBar21Solution {
    static final int DIM = 8;

    private static class P {
        public int i, j, d;

        P(int ai, int aj, int ad) {
            i = ai;
            j = aj;
            d = ad;
        }

        boolean equals(P o) {
            return i == o.i && j == o.j;
        }

        boolean isValid() {
            return i >= 0 && i < DIM && j >= 0 && j < DIM;
        }
    }

    private static P[] mvs;

    static {
        int[] coord = new int[]{-2, -1, 1, 2};
        mvs = new P[8];
        int mi = 0;
        for (int i : coord)
            for (int j : coord)
                if (Math.abs(i) != Math.abs(j))
                    mvs[mi++] = new P(i, j, 1);
    }

    public static int solution(int src, int dest) {
        int dist[][] = new int[DIM][DIM];
        Deque<P> qq = new ArrayDeque();
        P psrc = new P(src / DIM, src % DIM, 1);
        P pdst = new P(dest / DIM, dest % DIM, 0);
        qq.addLast(psrc);
        while (!qq.isEmpty()) {
            P p = qq.pop();
            if (pdst.equals(p)) {
                return p.d - 1;
            } else if (dist[p.i][p.j] == 0) {
                dist[p.i][p.j] = p.d;
                for (P m : mvs) {
                    P np = new P(p.i + m.i, p.j + m.j, p.d + m.d);
                    if (np.isValid() && dist[np.i][np.j] == 0) {
                        qq.addLast(np);
                    }
                }
            }
        }
        throw new IllegalStateException("hmm, 8x8 board must be always traversable");
    }

    public static void main(String args[]) {
        System.out.println(FooBar21Solution.solution(0, 10));
        System.out.println(FooBar21Solution.solution(0, 1));
        System.out.println(FooBar21Solution.solution(19, 36));
    }
}

