package dk.leetcode

class Solution_15 {
    private fun strToBitSet(chars: String) = chars
            .asSequence()
            .map {it - 'a'}
            .fold(0) {
                msk, bit -> msk or (1 shl bit)
            }

    private inline fun hasCode(bitSet: Int, ord: Int) = (1 shl ord) and bitSet != 0

    fun customSortString(order: String, str: String): String {
        val bitSet = strToBitSet(order)
        val ordMap = CharArray(26) {idx -> 'a'+idx}
        val mapBack = CharArray(26) {idx -> 'a'+idx}
        var code = 0
        order.forEach { ch ->
            while (!hasCode(bitSet, code))
                code++
            ordMap[ch-'a'] = 'a'+code
            mapBack[code] = ch
            code++
        }
        val res = str
                .map { ch -> ordMap[ch-'a'] }
                .sorted()
                .map { ch -> mapBack[ch-'a'] }
                .toCharArray()
        return String(res)
    }
}
