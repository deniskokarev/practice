package dk.leetcode
// https://leetcode.com/problems/path-with-minimum-effort/

import java.util.*

class PathWithMinimumEffort_Solution {
    private class D(val d: Int, val hfrom: Int, val t: Pair<Int, Int>)

    fun minimumEffortPath(mm: Array<IntArray>): Int {
        val h = mm.size
        val w = mm[0].size
        val dst = Pair(h - 1, w - 1)
        val seen = Array(h) { Array(w) { false } }
        val qq = PriorityQueue<D>() { d1, d2 -> if (d1.d < d2.d) -1 else +1 }
        qq.add(D(0, mm[0][0], Pair(0, 0)))
        while (qq.isNotEmpty()) {
            val nxt = qq.peek()
            qq.remove()
            if (nxt.t == dst)
                return nxt.d
            if (!seen[nxt.t.first][nxt.t.second]) {
                seen[nxt.t.first][nxt.t.second] = true
                for ((di, dj) in arrayOf(Pair(0, 1), Pair(-1, 0), Pair(0, -1), Pair(1, 0))) {
                    val i = nxt.t.first + di
                    val j = nxt.t.second + dj
                    if (i in 0 until h && j in 0 until w && !seen[i][j]) {
                        qq.add(D(Math.max(nxt.d, Math.abs(nxt.hfrom - mm[i][j])), mm[i][j], Pair(i, j)))
                    }
                }
            }
        }
        return -1
    }
}
