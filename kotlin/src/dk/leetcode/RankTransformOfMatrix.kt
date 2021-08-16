package dk.leetcode
// https://leetcode.com/problems/rank-transform-of-a-matrix/

// CPU: O(h * w * log(h * w))
// Mem: O(h * w)

// Join all equal elements that are connected via columns or rows
// Each node may have upto 2 children by row and column that are strictly less.
// The graph may have more than 1 connected components. Each component will be a DAG
// with >= 1 roots and >= 1 leafs. We will be walking the graph in "less than"
// direction and finding max depth at each level.
// All nodes connected by equality must have the same level (max of them)
class Solution_33 {
    private class Node(val v: Int) {
        var rank = Int.MIN_VALUE
        var ltChildByRow: Node? = null
        var ltChildByCol: Node? = null
        private var nextEq = this // next in linked loop of elements equal by row or col
        private var dsuRoot = this // must use DSU as simple merging lists twice breaks the loop

        private fun getRoot(): Node {
            if (dsuRoot !== this)
                dsuRoot = dsuRoot.getRoot()
            return dsuRoot
        }

        fun mergeEq(o: Node) {
            if (getRoot() !== o.getRoot()) {
                val l = nextEq
                val ol = o.nextEq
                o.nextEq = l
                nextEq = ol
                dsuRoot.dsuRoot = o.dsuRoot
            }
        }

        fun forEachEq(lambda: (it: Node) -> Unit) {
            var node = this
            do {
                lambda(node)
                node = node.nextEq
            } while (node !== this)
        }
    }

    private fun dfsRankLt(node: Node?): Int = if (node != null) dfsRankEq(node) else 0

    // rank all equal nodes at the given layer
    private fun dfsRankEq(node: Node): Int {
        if (node.rank == Int.MIN_VALUE) {
            var mxRankLt = 0
            node.forEachEq { mxRankLt = maxOf(mxRankLt, dfsRankLt(it.ltChildByCol), dfsRankLt(it.ltChildByRow)) }
            node.forEachEq { it.rank = mxRankLt + 1 }
        }
        return node.rank
    }

    private fun buildRankGraph(matrix: Array<IntArray>): Array<Array<Node>> {
        val height = matrix.size
        val width = matrix[0].size
        val rankGraph = Array(height) { r -> Array(width) { c -> Node(matrix[r][c]) } }
        // build the graph
        for (c in 0 until width) {
            val col = Array(height) { r -> rankGraph[r][c] }.sortedBy { it.v }
            var lt: Node? = null
            for (i in 1 until height) {
                if (col[i - 1].v == col[i].v)
                    col[i - 1].mergeEq(col[i])
                else
                    lt = col[i - 1]
                col[i].ltChildByCol = lt
            }
        }
        for (r in 0 until height) {
            val row = Array(width) { c -> rankGraph[r][c] }.sortedBy { it.v }
            var lt: Node? = null
            for (i in 1 until width) {
                if (row[i - 1].v == row[i].v)
                    row[i - 1].mergeEq(row[i])
                else
                    lt = row[i - 1]
                row[i].ltChildByRow = lt
            }
        }
        return rankGraph
    }

    fun matrixRankTransform(matrix: Array<IntArray>): Array<IntArray> {
        val height = matrix.size
        val width = matrix[0].size
        val rankGraph = buildRankGraph(matrix)
        rankGraph.forEach { r -> r.forEach { el -> dfsRankEq(el) } }
        return Array(height) { r -> IntArray(width) { c -> rankGraph[r][c].rank } }
    }
}
