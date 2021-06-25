package dk.leetcode

const val MOD = 1_000_000_007

class Solution_6 {
    fun findPaths(rows: Int, cols: Int, maxMove: Int, startRow: Int, startColumn: Int): Int {
        // BFS with repetitive visitations
        var count = Array(rows) { Array(cols) { 0 } }
        // every point will be in our bfs queue very quickly
        var waveFront = Array(rows) { Array(cols) { false } }
        count[startRow][startColumn] = 1
        waveFront[startRow][startColumn] = true
        var sm = 0L
        repeat(maxMove) {
            val newCount = Array(rows) { Array(cols) { 0 } }
            val newWaveFront = Array(rows) { Array(cols) { false } }
            for (r in count.indices) {
                for (c in count[r].indices) {
                    if (waveFront[r][c]) {
                        for (mv in arrayOf(Pair(+1, 0), Pair(-1, 0), Pair(0, +1), Pair(0, -1))) {
                            val nr = r + mv.first
                            val nc = c + mv.second
                            if (nr in 0 until rows && nc in 0 until cols) {
                                newWaveFront[nr][nc] = true
                                newCount[nr][nc] += count[r][c]
                                newCount[nr][nc] %= MOD
                            } else {
                                sm += count[r][c]
                            }
                        }
                    }
                }
            }
            count = newCount
            waveFront = newWaveFront
            sm %= MOD
        }
        return sm.toInt()
    }
}
