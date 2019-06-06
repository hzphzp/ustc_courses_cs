修改实现了RR算法，其中维护两个队列，一个是IO密集队列，一个是CPU密集队列，按照IO占0.8的概率优先IO密集型队列占用CPU，当时间片结束时再次判断当前进程的类型，加入相应队列的尾部，重新调度下一个占用CPU的进程。

```
ZhengYukundeMacBook-Pro:scheduler-homework ZhengYukun$ python scheduler-homework.py -p RR -q 2
ARG policy RR
ARG jobs 10
ARG maxlen 10
ARG seed 0

Here is the job list, with the run time of each job: 
  Job 0 ( length = 9 iotype = 1 )
  Job 1 ( length = 5 iotype = 0 )
  Job 2 ( length = 6 iotype = 0 )
  Job 3 ( length = 8 iotype = 1 )
  Job 4 ( length = 5 iotype = 1 )
  Job 5 ( length = 10 iotype = 1 )
  Job 6 ( length = 3 iotype = 1 )
  Job 7 ( length = 7 iotype = 0 )
  Job 8 ( length = 10 iotype = 1 )
  Job 9 ( length = 9 iotype = 1 )


** Solutions **

Execution trace:
  [ time   0 ] Run job   0 for 2.00 secs
  [ time   2 ] Run job   3 for 2.00 secs
  [ time   4 ] Run job   4 for 2.00 secs
  [ time   6 ] Run job   5 for 2.00 secs
  [ time   8 ] Run job   6 for 2.00 secs
  [ time  10 ] Run job   8 for 2.00 secs
  [ time  12 ] Run job   9 for 2.00 secs
  [ time  14 ] Run job   0 for 2.00 secs
  [ time  16 ] Run job   3 for 2.00 secs
  [ time  18 ] Run job   5 for 2.00 secs
  [ time  20 ] Run job   1 for 2.00 secs
  [ time  22 ] Run job   6 for 1.00 secs ( DONE at 23.00 )
  [ time  23 ] Run job   8 for 2.00 secs
  [ time  25 ] Run job   9 for 2.00 secs
  [ time  27 ] Run job   5 for 2.00 secs
  [ time  29 ] Run job   2 for 2.00 secs
  [ time  31 ] Run job   2 for 2.00 secs
  [ time  33 ] Run job   7 for 2.00 secs
  [ time  35 ] Run job   4 for 2.00 secs
  [ time  37 ] Run job   0 for 2.00 secs
  [ time  39 ] Run job   0 for 2.00 secs
  [ time  41 ] Run job   3 for 2.00 secs
  [ time  43 ] Run job   3 for 2.00 secs ( DONE at 45.00 )
  [ time  45 ] Run job   1 for 2.00 secs
  [ time  47 ] Run job   1 for 1.00 secs ( DONE at 48.00 )
  [ time  48 ] Run job   8 for 2.00 secs
  [ time  50 ] Run job   8 for 2.00 secs
  [ time  52 ] Run job   8 for 2.00 secs ( DONE at 54.00 )
  [ time  54 ] Run job   9 for 2.00 secs
  [ time  56 ] Run job   5 for 2.00 secs
  [ time  58 ] Run job   5 for 2.00 secs ( DONE at 60.00 )
  [ time  60 ] Run job   2 for 2.00 secs ( DONE at 62.00 )
  [ time  62 ] Run job   7 for 2.00 secs
  [ time  64 ] Run job   7 for 2.00 secs
  [ time  66 ] Run job   4 for 1.00 secs ( DONE at 67.00 )
  [ time  67 ] Run job   0 for 1.00 secs ( DONE at 68.00 )
  [ time  68 ] Run job   9 for 2.00 secs
  [ time  70 ] Run job   7 for 1.00 secs ( DONE at 71.00 )
  [ time  71 ] Run job   9 for 1.00 secs ( DONE at 72.00 )

Final statistics:
  Job   0 -- Response: 0.00  Turnaround 68.00  Wait 59.00
  Job   1 -- Response: 20.00  Turnaround 48.00  Wait 43.00
  Job   2 -- Response: 29.00  Turnaround 62.00  Wait 56.00
  Job   3 -- Response: 2.00  Turnaround 45.00  Wait 37.00
  Job   4 -- Response: 4.00  Turnaround 67.00  Wait 62.00
  Job   5 -- Response: 6.00  Turnaround 60.00  Wait 50.00
  Job   6 -- Response: 8.00  Turnaround 23.00  Wait 20.00
  Job   7 -- Response: 33.00  Turnaround 71.00  Wait 64.00
  Job   8 -- Response: 10.00  Turnaround 54.00  Wait 44.00
  Job   9 -- Response: 12.00  Turnaround 72.00  Wait 63.00

  Average -- Response: 12.40  Turnaround 57.00  Wait 49.80
  ```
