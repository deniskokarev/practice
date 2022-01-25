package dk.leetcode
// https://leetcode.com/problems/valid-mountain-array/

class ValidMountainArray {
    fun validMountainArray(arr: IntArray): Boolean {
        val sz = arr.size
        var i = 1
        if (i < sz && arr[i-1] < arr[i]) {
            while (i < sz && arr[i-1] < arr[i])
                i++
            if (i < sz && arr[i-1] > arr[i]) {
                while (i < sz && arr[i-1] > arr[i])
                    i++
                return (i == sz)
            }
        }
        return false
    }
}