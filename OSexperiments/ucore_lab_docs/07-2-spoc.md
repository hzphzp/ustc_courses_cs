40.

不能正确实现互斥。

修改如下：

```C
var flag:array[0..1] of boolean;//初值为false
turn:0 1
process i (0或1)
    while true
    do begin
        flag[i] =true;
        turn = j;
        while (flag[j] && turn == j)
        do skip;//skip为空语句

        临界区;
        flag[i] = false;
        出临界区;
    end
```
