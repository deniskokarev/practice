#lldb hints

Typical commands
https://lldb.llvm.org/lldb-gdb.html
Or
https://developer.apple.com/library/content/documentation/IDEs/Conceptual/gdb_to_lldb_transition_guide/document/lldb-command-examples.html

Inspect element of the vector
```
(lldb) expr vector.__begin_[0]
(lldb) p vector.__begin_[0]
```

Take input from a file
```
(lldb) settings set target.input-path /tmp/f2
```

# floating point output
```
cout << setprecision(9) << t << endl;
```

# don't forget to
```
#include <algorithm>
```

# GNU stdlibc++ is so lousy that you have to customize hash functions for ints
```
#include <unordered_map>

struct myhashi64 {
	size_t operator()(int64_t x) const {
		x = (x ^ (x >> 30)) * UINT64_C(0xbf58476d1ce4e5b9);
		x = (x ^ (x >> 27)) * UINT64_C(0x94d049bb133111eb);
		x = x ^ (x >> 31);
		return x;
	}
};

unordered_map<int64_t, int64_t, myhashi64> mymap;

```
