Santa2014
=========

C++ version of Naive Solution

This is an attempt to mimick the Python code provided by Kaggle exactly.

On my system with -O2 optimization it is about 60x faster than the Python code.   There is much one can do to optimize the C++ code to make this faster, as I mostly just translated code as-is.

```
/usr/bin/time ./a.out 900 ../HelpingSantasHelpers/toys_rev2.csv > mysol.csv
44.20user 15.54system 1:00.19elapsed 99%CPU (0avgtext+0avgdata 1500maxresident)k
```

There is also the ability to score submissions:
```
/usr/bin/time ./a.out --score 900 ../HelpingSantasHelpers/toys_rev2.csv < ../HelpingSantasHelpers/sampleSubmission_rev2.csv
1875730155.05752
88.47user 0.46system 1:29.01elapsed 99%CPU (0avgtext+0avgdata 626572maxresident)k
0inputs+0outputs (0major+156697minor)pagefaults 0swaps
```

This version now produces identical output to Kaggle's Python code.

```
rdbisch@mercury:~/work/kaggle/Santa2014$ /usr/bin/time ./a.out 900 ../HelpingSantasHelpers/toys_rev2.csv | ./a.out --score 900 ../HelpingSantasHelpers/toys_rev2.csv
40.80user 4.40system 1:05.41elapsed 69%CPU (0avgtext+0avgdata 1512maxresident)k
0inputs+0outputs (0major+431minor)pagefaults 0swaps
1875730155.05752
```

