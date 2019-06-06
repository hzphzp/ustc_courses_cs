# lab1 SPOC思考题

### 4.1 启动顺序
---

描述符特权级DPL、当前特权级CPL和请求特权级RPL的含义是什么？在哪些寄存器中这些字段？对应的访问条件是什么？ (challenge)写出一些简单的小程序（c or asm）来体现这些特权级的区别和联系。
 ```
  + 建议参见链接“ http://blog.csdn.net/better0332/article/details/3416749 ”对特权级的表述，并查阅指令手册。
  - 
 ```
- CPL为当前正在执行的代码所在的段的特权级；RPL为段选择子的属性，说明了进程对段访问的特权级；DPL规定访问该段的权限级别，要求DPL >= max{ CPL, RPL}  
- CPL在CS寄存器的低两位；RPL是selector中的bit 0和bit 1位组合所得的值；DPL存储在段描述符的第13、14bit  
- RPL ≤ CPL ,  DPL >= max{ CPL, RPL}  
- challenge
    用户态：user/hello.c：

    ```C
    #include <stdio.h>
    #include <ulib.h>
    int
    main(void) {
       cprintf("Hello world!!.\n");
       cprintf("I am process %d.\n", getpid());
       cprintf("hello pass.\n");
       uint32_t cs = 0;
       asm volatile("movl %%cs, %0\n" : "=r"(cs));
       cs &= 3;
       cprintf("user: %d\n", cs); 
       return 0;
    }
    ```
   
    内核态：kern/syscall/syscall.c：

    ```C
    static int
    sys_write(uint32_t arg[]) {
        uint32_t cs = 0;
        asm volatile("movl %%cs, %0\n" : "=r"(cs));
        cs &= 3;
        cprintf("kern: %d\n", cs); 
        int fd = (int)arg[0];
        void *base = (void *)arg[1];
        size_t len = (size_t)arg[2];
        return sysfile_write(fd, base, len);
    }    
    ``` 


### 4.2 C函数调用的实现
---

比较不同特权级的中断切换时的堆栈变化差别；(challenge)写出一些简单的小程序（c or asm）来显示出不同特权级的的中断切换的堆栈变化情况。

* 调用过程
  1. push需要保存的寄存器
  2. push存放实参的寄存器
  3. call
    1. push %ebp
    2. movl %esp, %ebp
    3. ...
    4. pop %ebp
    5. ret
  3. pop第一步中保存的寄存器

  | stack                 |
  |:---------------------:|
  | ...                   |
  | ...                   |
  | Caller's EBP          |
  | Return Address        |
  | Argument #1           |
  | Argument #2           |
  | Argument #3           |
  | Callersaved registers |
  | Local variable #1     |
  | caller's caller's EBP |

从用户态发出的中断需要进入内核态处理，所以处理中断的栈位于内核态，而应用程序的栈位于用户态，同时在内核态的栈需要压入用户态栈的ESP和SS，目的是中断处理结束后程序能够继续恢复到用户态执行，这是与内核态中产生中断的区别  


