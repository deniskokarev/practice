package dk.leetcode

class Solution_GameOfLife {
    private inline fun cntAround(bd: Array<IntArray>, h: Int, w: Int, i: Int, j: Int): Int {
        var cnt = 0
        for (y in i - 1..i + 1)
            for (x in j - 1..j + 1)
                if (y >= 0 && y < h && x >= 0 && x < w)
                    cnt += bd[y][x] and 1
        return cnt - (bd[i][j] and 1)
    }

    fun gameOfLife(bd: Array<IntArray>): Unit {
        val h = bd.size
        val w = bd[0].size
        for (i in 0 until h) {
            for (j in 0 until w) {
                val cnt = cntAround(bd, h, w, i, j)
                val res = when {
                    (cnt < 2) -> 0
                    (cnt == 2) -> bd[i][j] and 1
                    (cnt == 3) -> 1
                    else -> 0
                }
                bd[i][j] = bd[i][j] or (res shl 1)
            }
        }
        for (i in 0 until h)
            for (j in 0 until w)
                bd[i][j] = bd[i][j] shr 1
    }
}
