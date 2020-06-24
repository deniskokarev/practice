// https://leetcode.com/problems/power-of-three/

template<int B, int64_t V, bool IS_MAX> struct _IMAXPOW {
    static constexpr int64_t value = _IMAXPOW<B, B*V, (B*V > INT_MAX)>::value;
};

template<int B, int64_t V> struct _IMAXPOW<B,V,true> {
    static constexpr int64_t value = V/B;
};

// return max pow of BASE that still fits INT_MAX
template<int BASE> constexpr int imaxpow() {
    return _IMAXPOW<BASE,1,false>::value; 
}

class Solution {
public:
    bool isPowerOfThree(int n) {
        return n > 0 && !(imaxpow<3>()%n);
    }
};
