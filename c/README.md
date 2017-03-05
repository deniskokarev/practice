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

