## 小组思考题

2. （spoc)了解race condition. 进入[race-condition代码目录](https://github.com/chyyuu/ucore_lab/tree/master/related_info/lab7/race-condition)。

 - 执行 `./x86.py -p loop.s -t 1 -i 100 -R dx`， 请问`dx`的值是什么？
  
 ```
    dx          Thread 0         
    0   
   -1   1000 sub  $1,%dx
   -1   1001 test $0,%dx
   -1   1002 jgte .top
   -1   1003 halt
 ```
 
 - 执行 `./x86.py -p loop.s -t 2 -i 100 -a dx=3,dx=3 -R dx` ， 请问`dx`的值是什么？

 ```
   dx          Thread 0                Thread 1         
    3   
    2   1000 sub  $1,%dx
    2   1001 test $0,%dx
    2   1002 jgte .top
    1   1000 sub  $1,%dx
    1   1001 test $0,%dx
    1   1002 jgte .top
    0   1000 sub  $1,%dx
    0   1001 test $0,%dx
    0   1002 jgte .top
   -1   1000 sub  $1,%dx
   -1   1001 test $0,%dx
   -1   1002 jgte .top
   -1   1003 halt
    3   ----- Halt;Switch -----  ----- Halt;Switch -----  
    2                            1000 sub  $1,%dx
    2                            1001 test $0,%dx
    2                            1002 jgte .top
    1                            1000 sub  $1,%dx
    1                            1001 test $0,%dx
    1                            1002 jgte .top
    0                            1000 sub  $1,%dx
    0                            1001 test $0,%dx
    0                            1002 jgte .top
   -1                            1000 sub  $1,%dx
   -1                            1001 test $0,%dx
   -1                            1002 jgte .top
   -1                            1003 halt
 ```

 - 执行 `./x86.py -p loop.s -t 2 -i 3 -r -a dx=3,dx=3 -R dx`， 请问`dx`的值是什么？

 ```
    dx          Thread 0                Thread 1         
    3   
    2   1000 sub  $1,%dx
    3   ------ Interrupt ------  ------ Interrupt ------  
    2                            1000 sub  $1,%dx
    2                            1001 test $0,%dx
    2   ------ Interrupt ------  ------ Interrupt ------  
    2   1001 test $0,%dx
    2   1002 jgte .top
    1   1000 sub  $1,%dx
    2   ------ Interrupt ------  ------ Interrupt ------  
    2                            1002 jgte .top
    1   ------ Interrupt ------  ------ Interrupt ------  
    1   1001 test $0,%dx
    1   1002 jgte .top
    0   1000 sub  $1,%dx
    2   ------ Interrupt ------  ------ Interrupt ------  
    1                            1000 sub  $1,%dx
    1                            1001 test $0,%dx
    1                            1002 jgte .top
    0   ------ Interrupt ------  ------ Interrupt ------  
    0   1001 test $0,%dx
    0   1002 jgte .top
   -1   1000 sub  $1,%dx
    1   ------ Interrupt ------  ------ Interrupt ------  
    0                            1000 sub  $1,%dx
    0                            1001 test $0,%dx
   -1   ------ Interrupt ------  ------ Interrupt ------  
   -1   1001 test $0,%dx
   -1   1002 jgte .top
   -1   1003 halt
    0   ----- Halt;Switch -----  ----- Halt;Switch -----  
    0   ------ Interrupt ------  ------ Interrupt ------  
    0                            1002 jgte .top
   -1                            1000 sub  $1,%dx
   -1   ------ Interrupt ------  ------ Interrupt ------  
   -1                            1001 test $0,%dx
   -1                            1002 jgte .top
   -1   ------ Interrupt ------  ------ Interrupt ------  
   -1                            1003 halt
 ```

 - 变量x的内存地址为2000, `./x86.py -p looping-race-nolock.s -t 1 -M 2000`, 请问变量x的值是什么？

 ```
 2000      bx          Thread 0         
    0       0   
    0       0   1000 mov 2000, %ax
    0       0   1001 add $1, %ax
    1       0   1002 mov %ax, 2000
    1      -1   1003 sub  $1, %bx
    1      -1   1004 test $0, %bx
    1      -1   1005 jgt .top
    1      -1   1006 halt
 ```

 - 变量x的内存地址为2000, `./x86.py -p looping-race-nolock.s -t 2 -a bx=3 -M 2000`, 请问变量x的值是什么？为何每个线程要循环3次？

 因为程序等效于for(int bx = 3;bx > 0;bx--){...}，所以循环三次。

 ```
  2000      bx          Thread 0                Thread 1         
    0       3   
    0       3   1000 mov 2000, %ax
    0       3   1001 add $1, %ax
    1       3   1002 mov %ax, 2000
    1       2   1003 sub  $1, %bx
    1       2   1004 test $0, %bx
    1       2   1005 jgt .top
    1       2   1000 mov 2000, %ax
    1       2   1001 add $1, %ax
    2       2   1002 mov %ax, 2000
    2       1   1003 sub  $1, %bx
    2       1   1004 test $0, %bx
    2       1   1005 jgt .top
    2       1   1000 mov 2000, %ax
    2       1   1001 add $1, %ax
    3       1   1002 mov %ax, 2000
    3       0   1003 sub  $1, %bx
    3       0   1004 test $0, %bx
    3       0   1005 jgt .top
    3       0   1006 halt
    3       3   ----- Halt;Switch -----  ----- Halt;Switch -----  
    3       3                            1000 mov 2000, %ax
    3       3                            1001 add $1, %ax
    4       3                            1002 mov %ax, 2000
    4       2                            1003 sub  $1, %bx
    4       2                            1004 test $0, %bx
    4       2                            1005 jgt .top
    4       2                            1000 mov 2000, %ax
    4       2                            1001 add $1, %ax
    5       2                            1002 mov %ax, 2000
    5       1                            1003 sub  $1, %bx
    5       1                            1004 test $0, %bx
    5       1                            1005 jgt .top
    5       1                            1000 mov 2000, %ax
    5       1                            1001 add $1, %ax
    6       1                            1002 mov %ax, 2000
    6       0                            1003 sub  $1, %bx
    6       0                            1004 test $0, %bx
    6       0                            1005 jgt .top
    6       0                            1006 halt
 ```

 - 变量x的内存地址为2000, `./x86.py -p looping-race-nolock.s -t 2 -M 2000 -i 4 -r -s 0`， 请问变量x的值是什么？

 ```
 2000      bx          Thread 0                Thread 1         
    0       0   
    0       0   1000 mov 2000, %ax
    0       0   ------ Interrupt ------  ------ Interrupt ------  
    0       0                            1000 mov 2000, %ax
    0       0                            1001 add $1, %ax
    1       0                            1002 mov %ax, 2000
    1       0   ------ Interrupt ------  ------ Interrupt ------  
    1       0   1001 add $1, %ax
    1       0   1002 mov %ax, 2000
    1      -1   1003 sub  $1, %bx
    1      -1   1004 test $0, %bx
    1       0   ------ Interrupt ------  ------ Interrupt ------  
    1      -1                            1003 sub  $1, %bx
    1      -1                            1004 test $0, %bx
    1      -1   ------ Interrupt ------  ------ Interrupt ------  
    1      -1   1005 jgt .top
    1      -1   ------ Interrupt ------  ------ Interrupt ------  
    1      -1                            1005 jgt .top
    1      -1                            1006 halt
    1      -1   ----- Halt;Switch -----  ----- Halt;Switch -----  
    1      -1   1006 halt
 ```

 - 变量x的内存地址为2000, `./x86.py -p looping-race-nolock.s -t 2 -M 2000 -i 4 -r -s 1`， 请问变量x的值是什么？

 ```
  2000      bx          Thread 0                Thread 1         
    0       0   
    0       0   1000 mov 2000, %ax
    0       0   1001 add $1, %ax
    0       0   ------ Interrupt ------  ------ Interrupt ------  
    0       0                            1000 mov 2000, %ax
    0       0                            1001 add $1, %ax
    0       0   ------ Interrupt ------  ------ Interrupt ------  
    1       0   1002 mov %ax, 2000
    1      -1   1003 sub  $1, %bx
    1      -1   1004 test $0, %bx
    1       0   ------ Interrupt ------  ------ Interrupt ------  
    1       0                            1002 mov %ax, 2000
    1      -1   ------ Interrupt ------  ------ Interrupt ------  
    1      -1   1005 jgt .top
    1      -1   1006 halt
    1       0   ----- Halt;Switch -----  ----- Halt;Switch -----  
    1       0   ------ Interrupt ------  ------ Interrupt ------  
    1      -1                            1003 sub  $1, %bx
    1      -1                            1004 test $0, %bx
    1      -1   ------ Interrupt ------  ------ Interrupt ------  
    1      -1                            1005 jgt .top
    1      -1                            1006 halt
 ```


 - 变量x的内存地址为2000, `./x86.py -p looping-race-nolock.s -t 2 -M 2000 -i 4 -r -s 2`， 请问变量x的值是什么？ 

 ```
  2000      bx          Thread 0                Thread 1         
    0       0   
    0       0   1000 mov 2000, %ax
    0       0   1001 add $1, %ax
    1       0   1002 mov %ax, 2000
    1      -1   1003 sub  $1, %bx
    1       0   ------ Interrupt ------  ------ Interrupt ------  
    1       0                            1000 mov 2000, %ax
    1       0                            1001 add $1, %ax
    1      -1   ------ Interrupt ------  ------ Interrupt ------  
    1      -1   1004 test $0, %bx
    1      -1   1005 jgt .top
    1       0   ------ Interrupt ------  ------ Interrupt ------  
    2       0                            1002 mov %ax, 2000
    2      -1                            1003 sub  $1, %bx
    2      -1                            1004 test $0, %bx
    2      -1   ------ Interrupt ------  ------ Interrupt ------  
    2      -1   1006 halt
    2      -1   ----- Halt;Switch -----  ----- Halt;Switch -----  
    2      -1                            1005 jgt .top
    2      -1                            1006 halt
 ```


 - 变量x的内存地址为2000, `./x86.py -p looping-race-nolock.s -a bx=1 -t 2 -M 2000 -i 1`， 请问变量x的值是什么？ 

 ```
  2000      bx          Thread 0                Thread 1         
    0       1   
    0       1   1000 mov 2000, %ax
    0       1   ------ Interrupt ------  ------ Interrupt ------  
    0       1                            1000 mov 2000, %ax
    0       1   ------ Interrupt ------  ------ Interrupt ------  
    0       1   1001 add $1, %ax
    0       1   ------ Interrupt ------  ------ Interrupt ------  
    0       1                            1001 add $1, %ax
    0       1   ------ Interrupt ------  ------ Interrupt ------  
    1       1   1002 mov %ax, 2000
    1       1   ------ Interrupt ------  ------ Interrupt ------  
    1       1                            1002 mov %ax, 2000
    1       1   ------ Interrupt ------  ------ Interrupt ------  
    1       0   1003 sub  $1, %bx
    1       1   ------ Interrupt ------  ------ Interrupt ------  
    1       0                            1003 sub  $1, %bx
    1       0   ------ Interrupt ------  ------ Interrupt ------  
    1       0   1004 test $0, %bx
    1       0   ------ Interrupt ------  ------ Interrupt ------  
    1       0                            1004 test $0, %bx
    1       0   ------ Interrupt ------  ------ Interrupt ------  
    1       0   1005 jgt .top
    1       0   ------ Interrupt ------  ------ Interrupt ------  
    1       0                            1005 jgt .top
    1       0   ------ Interrupt ------  ------ Interrupt ------  
    1       0   1006 halt
    1       0   ----- Halt;Switch -----  ----- Halt;Switch -----  
    1       0   ------ Interrupt ------  ------ Interrupt ------  
    1       0                            1006 halt
 ```

3. （spoc） 了解software-based lock, hardware-based lock, [software-hardware-lock代码目录](https://github.com/chyyuu/ucore_lab/tree/master/related_info/lab7/software-hardware-locks)

  - 理解flag.s,peterson.s,test-and-set.s,ticket.s,test-and-test-and-set.s 请通过x86.py分析这些代码是否实现了锁机制？请给出你的实验过程和结论说明。能否设计新的硬件原子操作指令Compare-And-Swap,Fetch-And-Add？

  - flag.s:不能实现，原因如下：
  
  ```
  ZhengYukundeMBP:software-hardware-locks ZhengYukun$ ./x86.py -p flag.s -t 2 -i 1 -r -R bx,ax -c 

   bx    ax          Thread 0                Thread 1         

    0     0   
    0     0   1000 mov  flag, %ax
    0     0   ------ Interrupt ------  ------ Interrupt ------  
    0     0                            1000 mov  flag, %ax
    0     0   ------ Interrupt ------  ------ Interrupt ------  
    0     0   1001 test $0, %ax
    0     0   ------ Interrupt ------  ------ Interrupt ------  
    0     0                            1001 test $0, %ax
    0     0   ------ Interrupt ------  ------ Interrupt ------  
    0     0   1002 jne  .acquire
    0     0   ------ Interrupt ------  ------ Interrupt ------  
    0     0                            1002 jne  .acquire
    0     0   ------ Interrupt ------  ------ Interrupt ------  
    0     0   1003 mov  $1, flag
    0     0   ------ Interrupt ------  ------ Interrupt ------  
    0     0                            1003 mov  $1, flag
    0     0   ------ Interrupt ------  ------ Interrupt ------  
    0     0   1004 mov  count, %ax
    0     0   ------ Interrupt ------  ------ Interrupt ------  
    0     0                            1004 mov  count, %ax
    0     0   ------ Interrupt ------  ------ Interrupt ------  
    0     1   1005 add  $1, %ax
    0     0   ------ Interrupt ------  ------ Interrupt ------  
    0     1                            1005 add  $1, %ax
    0     1   ------ Interrupt ------  ------ Interrupt ------  
    0     1   1006 mov  %ax, count
    0     1   ------ Interrupt ------  ------ Interrupt ------  
    0     1                            1006 mov  %ax, count
    0     1   ------ Interrupt ------  ------ Interrupt ------  
    0     1   1007 mov  $0, flag
    0     1   ------ Interrupt ------  ------ Interrupt ------  
    0     1                            1007 mov  $0, flag
    0     1   ------ Interrupt ------  ------ Interrupt ------  
   -1     1   1008 sub  $1, %bx
    0     1   ------ Interrupt ------  ------ Interrupt ------  
   -1     1                            1008 sub  $1, %bx
   -1     1   ------ Interrupt ------  ------ Interrupt ------  
   -1     1   1009 test $0, %bx
   -1     1   ------ Interrupt ------  ------ Interrupt ------  
   -1     1                            1009 test $0, %bx
   -1     1   ------ Interrupt ------  ------ Interrupt ------  
   -1     1   1010 jgt .top
   -1     1   ------ Interrupt ------  ------ Interrupt ------  
   -1     1                            1010 jgt .top
   -1     1   ------ Interrupt ------  ------ Interrupt ------  
   -1     1   1011 halt
   -1     1   ----- Halt;Switch -----  ----- Halt;Switch -----  
   -1     1   ------ Interrupt ------  ------ Interrupt ------  
   -1     1                            1011 halt
ZhengYukundeMBP:software-hardware-locks ZhengYukun$ ./x86.py -p flag.s -t 2 -i 100 -r -R bx,ax -c 

   bx    ax          Thread 0                Thread 1         

    0     0   
    0     0   1000 mov  flag, %ax
    0     0   1001 test $0, %ax
    0     0   1002 jne  .acquire
    0     0   1003 mov  $1, flag
    0     0   1004 mov  count, %ax
    0     1   1005 add  $1, %ax
    0     1   1006 mov  %ax, count
    0     1   1007 mov  $0, flag
   -1     1   1008 sub  $1, %bx
   -1     1   1009 test $0, %bx
   -1     1   1010 jgt .top
   -1     1   1011 halt
    0     0   ----- Halt;Switch -----  ----- Halt;Switch -----  
    0     0                            1000 mov  flag, %ax
    0     0                            1001 test $0, %ax
    0     0                            1002 jne  .acquire
    0     0                            1003 mov  $1, flag
    0     1                            1004 mov  count, %ax
    0     2                            1005 add  $1, %ax
    0     2                            1006 mov  %ax, count
    0     2                            1007 mov  $0, flag
   -1     2                            1008 sub  $1, %bx
   -1     2                            1009 test $0, %bx
   -1     2                            1010 jgt .top
   -1     2                            1011 halt
  ```
  
  当分别以1和100的中断频率执行个并发进程时最终的count结果分别为1和2，观察执行信息可以看出前者在同一时间点时有两个进程同时处于临界区，因此flag.s不能实现锁机制。
  
  
- peterson.s：能够实现锁机制，测例如下：

两个并发进程，id分别为0和1，中断频率为1，表示每步都会进行进程切换，保证一个进程在临界区执行时另一个进程会尝试打断它。通过测试发现当thread0在临界区执行时，thread1会处于循环中等待，证明锁机制起了作用。保证同一时间只有一个进程能够进入临界区，同时一旦该进程退出临界区，其他进程能够感知全局变量的变化，从而做到“有空则入”。

```
ZhengYukundeMBP:software-hardware-locks ZhengYukun$ ./x86.py -p peterson.s -t 2 -i 1 -a bx=0,bx=1 -r -R bx,cx,ax -c

   bx    cx    ax          Thread 0                Thread 1         

    0     0     0   
    0     0     0   1000 lea flag, %fx
    1     0     0   ------ Interrupt ------  ------ Interrupt ------  
    1     0     0                            1000 lea flag, %fx
    0     0     0   ------ Interrupt ------  ------ Interrupt ------  
    0     0     0   1001 mov %bx, %cx
    1     0     0   ------ Interrupt ------  ------ Interrupt ------  
    1     1     0                            1001 mov %bx, %cx
    0     0     0   ------ Interrupt ------  ------ Interrupt ------  
    0     0     0   1002 neg %cx
    1     1     0   ------ Interrupt ------  ------ Interrupt ------  
    1    -1     0                            1002 neg %cx
    0     0     0   ------ Interrupt ------  ------ Interrupt ------  
    0     1     0   1003 add $1, %cx
    1    -1     0   ------ Interrupt ------  ------ Interrupt ------  
    1     0     0                            1003 add $1, %cx
    0     1     0   ------ Interrupt ------  ------ Interrupt ------  
    0     1     0   1004 mov $1, 0(%fx,%bx,4)
    1     0     0   ------ Interrupt ------  ------ Interrupt ------  
    1     0     0                            1004 mov $1, 0(%fx,%bx,4)
    0     1     0   ------ Interrupt ------  ------ Interrupt ------  
    0     1     0   1005 mov %cx, turn
    1     0     0   ------ Interrupt ------  ------ Interrupt ------  
    1     0     0                            1005 mov %cx, turn
    0     1     0   ------ Interrupt ------  ------ Interrupt ------  
    0     1     1   1006 mov 0(%fx,%cx,4), %ax
    1     0     0   ------ Interrupt ------  ------ Interrupt ------  
    1     0     1                            1006 mov 0(%fx,%cx,4), %ax
    0     1     1   ------ Interrupt ------  ------ Interrupt ------  
    0     1     1   1007 test $1, %ax
    1     0     1   ------ Interrupt ------  ------ Interrupt ------  
    1     0     1                            1007 test $1, %ax
    0     1     1   ------ Interrupt ------  ------ Interrupt ------  
    0     1     1   1008 jne .fini
    1     0     1   ------ Interrupt ------  ------ Interrupt ------  
    1     0     1                            1008 jne .fini
    0     1     1   ------ Interrupt ------  ------ Interrupt ------  
    0     1     0   1009 mov turn, %ax
    1     0     1   ------ Interrupt ------  ------ Interrupt ------  
    1     0     0                            1009 mov turn, %ax
    0     1     0   ------ Interrupt ------  ------ Interrupt ------  
    0     1     0   1010 test %cx, %ax
    1     0     0   ------ Interrupt ------  ------ Interrupt ------  
    1     0     0                            1010 test %cx, %ax
    0     1     0   ------ Interrupt ------  ------ Interrupt ------  
    0     1     0   1011 je .spin1
    1     0     0   ------ Interrupt ------  ------ Interrupt ------  
    1     0     0                            1011 je .spin1
    0     1     0   ------ Interrupt ------  ------ Interrupt ------  
    0     1     0   1012 mov count, %ax
    1     0     0   ------ Interrupt ------  ------ Interrupt ------  
    1     0     1                            1006 mov 0(%fx,%cx,4), %ax
    0     1     0   ------ Interrupt ------  ------ Interrupt ------  
    0     1     1   1013 add $1, %ax
    1     0     1   ------ Interrupt ------  ------ Interrupt ------  
    1     0     1                            1007 test $1, %ax
    0     1     1   ------ Interrupt ------  ------ Interrupt ------  
    0     1     1   1014 mov %ax, count
    1     0     1   ------ Interrupt ------  ------ Interrupt ------  
    1     0     1                            1008 jne .fini
    0     1     1   ------ Interrupt ------  ------ Interrupt ------  
    0     1     1   1015 mov $0, 0(%fx,%bx,4)
    1     0     1   ------ Interrupt ------  ------ Interrupt ------  
    1     0     0                            1009 mov turn, %ax
    0     1     1   ------ Interrupt ------  ------ Interrupt ------  
    0     1     1   1016 mov %cx, turn
    1     0     0   ------ Interrupt ------  ------ Interrupt ------  
    1     0     0                            1010 test %cx, %ax
    0     1     1   ------ Interrupt ------  ------ Interrupt ------  
    0     1     1   1017 halt
    1     0     0   ----- Halt;Switch -----  ----- Halt;Switch -----  
    1     0     0   ------ Interrupt ------  ------ Interrupt ------  
    1     0     0                            1011 je .spin1
    1     0     0   ------ Interrupt ------  ------ Interrupt ------  
    1     0     0                            1006 mov 0(%fx,%cx,4), %ax
    1     0     0   ------ Interrupt ------  ------ Interrupt ------  
    1     0     0                            1007 test $1, %ax
    1     0     0   ------ Interrupt ------  ------ Interrupt ------  
    1     0     0                            1008 jne .fini
    1     0     0   ------ Interrupt ------  ------ Interrupt ------  
    1     0     1                            1012 mov count, %ax
    1     0     1   ------ Interrupt ------  ------ Interrupt ------  
    1     0     2                            1013 add $1, %ax
    1     0     2   ------ Interrupt ------  ------ Interrupt ------  
    1     0     2                            1014 mov %ax, count
    1     0     2   ------ Interrupt ------  ------ Interrupt ------  
    1     0     2                            1015 mov $0, 0(%fx,%bx,4)
    1     0     2   ------ Interrupt ------  ------ Interrupt ------  
    1     0     2                            1016 mov %cx, turn
    1     0     2   ------ Interrupt ------  ------ Interrupt ------  
    1     0     2                            1017 halt
```

- test-and-set.s：能够实现锁机制，借助了原子操作``xchg``，使得能够使多个并发进程某一时刻只有一个进程能够进入临界区，同时其他程序在循环中等待的时候能够实现“有空则入”。

```
ZhengYukundeMBP:software-hardware-locks ZhengYukun$ ./x86.py -p test-and-set.s -t 2 -i 1 -r -R bx,ax -c

   bx    ax          Thread 0                Thread 1         

    0     0   
    0     1   1000 mov  $1, %ax
    0     0   ------ Interrupt ------  ------ Interrupt ------  
    0     1                            1000 mov  $1, %ax
    0     1   ------ Interrupt ------  ------ Interrupt ------  
    0     0   1001 xchg %ax, mutex
    0     1   ------ Interrupt ------  ------ Interrupt ------  
    0     1                            1001 xchg %ax, mutex
    0     0   ------ Interrupt ------  ------ Interrupt ------  
    0     0   1002 test $0, %ax
    0     1   ------ Interrupt ------  ------ Interrupt ------  
    0     1                            1002 test $0, %ax
    0     0   ------ Interrupt ------  ------ Interrupt ------  
    0     0   1003 jne  .acquire
    0     1   ------ Interrupt ------  ------ Interrupt ------  
    0     1                            1003 jne  .acquire
    0     0   ------ Interrupt ------  ------ Interrupt ------  
    0     0   1004 mov  count, %ax
    0     1   ------ Interrupt ------  ------ Interrupt ------  
    0     1                            1000 mov  $1, %ax
    0     0   ------ Interrupt ------  ------ Interrupt ------  
    0     1   1005 add  $1, %ax
    0     1   ------ Interrupt ------  ------ Interrupt ------  
    0     1                            1001 xchg %ax, mutex
    0     1   ------ Interrupt ------  ------ Interrupt ------  
    0     1   1006 mov  %ax, count
    0     1   ------ Interrupt ------  ------ Interrupt ------  
    0     1                            1002 test $0, %ax
    0     1   ------ Interrupt ------  ------ Interrupt ------  
    0     1   1007 mov  $0, mutex
    0     1   ------ Interrupt ------  ------ Interrupt ------  
    0     1                            1003 jne  .acquire
    0     1   ------ Interrupt ------  ------ Interrupt ------  
   -1     1   1008 sub  $1, %bx
    0     1   ------ Interrupt ------  ------ Interrupt ------  
    0     1                            1000 mov  $1, %ax
   -1     1   ------ Interrupt ------  ------ Interrupt ------  
   -1     1   1009 test $0, %bx
    0     1   ------ Interrupt ------  ------ Interrupt ------  
    0     0                            1001 xchg %ax, mutex
   -1     1   ------ Interrupt ------  ------ Interrupt ------  
   -1     1   1010 jgt .top
    0     0   ------ Interrupt ------  ------ Interrupt ------  
    0     0                            1002 test $0, %ax
   -1     1   ------ Interrupt ------  ------ Interrupt ------  
   -1     1   1011 halt
    0     0   ----- Halt;Switch -----  ----- Halt;Switch -----  
    0     0   ------ Interrupt ------  ------ Interrupt ------  
    0     0                            1003 jne  .acquire
    0     0   ------ Interrupt ------  ------ Interrupt ------  
    0     1                            1004 mov  count, %ax
    0     1   ------ Interrupt ------  ------ Interrupt ------  
    0     2                            1005 add  $1, %ax
    0     2   ------ Interrupt ------  ------ Interrupt ------  
    0     2                            1006 mov  %ax, count
    0     2   ------ Interrupt ------  ------ Interrupt ------  
    0     2                            1007 mov  $0, mutex
    0     2   ------ Interrupt ------  ------ Interrupt ------  
   -1     2                            1008 sub  $1, %bx
   -1     2   ------ Interrupt ------  ------ Interrupt ------  
   -1     2                            1009 test $0, %bx
   -1     2   ------ Interrupt ------  ------ Interrupt ------  
   -1     2                            1010 jgt .top
   -1     2   ------ Interrupt ------  ------ Interrupt ------  
   -1     2                            1011 halt
```

- ticket.s：

三个并发进程，同样能够根据到turn选择进入临界区的进程，其他程序在等待时能够检测其变化，及时进入。

```
ZhengYukundeMBP:software-hardware-locks ZhengYukun$ ./x86.py -p ticket.s -t 3 -i 1 -r -R bx,ax,cx -c

   bx    ax    cx          Thread 0                Thread 1                Thread 2         

    0     0     0   
    0     1     0   1000 mov $1, %ax
    0     0     0   ------ Interrupt ------  ------ Interrupt ------  ------ Interrupt ------  
    0     1     0                            1000 mov $1, %ax
    0     0     0   ------ Interrupt ------  ------ Interrupt ------  ------ Interrupt ------  
    0     1     0                                                     1000 mov $1, %ax
    0     1     0   ------ Interrupt ------  ------ Interrupt ------  ------ Interrupt ------  
    0     0     0   1001 fetchadd %ax, ticket
    0     1     0   ------ Interrupt ------  ------ Interrupt ------  ------ Interrupt ------  
    0     1     0                            1001 fetchadd %ax, ticket
    0     1     0   ------ Interrupt ------  ------ Interrupt ------  ------ Interrupt ------  
    0     2     0                                                     1001 fetchadd %ax, ticket
    0     0     0   ------ Interrupt ------  ------ Interrupt ------  ------ Interrupt ------  
    0     0     0   1002 mov turn, %cx
    0     1     0   ------ Interrupt ------  ------ Interrupt ------  ------ Interrupt ------  
    0     1     0                            1002 mov turn, %cx
    0     2     0   ------ Interrupt ------  ------ Interrupt ------  ------ Interrupt ------  
    0     2     0                                                     1002 mov turn, %cx
    0     0     0   ------ Interrupt ------  ------ Interrupt ------  ------ Interrupt ------  
    0     0     0   1003 test %cx, %ax
    0     1     0   ------ Interrupt ------  ------ Interrupt ------  ------ Interrupt ------  
    0     1     0                            1003 test %cx, %ax
    0     2     0   ------ Interrupt ------  ------ Interrupt ------  ------ Interrupt ------  
    0     2     0                                                     1003 test %cx, %ax
    0     0     0   ------ Interrupt ------  ------ Interrupt ------  ------ Interrupt ------  
    0     0     0   1004 jne .tryagain
    0     1     0   ------ Interrupt ------  ------ Interrupt ------  ------ Interrupt ------  
    0     1     0                            1004 jne .tryagain
    0     2     0   ------ Interrupt ------  ------ Interrupt ------  ------ Interrupt ------  
    0     2     0                                                     1004 jne .tryagain
    0     0     0   ------ Interrupt ------  ------ Interrupt ------  ------ Interrupt ------  
    0     0     0   1005 mov  count, %ax
    0     1     0   ------ Interrupt ------  ------ Interrupt ------  ------ Interrupt ------  
    0     1     0                            1002 mov turn, %cx
    0     2     0   ------ Interrupt ------  ------ Interrupt ------  ------ Interrupt ------  
    0     2     0                                                     1002 mov turn, %cx
    0     0     0   ------ Interrupt ------  ------ Interrupt ------  ------ Interrupt ------  
    0     1     0   1006 add  $1, %ax
    0     1     0   ------ Interrupt ------  ------ Interrupt ------  ------ Interrupt ------  
    0     1     0                            1003 test %cx, %ax
    0     2     0   ------ Interrupt ------  ------ Interrupt ------  ------ Interrupt ------  
    0     2     0                                                     1003 test %cx, %ax
    0     1     0   ------ Interrupt ------  ------ Interrupt ------  ------ Interrupt ------  
    0     1     0   1007 mov  %ax, count
    0     1     0   ------ Interrupt ------  ------ Interrupt ------  ------ Interrupt ------  
    0     1     0                            1004 jne .tryagain
    0     2     0   ------ Interrupt ------  ------ Interrupt ------  ------ Interrupt ------  
    0     2     0                                                     1004 jne .tryagain
    0     1     0   ------ Interrupt ------  ------ Interrupt ------  ------ Interrupt ------  
    0     1     0   1008 mov $1, %ax
    0     1     0   ------ Interrupt ------  ------ Interrupt ------  ------ Interrupt ------  
    0     1     0                            1002 mov turn, %cx
    0     2     0   ------ Interrupt ------  ------ Interrupt ------  ------ Interrupt ------  
    0     2     0                                                     1002 mov turn, %cx
    0     1     0   ------ Interrupt ------  ------ Interrupt ------  ------ Interrupt ------  
    0     0     0   1009 fetchadd %ax, turn
    0     1     0   ------ Interrupt ------  ------ Interrupt ------  ------ Interrupt ------  
    0     1     0                            1003 test %cx, %ax
    0     2     0   ------ Interrupt ------  ------ Interrupt ------  ------ Interrupt ------  
    0     2     0                                                     1003 test %cx, %ax
    0     0     0   ------ Interrupt ------  ------ Interrupt ------  ------ Interrupt ------  
   -1     0     0   1010 sub  $1, %bx
    0     1     0   ------ Interrupt ------  ------ Interrupt ------  ------ Interrupt ------  
    0     1     0                            1004 jne .tryagain
    0     2     0   ------ Interrupt ------  ------ Interrupt ------  ------ Interrupt ------  
    0     2     0                                                     1004 jne .tryagain
   -1     0     0   ------ Interrupt ------  ------ Interrupt ------  ------ Interrupt ------  
   -1     0     0   1011 test $0, %bx
    0     1     0   ------ Interrupt ------  ------ Interrupt ------  ------ Interrupt ------  
    0     1     1                            1002 mov turn, %cx
    0     2     0   ------ Interrupt ------  ------ Interrupt ------  ------ Interrupt ------  
    0     2     1                                                     1002 mov turn, %cx
   -1     0     0   ------ Interrupt ------  ------ Interrupt ------  ------ Interrupt ------  
   -1     0     0   1012 jgt .top
    0     1     1   ------ Interrupt ------  ------ Interrupt ------  ------ Interrupt ------  
    0     1     1                            1003 test %cx, %ax
    0     2     1   ------ Interrupt ------  ------ Interrupt ------  ------ Interrupt ------  
    0     2     1                                                     1003 test %cx, %ax
   -1     0     0   ------ Interrupt ------  ------ Interrupt ------  ------ Interrupt ------  
   -1     0     0   1013 halt
    0     1     1   ----- Halt;Switch -----  ----- Halt;Switch -----  ----- Halt;Switch -----  
    0     2     1   ------ Interrupt ------  ------ Interrupt ------  ------ Interrupt ------  
    0     2     1                                                     1004 jne .tryagain
    0     1     1   ------ Interrupt ------  ------ Interrupt ------  ------ Interrupt ------  
    0     1     1                            1004 jne .tryagain
    0     2     1   ------ Interrupt ------  ------ Interrupt ------  ------ Interrupt ------  
    0     2     1                                                     1002 mov turn, %cx
    0     1     1   ------ Interrupt ------  ------ Interrupt ------  ------ Interrupt ------  
    0     1     1                            1005 mov  count, %ax
    0     2     1   ------ Interrupt ------  ------ Interrupt ------  ------ Interrupt ------  
    0     2     1                                                     1003 test %cx, %ax
    0     1     1   ------ Interrupt ------  ------ Interrupt ------  ------ Interrupt ------  
    0     2     1                            1006 add  $1, %ax
    0     2     1   ------ Interrupt ------  ------ Interrupt ------  ------ Interrupt ------  
    0     2     1                                                     1004 jne .tryagain
    0     2     1   ------ Interrupt ------  ------ Interrupt ------  ------ Interrupt ------  
    0     2     1                            1007 mov  %ax, count
    0     2     1   ------ Interrupt ------  ------ Interrupt ------  ------ Interrupt ------  
    0     2     1                                                     1002 mov turn, %cx
    0     2     1   ------ Interrupt ------  ------ Interrupt ------  ------ Interrupt ------  
    0     1     1                            1008 mov $1, %ax
    0     2     1   ------ Interrupt ------  ------ Interrupt ------  ------ Interrupt ------  
    0     2     1                                                     1003 test %cx, %ax
    0     1     1   ------ Interrupt ------  ------ Interrupt ------  ------ Interrupt ------  
    0     1     1                            1009 fetchadd %ax, turn
    0     2     1   ------ Interrupt ------  ------ Interrupt ------  ------ Interrupt ------  
    0     2     1                                                     1004 jne .tryagain
    0     1     1   ------ Interrupt ------  ------ Interrupt ------  ------ Interrupt ------  
   -1     1     1                            1010 sub  $1, %bx
    0     2     1   ------ Interrupt ------  ------ Interrupt ------  ------ Interrupt ------  
    0     2     2                                                     1002 mov turn, %cx
   -1     1     1   ------ Interrupt ------  ------ Interrupt ------  ------ Interrupt ------  
   -1     1     1                            1011 test $0, %bx
    0     2     2   ------ Interrupt ------  ------ Interrupt ------  ------ Interrupt ------  
    0     2     2                                                     1003 test %cx, %ax
   -1     1     1   ------ Interrupt ------  ------ Interrupt ------  ------ Interrupt ------  
   -1     1     1                            1012 jgt .top
    0     2     2   ------ Interrupt ------  ------ Interrupt ------  ------ Interrupt ------  
    0     2     2                                                     1004 jne .tryagain
   -1     1     1   ------ Interrupt ------  ------ Interrupt ------  ------ Interrupt ------  
   -1     1     1                            1013 halt
    0     2     2   ----- Halt;Switch -----  ----- Halt;Switch -----  ----- Halt;Switch -----  
    0     2     2   ------ Interrupt ------  ------ Interrupt ------  ------ Interrupt ------  
    0     2     2                                                     1005 mov  count, %ax
    0     2     2   ------ Interrupt ------  ------ Interrupt ------  ------ Interrupt ------  
    0     3     2                                                     1006 add  $1, %ax
    0     3     2   ------ Interrupt ------  ------ Interrupt ------  ------ Interrupt ------  
    0     3     2                                                     1007 mov  %ax, count
    0     3     2   ------ Interrupt ------  ------ Interrupt ------  ------ Interrupt ------  
    0     1     2                                                     1008 mov $1, %ax
    0     1     2   ------ Interrupt ------  ------ Interrupt ------  ------ Interrupt ------  
    0     2     2                                                     1009 fetchadd %ax, turn
    0     2     2   ------ Interrupt ------  ------ Interrupt ------  ------ Interrupt ------  
   -1     2     2                                                     1010 sub  $1, %bx
   -1     2     2   ------ Interrupt ------  ------ Interrupt ------  ------ Interrupt ------  
   -1     2     2                                                     1011 test $0, %bx
   -1     2     2   ------ Interrupt ------  ------ Interrupt ------  ------ Interrupt ------  
   -1     2     2                                                     1012 jgt .top
   -1     2     2   ------ Interrupt ------  ------ Interrupt ------  ------ Interrupt ------  
   -1     2     2                                                     1013 halt
```

- test-and-test-and-set.s:能够实现锁机制。反证法：如果某一时刻有两个进程同时位于临界区，那么说明上一个跳转指令处ax均为0，那说明执行xchg时mutex均为0，但由于这是一条原子操作指令，那么先执行的进程肯定已经将mutex置为了1，所以矛盾，证明锁机制成立。

```
ZhengYukundeMBP:software-hardware-locks ZhengYukun$ ./x86.py -p test-and-test-and-set.s -t 2 -i 1 -r -R bx,ax -c

   bx    ax          Thread 0                Thread 1         

    0     0   
    0     0   1000 mov  mutex, %ax
    0     0   ------ Interrupt ------  ------ Interrupt ------  
    0     0                            1000 mov  mutex, %ax
    0     0   ------ Interrupt ------  ------ Interrupt ------  
    0     0   1001 test $0, %ax
    0     0   ------ Interrupt ------  ------ Interrupt ------  
    0     0                            1001 test $0, %ax
    0     0   ------ Interrupt ------  ------ Interrupt ------  
    0     0   1002 jne .acquire
    0     0   ------ Interrupt ------  ------ Interrupt ------  
    0     0                            1002 jne .acquire
    0     0   ------ Interrupt ------  ------ Interrupt ------  
    0     1   1003 mov  $1, %ax
    0     0   ------ Interrupt ------  ------ Interrupt ------  
    0     1                            1003 mov  $1, %ax
    0     1   ------ Interrupt ------  ------ Interrupt ------  
    0     0   1004 xchg %ax, mutex
    0     1   ------ Interrupt ------  ------ Interrupt ------  
    0     1                            1004 xchg %ax, mutex
    0     0   ------ Interrupt ------  ------ Interrupt ------  
    0     0   1005 test $0, %ax
    0     1   ------ Interrupt ------  ------ Interrupt ------  
    0     1                            1005 test $0, %ax
    0     0   ------ Interrupt ------  ------ Interrupt ------  
    0     0   1006 jne .acquire
    0     1   ------ Interrupt ------  ------ Interrupt ------  
    0     1                            1006 jne .acquire
    0     0   ------ Interrupt ------  ------ Interrupt ------  
    0     0   1007 mov  count, %ax
    0     1   ------ Interrupt ------  ------ Interrupt ------  
    0     1                            1000 mov  mutex, %ax
    0     0   ------ Interrupt ------  ------ Interrupt ------  
    0     1   1008 add  $1, %ax
    0     1   ------ Interrupt ------  ------ Interrupt ------  
    0     1                            1001 test $0, %ax
    0     1   ------ Interrupt ------  ------ Interrupt ------  
    0     1   1009 mov  %ax, count
    0     1   ------ Interrupt ------  ------ Interrupt ------  
    0     1                            1002 jne .acquire
    0     1   ------ Interrupt ------  ------ Interrupt ------  
    0     1   1010 mov  $0, mutex
    0     1   ------ Interrupt ------  ------ Interrupt ------  
    0     0                            1000 mov  mutex, %ax
    0     1   ------ Interrupt ------  ------ Interrupt ------  
   -1     1   1011 sub  $1, %bx
    0     0   ------ Interrupt ------  ------ Interrupt ------  
    0     0                            1001 test $0, %ax
   -1     1   ------ Interrupt ------  ------ Interrupt ------  
   -1     1   1012 test $0, %bx
    0     0   ------ Interrupt ------  ------ Interrupt ------  
    0     0                            1002 jne .acquire
   -1     1   ------ Interrupt ------  ------ Interrupt ------  
   -1     1   1013 jgt .top
    0     0   ------ Interrupt ------  ------ Interrupt ------  
    0     1                            1003 mov  $1, %ax
   -1     1   ------ Interrupt ------  ------ Interrupt ------  
   -1     1   1014 halt
    0     1   ----- Halt;Switch -----  ----- Halt;Switch -----  
    0     1   ------ Interrupt ------  ------ Interrupt ------  
    0     0                            1004 xchg %ax, mutex
    0     0   ------ Interrupt ------  ------ Interrupt ------  
    0     0                            1005 test $0, %ax
    0     0   ------ Interrupt ------  ------ Interrupt ------  
    0     0                            1006 jne .acquire
    0     0   ------ Interrupt ------  ------ Interrupt ------  
    0     1                            1007 mov  count, %ax
    0     1   ------ Interrupt ------  ------ Interrupt ------  
    0     2                            1008 add  $1, %ax
    0     2   ------ Interrupt ------  ------ Interrupt ------  
    0     2                            1009 mov  %ax, count
    0     2   ------ Interrupt ------  ------ Interrupt ------  
    0     2                            1010 mov  $0, mutex
    0     2   ------ Interrupt ------  ------ Interrupt ------  
   -1     2                            1011 sub  $1, %bx
   -1     2   ------ Interrupt ------  ------ Interrupt ------  
   -1     2                            1012 test $0, %bx
   -1     2   ------ Interrupt ------  ------ Interrupt ------  
   -1     2                            1013 jgt .top
   -1     2   ------ Interrupt ------  ------ Interrupt ------  
   -1     2                            1014 halt
```

- 能否设计新的硬件原子操作指令Compare-And-Swap,Fetch-And-Add？

能。

Compare-And-Swap

```
.var mutex
.var ptr
.var expected
.var new
.main
.top  

.acquire
mov  $1, %ax        
xchg %ax, mutex     # atomic swap of 1 and mutex
test $0, %ax        # if we get 0 back: lock is free!
jne  .acquire       # if not, try again

# critical section
mov  ptr, %ax     # get the value at the address
test  %ax, expected
jne $1
mov  new, ptr

# release lock
mov  $0, mutex

halt
```

Fetch-And-Add

```
.var mutex
.var ptr
.main
.top  

.acquire
mov  $1, %ax        
xchg %ax, mutex     # atomic swap of 1 and mutex
test $0, %ax        # if we get 0 back: lock is free!
jne  .acquire       # if not, try again

# critical section
mov  ptr, %ax     # get the value at the address
add $1, %ax
mov  %ax, ptr
sub $1, %ax

# release lock
mov  $0, mutex

halt
```

查找资料得到以下实现方法：

![](https://raw.githubusercontent.com/zhengyk11/ucore_lab_docs/master/07-1-spoc-discussion/cas.png)

![](https://raw.githubusercontent.com/zhengyk11/ucore_lab_docs/master/07-1-spoc-discussion/faa.png)



