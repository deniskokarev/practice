package dk.leetcode

class Solution3 {
    class SmMsk(val sum: Long, val msk: Int)

    fun makesquare(matchsticks: IntArray): Boolean {
        val sz = matchsticks.size
        val totalLen: Long = matchsticks.fold(0L) {sm, el -> sm + el}
        if ((totalLen and 3L) != 0L)
            return false
        val qLen = totalLen shr 2
        val p2sz = 1 shl sz
        // valid one side combinations
        val fits = BooleanArray(p2sz) {
            msk -> matchsticks.fold(SmMsk(0, msk)) {sm, el -> SmMsk(sm.sum + el * (sm.msk and 1), sm.msk shr 1)}.sum == qLen
        }
        // match 2 sides from 1s (can emplace result into same fits[] array)
        // no more than 3^sz iterations altogether
        for (msk in p2sz-1 downTo 0) {
            if (fits[msk]) {
                val neg = msk.inv()
                var cmsk = (p2sz - 1) and neg // complementary mask to msk
                while (cmsk != 0) {
                    fits[msk or cmsk] = fits[msk or cmsk] || fits[cmsk]
                    cmsk = (cmsk - 1) and neg
                }
            }
        }
        // match 2 and 2 sides
        for (msk in 0 until p2sz) {
            val nmsk = msk.inv() and (p2sz-1)
            if (fits[msk] && fits[nmsk])
                return true
        }
        return false
    }
}
