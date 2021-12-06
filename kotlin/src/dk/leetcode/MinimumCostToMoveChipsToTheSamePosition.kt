// https://leetcode.com/problems/minimum-cost-to-move-chips-to-the-same-position/
package dk.leetcode

class MinimumCostToMoveChipsToTheSamePosition {
    fun minCostToMoveChips(pos: IntArray): Int {
        val eoCnt = arrayOf(0, 0);
        pos.forEach { p ->
            eoCnt[p and 1]++
        }
        return eoCnt.min()!!
    }
}