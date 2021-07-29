package dk.leetcode
// https://leetcode.com/problems/01-matrix/

class Solution_25 {
    class MV(val row: Int, val col: Int, val dist: Int) {
        inline operator fun plus(o: MV): MV = MV(row+o.row, col+o.col, dist+o.dist)
        inline fun inRange(h: Int, w: Int) = row in 0 until h && col in 0 until w
    }

    private val moves = arrayOf(MV(-1, 0, 1), MV(+1, 0, 1), MV(0, -1, 1), MV(0, +1, 1))

    fun updateMatrix(mat: Array<IntArray>): Array<IntArray> {
        val h = mat.size
        val w = mat[0].size
        val queue = ArrayDeque<MV>()
        for (r in 0 until h)
            for (c in 0 until w)
                if (mat[r][c] == 0)
                    queue.addLast(MV(r,c,0))
                else
                    mat[r][c] = Int.MAX_VALUE
        while (!queue.isEmpty()) {
            val pos = queue.removeFirst()
            for (mv in moves) {
                val nPos = pos + mv
                if (nPos.inRange(h, w) && mat[nPos.row][nPos.col] == Int.MAX_VALUE) {
                    mat[nPos.row][nPos.col] = nPos.dist
                    queue.addLast(nPos)
                }
            }
        }
        return mat
    }
}
