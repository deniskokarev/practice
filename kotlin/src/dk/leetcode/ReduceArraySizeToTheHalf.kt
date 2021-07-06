package dk.leetcode

// custom heap solution
class Solution_11 {
    private class N(var freq: Int, val v: Int)
    private fun ArrayList<*>.swap(a: Int, b: Int) = java.util.Collections.swap(this, a, b)
    private fun IntArray.swap(a: Int, b: Int) {
        val tmp = this[a]
        this[a] = this[b]
        this[b] = tmp
    }
    private tailrec fun ArrayList<N>.moveUp(node: Int, v2p: IntArray) {
        if (node > 1) {
            val parent = node / 2
            if (this[node].freq > this[parent].freq) {
                this.swap(node, parent)
                v2p.swap(this[node].v, this[parent].v)
                moveUp(parent, v2p)
            }
        }
    }
    private tailrec fun ArrayList<N>.moveDown(node: Int) {
        val sz = this.size
        val l = node*2
        if (l < sz) {
            val r = l + 1
            val c = when {
                (r < sz && this[l].freq < this[r].freq) -> r
                else -> l
            }
            if (this[node].freq < this[c].freq) {
                this.swap(node, c)
                moveDown(c)
            }
        }
    }
    fun minSetSize(arr: IntArray): Int {
        val v2p = IntArray(100_000+1){-1}
        val heap = ArrayList<N>()
        heap.add(N(-1,-1))
        arr.forEach {a ->
            if (v2p[a] == -1) {
                v2p[a] = heap.size
                heap.add(N(0, a))
            }
            val node = v2p[a]
            heap[node].freq++
            heap.moveUp(node, v2p)
        }
        var smFreq = 0
        var ans = 0
        while (heap.size > 0 && smFreq*2 < arr.size) {
            ans++
            smFreq += heap[1].freq
            heap.swap(1, heap.lastIndex)
            heap.removeAt(heap.lastIndex)
            heap.moveDown(1)
        }
        return ans
    }
}
