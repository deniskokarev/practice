package dk.leetcode
// https://leetcode.com/problems/map-sum-pairs/

class MapSum() {
    // export-friendly trie
    private class Node(var v: Int, var sm: Int) {
        val nxt = IntArray(26)
    }

    private val nodes = ArrayList<Node>().apply {
        add(Node(0,0))
        add(Node(0,0)) // root starts with ofs=1
    }

    fun insert(key: String, v: Int) {
        var root = 1
        val path = arrayListOf(root) // instead of recursion
        key.forEach { c ->
            val idx = c - 'a'
            if (nodes[root].nxt[idx] == 0) {
                nodes[root].nxt[idx] = nodes.size
                nodes.add(Node(0, 0))
            }
            root = nodes[root].nxt[idx]
            path.add(root)
        }
        val diff = v - nodes[root].v
        nodes[root].v = v
        path.forEach { node -> nodes[node].sm += diff }
    }

    fun sum(prefix: String): Int {
        var root = 1
        prefix.forEach { c ->
            root = nodes[root].nxt[c - 'a'] // not-found stays at Node 0
        }
        return nodes[root].sm
    }
}
