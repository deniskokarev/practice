package dk.leetcode
// https://leetcode.com/problems/decode-string/

class DecodeString {
    /**
     * @param o: output
     * @param s: src string
     * @param pos: current parser pos in s
     * @return final pos for this level of []
     */
    private fun decodeB(o: StringBuilder, s: String, pos: Int): Int {
        val sz = s.length
        var p =  pos
        while (p < sz) {
            val c = s[p]
            if (c.isDigit()) {
                var mul = c - '0'
                p++
                while (p<sz && s[p].isDigit()) {
                    mul *= 10
                    mul += s[p]-'0'
                    p++
                }
                val b = o.length
                p = decodeB(o, s, p+1)
                val e = o.length
                repeat (mul-1) {
                    o.append(o.substring(b, e))
                }
            } else if (c == ']') {
                return p+1
            } else {
                o.append(c)
                p++
            }
        }
        return sz
    }

    fun decodeString(s: String): String {
        val output = StringBuilder()
        decodeB(output, s, 0)
        return output.toString()
    }
}