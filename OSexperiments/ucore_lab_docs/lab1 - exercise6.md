## 练习6：完善中断初始化和处理

请完成编码工作和回答如下问题：

1. 中断描述符表（也可简称为保护模式下的中断向量表）中一个表项占多少字节？其中哪几位代表中断处理代码的入口？  
  访问/kern/mm/mmu.h，其中定义中断描述符代表的结构体如下：
  
  ```C
  /* Gate descriptors for interrupts and traps */
  struct gatedesc {
    unsigned gd_off_15_0 : 16;        // low 16 bits of offset in segment
    unsigned gd_ss : 16;            // segment selector
    unsigned gd_args : 5;            // # args, 0 for interrupt/trap gates
    unsigned gd_rsv1 : 3;            // reserved(should be zero I guess)
    unsigned gd_type : 4;            // type(STS_{TG,IG32,TG32})
    unsigned gd_s : 1;                // must be 0 (system)
    unsigned gd_dpl : 2;            // descriptor(meaning new) privilege level
    unsigned gd_p : 1;                // Present
    unsigned gd_off_31_16 : 16;        // high bits of offset in segment
  };
  ```
  
  可知，一个表项占8 byte，0~1字节和6~7字节分别表示低16位和高16位的段内偏移，2~3字节表示的是段选择子。  
2. 请编程完善kern/trap/trap.c中对中断向量表进行初始化的函数idt_init。在idt_init函数中，依次对所有中断入口进行初始化。使用mmu.h中的SETGATE宏，填充idt数组内容。每个中断的入口由tools/vectors.c生成，使用trap.c中声明的vectors数组即可。

  ```C
  void
  idt_init(void) {
        /* LAB1 YOUR CODE : STEP 2 */
        /* (1) Where are the entry addrs of each Interrupt Service Routine (ISR)?
         *     All ISR's entry addrs are stored in __vectors. where is uintptr_t __vectors[] ?
         *     __vectors[] is in kern/trap/vector.S which is produced by tools/vector.c
         *     (try "make" command in lab1, then you will find vector.S in kern/trap DIR)
         *     You can use  "extern uintptr_t __vectors[];" to define this extern variable which will be used later.
         * (2) Now you should setup the entries of ISR in Interrupt Description Table (IDT).
         *     Can you see idt[256] in this file? Yes, it's IDT! you can use SETGATE macro to setup each item of IDT
         * (3) After setup the contents of IDT, you will let CPU know where is the IDT by using 'lidt' instruction.
         *     You don't know the meaning of this instruction? just google it! and check the libs/x86.h to know more.
         *     Notice: the argument of lidt is idt_pd. try to find it!
         */
        extern uintptr_t __vectors[];
        int i;
        //将256个idt表项全部填充，参数：0表示为中断，GD_KTEXT表示kernel text，
        //__vectors[i]表示对用的中断处理程序在代码段中的偏移，DPL_KERNEL表示为内核态
        for (i = 0; i < sizeof(idt) / sizeof(struct gatedesc); i++) {
          SETGATE(idt[i], 0, GD_KTEXT, __vectors[i], DPL_KERNEL);
        }
        //从用户态切换到内核态
        // set for switch from user to kernel
        SETGATE(idt[T_SWITCH_TOK], 0, GD_KTEXT, __vectors[T_SWITCH_TOK], DPL_USER);
        // load the IDT
        //加载IDT
        lidt(&idt_pd);
  }
  ```
  
3. 请编程完善trap.c中的中断处理函数trap，在对时钟中断进行处理的部分填写trap函数中处理时钟中断的部分，使操作系统每遇到100次时钟中断后，调用print_ticks子程序，向屏幕上打印一行文字”100 ticks”。  
  添加代码如下：
  
  ```C
  /* trap_dispatch - dispatch based on what type of trap occurred */
  static void
  trap_dispatch(struct trapframe *tf) {
     char c;
  
      switch (tf->tf_trapno) {
      case IRQ_OFFSET + IRQ_TIMER:
          /* LAB1 YOUR CODE : STEP 3 */
          /* handle the timer interrupt */
          /* (1) After a timer interrupt, you should record this event using a global variable (increase it), such as ticks in     kern/driver/clock.c
           * (2) Every TICK_NUM cycle, you can print some info using a funciton, such as print_ticks().
          * (3) Too Simple? Yes, I think so!
          */
          //ticks用来记录时钟中断次数，每100次调用一次print_ticks()即可
          ticks++;
          if (ticks % TICK_NUM == 0) {
              print_ticks();
          }
          break;
      case IRQ_OFFSET + IRQ_COM1:
      ......
  ```

> 【注意】除了系统调用中断(T_SYSCALL)使用陷阱门描述符且权限为用户态权限以外，其它中断均使用特权级(DPL)为０的中断门描述符，权限为内核态权限；而ucore的应用程序处于特权级３，需要采用｀int 0x80`指令操作（这种方式称为软中断，软件中断，Tra中断，在lab5会碰到）来发出系统调用请求，并要能实现从特权级３到特权级０的转换，所以系统调用中断(T_SYSCALL)所对应的中断门描述符中的特权级（DPL）需要设置为３。

要求完成问题2和问题3 提出的相关函数实现，提交改进后的源代码包（可以编译执行），并在实验报告中简要说明实现过程，并写出对问题1的回答。完成这问题2和3要求的部分代码后，运行整个系统，可以看到大约每1秒会输出一次”100 ticks”，而按下的键也会在屏幕上显示。

提示：可阅读小节“中断与异常”。
