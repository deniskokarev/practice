package dk.leetcode

import kotlin.random.Random

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

class Solution2_TopKFrequentElements {
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

class Solution__TopKFrequentElements {
    private fun <T> Array<T>.swap(i: Int, j: Int) {
        val t = this[i]
        this[i] = this[j]
        this[j] = t
    }

    /**
     * Comparable Pair
     * (1, 0) < (0, 1)
     * (1, 1) < (1, 0)
     */
    private class MxPair<F: Comparable<F>, S: Comparable<S>>(val first: F, val second: S): Comparable<MxPair<F,S>> {
        override fun compareTo(o: MxPair<F, S>): Int {
            val cmpF = first.compareTo(o.first)
            return if (cmpF != 0) {
                -cmpF
            } else {
                -second.compareTo(o.second)
            }
        }
    }

    /**
     * Partition array between [b, e) 3way based on pivot element originally located at position b
     * return Pair(first, second)
     * [b, first) < pivot
     * [first, second) = pivot
     * [second, e) > pivot
     */
    private fun <T : Comparable<T>> Array<T>.part3(b: Int, e: Int): Pair<Int, Int> {
        val pivot = this[b]
        var m = b
        var i = b
        var j = e - 1
        while (i <= j) {
            if (this[i] < pivot)
                swap(m++, i++)
            else if (pivot < this[i])
                swap(i, j--)
            else
                i++
        }
        return Pair(m, i)
    }

    fun topKFrequent(nums: IntArray, k: Int): IntArray {
        val fq = mutableMapOf<Int, Int>()
        nums.forEach { n ->
            fq[n] = fq.getOrDefault(n, 0) + 1
        }
        val aa = Array(fq.size) { MxPair(0, 0) }
        var i = 0
        fq.forEach { (k, v) ->
            aa[i++] = MxPair(v, k)
        }
        val rnd = Random(1)
        var b = 0
        var e = aa.size
        while (true) {
            val p = b + rnd.nextInt(e - b)
            aa.swap(b, p)
            val (i, j) = aa.part3(b, e)
            if (k > j) {
                b = j
            } else if (k < i) {
                e = i
            } else {
                break
            }
        }
        return IntArray(k) { i -> aa[i].second }
    }
}
