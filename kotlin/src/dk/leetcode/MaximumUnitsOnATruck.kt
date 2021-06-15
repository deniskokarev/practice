package dk.leetcode

import kotlin.math.min

class Solution2 {
    fun maximumUnits(boxTypes: Array<IntArray>, truckSize: Int): Int {
        var sz: Int = truckSize
        boxTypes.sortWith(compareBy { it[1] }) // NB!: not sortedWith()
        var tail = boxTypes.size - 1
        var sm = 0
        while (sz > 0 && tail >= 0) {
            // NB! just like in java there is no Array.pop_back()
            val boxes = boxTypes[tail][0]
            val units = boxTypes[tail][1]
            val mayTake = min(sz, boxes)
            sm += mayTake * units
            sz -= mayTake
            tail--
        }
        return sm
    }
}
