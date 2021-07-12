package dk.leetcode

class Solution_14 {
    private inline fun oneWayMap(strA: String, strB: String): Boolean {
        val a2b = IntArray(256){-1}
        val aLst = strA.asSequence().map {ch -> ch.toInt()}
        val bLst = strB.asSequence().map {ch -> ch.toInt()}
        aLst.zip(bLst).forEach {(a, b) ->
            if (a2b[a] == -1)
                a2b[a] = b
            if (a2b[a] != b)
                return false
        }
        return true
    }
    fun isIsomorphic(s: String, t: String) = oneWayMap(s, t) && oneWayMap(t ,s)
}
