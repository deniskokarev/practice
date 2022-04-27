package dk.leetcode

// https://leetcode.com/problems/min-cost-to-connect-all-points/
import java.util.*

private inline fun Array<IntArray>.dist(i: Int, j: Int): Int {
    val d1 = this[i][0] - this[j][0]
    val d2 = this[i][1] - this[j][1]
    return Math.abs(d1) + Math.abs(d2)
}

class Solution_MinCostToConnectAllPoints {
    class PP(val d: Int, val i: Int, val j: Int) {
        constructor(points: Array<IntArray>, i: Int, j: Int) : this(points.dist(i, j), i, j)
    }

    fun minCostConnectPoints(points: Array<IntArray>): Int {
        val sz = points.size
        val pq = PriorityQueue<PP> { pp1, pp2 ->
            if (pp1.d < pp2.d) {
                -1
            } else {
                +1
            }
        }
        val seen = Array(sz) { false }
        var sm = 0
        var rem = sz - 1
        seen[0] = true
        for (j in points.indices)
            if (!seen[j])
                pq.add(PP(points, 0, j))
        while (rem > 0) {
            val nxt = pq.peek()
            val i = nxt.j
            pq.remove()
            if (!seen[i]) {
                seen[i] = true
                sm += nxt.d
                rem--
                for (j in points.indices)
                    if (!seen[j])
                        pq.add(PP(points, i, j))
            }
        }
        return sm
    }
}
