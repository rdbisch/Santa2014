Santa2014
=========

C++ version of Naive Solution

This is an attempt to mimick the Python code provided by Kaggle exactly.

On my system with -O2 optimization it is about 60x faster than the Python code.   There is much one can do to optimize the C++ code to make this faster, as I mostly just translated code as-is.

```
/usr/bin/time ./a.out 900 ../HelpingSantasHelpers/toys_rev2.csv > mysol.csv
44.20user 15.54system 1:00.19elapsed 99%CPU (0avgtext+0avgdata 1500maxresident)k
```

It's not quite there yet as the output of the programs start to differ unexpectedly around the 2.3 million toys in--

```
My Code                        | Kaggle
2308746,14,2014 5 27 9 0,8     | 2308746,151,2014 5 26 19 0,124
2308747,107,2014 5 27 9 0,19   | 2308747,14,2014 5 27 9 0,11
2308748,151,2014 5 27 9 0,184  | 2308748,107,2014 5 27 9 0,21
```

shortly after this, the differences above cascade and they become completely different.  

Note that this output from Kaggle was produced by modified Python Naive Solution that differs only slightly from the official version:

```
28c29
<         heapq.heappush(list_elves, (elf.next_available_time, elf))
---
>         heapq.heappush(list_elves, (elf.next_available_time, elf.id, elf))
```

and

```
>             # put elf back in heap
>             heapq.heappush(myelves, (current_elf.next_available_time, current_elf.id, current_elf))
```

This was to make the priority queue order the same between implementations.
