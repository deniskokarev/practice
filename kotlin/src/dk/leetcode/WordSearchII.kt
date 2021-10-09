package dk.leetcode

class WordSearchII {
    private class TNode(var end: Boolean) {
        val chld = Array<TNode?>(26) { null }
    }

    private fun canMove(board: Array<CharArray>, i: Int, j: Int) =
        (i >= 0 && i < board.size && j >= 0 && j < board[i].size)

    private val MV = arrayOf(Pair(0, -1), Pair(0, +1), Pair(-1, 0), Pair(+1, 0))

    private fun dfs(
        res: MutableSet<String>,
        board: Array<CharArray>,
        i: Int,
        j: Int,
        parent: TNode,
        seen: Array<BooleanArray>,
        path: StringBuffer
    ) {
        if (!seen[i][j]) {
            seen[i][j] = true
            val root = parent.chld[board[i][j] - 'a']
            if (root != null) {
                path.append(board[i][j])
                if (root.end)
                    res.add(path.toString())
                MV.forEach { (di, dj) ->
                    val ni = i + di
                    val nj = j + dj
                    if (canMove(board, ni, nj))
                        dfs(res, board, ni, nj, root, seen, path)
                }
                path.setLength(path.length - 1)
            }
            seen[i][j] = false
        }
    }

    private fun buildTrie(words: Array<String>, root: TNode) {
        words.forEach { word ->
            var r = root
            word.forEach { c ->
                val idx = c - 'a'
                val ri = r.chld[idx]
                if (ri == null) {
                    val nr = TNode(false)
                    r.chld[idx] = nr
                    r = nr
                } else {
                    r = ri
                }
            }
            r.end = true
        }
    }

    fun findWords(board: Array<CharArray>, words: Array<String>): List<String> {
        val root = TNode(false)
        buildTrie(words, root)
        val seen = Array(board.size) {
            BooleanArray(board[0].size) {false}
        }
        val res = mutableSetOf<String>()
        val path = StringBuffer()
        for (i in board.indices)
            for (j in board[i].indices)
                dfs(res, board, i, j, root, seen, path)
        return res.toList()
    }
}
