# High precision, high frequency periodic timer demo

This small repository contains C files that demonstrate the two ways of creating a periodic timer. The first approach is based on sleep the second is based constantly checking the time to see when to trigger.

To build the two binaries:
```
$ cd src
$ make
```

To run the executables:
```
$ ./bin/bytimecheck 20000 30 res.csv
```
which will run a time check based periodic timer for 30 seconds. The frequency of triggers is 20000, i.e. 20000 events per second and the planned and actual trigger times are saved in file `res.csv`. Run `./bin/bysleep` for a sleep based timer.

The program will output a few useful information, e.g the planned delays between triggers and the average of actal and planned delays. You can get a full distribution of the delays, .e.g by a simple q process:

```
$ q
q) \l utils/csvutil.q
q) t: .csv.read `res.csv
q) update rate: nr % sum nr from select nr: count i by 1000 xbar latency from t
latency| nr      rate
-------| ----------------
0      | 4991570 0.998314
1000   | 443     8.86e-05
2000   | 139     2.78e-05
3000   | 47      9.4e-06
...
```
