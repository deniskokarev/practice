package dk.leetcode

// https://leetcode.com/problems/top-k-frequent-elements/

/**
 * Heap that organizes elements by Scores which may be incremented.
 * Each element is identified by K
 * Initially each element gets added with score = 1
 * which may be later incremented by 1 using inc(k)
 */
class IncHeap<K>(k: K) {
    // heap element
    private class P<K>(val k: K, var s: Int)

    // heap with root at pos 1. Position 0 unused to simplify arithmetic
    private val hh = arrayListOf(P(k, -1), P(k, 1))

    // key -> heap pos
    private val k2p = hashMapOf(k to 1)

    private fun swap(i: Int, j: Int) {
        k2p[hh[i].k] = j
        k2p[hh[j].k] = i
        val t = hh[j]
        hh[j] = hh[i]
        hh[i] = t
    }

    // increment element with given k and move it up the heap
    fun inc(k: K) {
        val fnd = k2p[k]
        var chld = if (fnd == null) {
            val p = hh.size
            hh.add(P(k, 0))
            k2p[k] = p
            p
        } else {
            fnd
        }
        hh[chld].s++
        while (chld > 1) {
            val par = chld / 2
            if (hh[par].s < hh[chld].s) {
                swap(par, chld)
            }
            chld = par
        }
    }

    // sieve root element
    private fun sieve() {
        val sz = hh.size
        var r = 1
        while (true) {
            val left = r * 2
            val right = left + 1
            val c = if (right < sz && hh[right].s > hh[left].s) {
                right
            } else if (left < sz) {
                left
            } else {
                break
            }
            if (hh[r].s < hh[c].s) {
                swap(r, c)
                r = c
            } else {
                break
            }
        }
    }

    val size
        get() = hh.size

    // LC kotlin is so old that it doesn't even have removeLast()
    private fun <T> ArrayList<T>.pop() {
        this.removeAt(this.lastIndex)
    }

    fun pop(): K {
        val res = hh[1].k
        swap(1, size - 1)
        hh.pop()
        sieve()
        return res
    }
}

class Solution_TopKFrequentElements {
    fun topKFrequent(nums: IntArray, k: Int): IntArray {
        val hh = IncHeap(nums[0])
        var i = 1
        while (i < nums.size)
            hh.inc(nums[i++])
        val ans = IntArray(k)
        i = 0
        while (i < k)
            ans[i++] = hh.pop()
        return ans
    }
}
