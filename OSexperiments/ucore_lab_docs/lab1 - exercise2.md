## 练习2：使用qemu执行并调试lab1中的软件

为了熟悉使用qemu和gdb进行的调试工作，我们进行如下的小练习：  

1. 从CPU加电后执行的第一条指令开始，单步跟踪BIOS的执行。  
	a. 为了跟踪BIOS，需要修改lab1/tools/gdbinit, 内容为:  
	
	```
	file bin/kernel
	set architecture i8086
	target remote :1234
	break kern_init
	```
	
	b. 随后执行debug，在gdb调试界面下执行``si``命令  
	c. 在gdb界面下，可通过如下命令来看BIOS的代码  
	
	```
 	x /2i $pc  //显示当前eip处的2条汇编指令
 	```
 	
2. 在初始化位置0x7c00设置实地址断点,测试断点正常。  
	a. 修改lab1/tools/gdbinit，内容为：
	```
	file bin/kernel
	target remote :1234
	break kern_init
	continue
	set architecture i8086
	b *0x7c00
	c
	x /2i $pc
	set architecture i386
	```
	
	b. ``make debug``后得到如下结果：  
	```
	Breakpoint 2 at 0x7c00
	Breakpoint 2, 0x00007c00 in ?? ()
	=> 0x7c00:      cli    
   	0x7c01:      cld    
	The target architecture is assumed to be i386
	```
	
3. 从0x7c00开始跟踪代码运行,将单步跟踪反汇编得到的代码与bootasm.S和 bootblock.asm进行比较。  
	a. 修改lab1/tools/gdbinit，内容为  
	```
    file bin/kernel
    set architecture i8086
    target remote :1234
    break kern_init
    continue
    b *0x7c00
    c
    x /10i $pc
	```
	b. 将Makefile中qemu修改如下,用来将运行的汇编指令保存在q.log中：
	```
qemu: $(UCOREIMG)
	$(V)$(QEMU) -no-reboot -d in_asm -D q.log -parallel stdio -hda $< -serial null
	```
	c. 执行``make qemu``后得到q.log,得到部分结果如下：
    ```
    IN: 
    0x00007c00:  cli    
    0x00007c01:  cld    
    0x00007c02:  xor    %ax,%ax
    0x00007c04:  mov    %ax,%ds
    0x00007c06:  mov    %ax,%es
    0x00007c08:  mov    %ax,%ss
    
    ----------------
    IN: 
    0x00007c0a:  in     $0x64,%al
    
    ----------------
    IN: 
    0x00007c0c:  test   $0x2,%al
    0x00007c0e:  jne    0x7c0a
    
    ----------------
    IN: 
    0x00007c10:  mov    $0xd1,%al
    0x00007c12:  out    %al,$0x64
    0x00007c14:  in     $0x64,%al
    0x00007c16:  test   $0x2,%al
    0x00007c18:  jne    0x7c14
    
    ----------------
    IN: 
    0x00007c1a:  mov    $0xdf,%al
    0x00007c1c:  out    %al,$0x60
    0x00007c1e:  lgdtw  0x7c6c
    0x00007c23:  mov    %cr0,%eax
    0x00007c26:  or     $0x1,%eax
    0x00007c2a:  mov    %eax,%cr0
    
    ----------------
    IN: 
    0x00007c2d:  ljmp   $0x8,$0x7c32
    
    ----------------
    IN: 
    0x00007c32:  mov    $0x10,%ax
    0x00007c36:  mov    %eax,%ds
    
    ----------------
    IN: 
    0x00007c38:  mov    %eax,%es
    
    ----------------
    IN: 
    0x00007c3a:  mov    %eax,%fs
    0x00007c3c:  mov    %eax,%gs
    0x00007c3e:  mov    %eax,%ss
    
    ----------------
    IN: 
    0x00007c40:  mov    $0x0,%ebp
    
    ----------------
    IN: 
    0x00007c45:  mov    $0x7c00,%esp
    0x00007c4a:  call   0x7cd1
    
    ----------------
    IN: 
    0x00007cd1:  push   %ebp
    ```

	将上述代码与bootasm.S和bootblock.asm比较，发现汇编指令相同。  
	
4. 自己找一个bootloader或内核中的代码位置，设置断点并进行测试。  
	a. 设置断点  
	```
	break clock_init
	```
	
	b. 执行``make debug``，结果如下： 
    ```
       ┌──kern/driver/clock.c──────────────────────────────────────────────────────┐
       │35          outb(TIMER_MODE, TIMER_SEL0 | TIMER_RATEGEN | TIMER_16BIT);    │
       │36          outb(IO_TIMER1, TIMER_DIV(100) % 256);                         │
       │37          outb(IO_TIMER1, TIMER_DIV(100) / 256);                         │
       │38                                                                         │
       │39          // initialize time counter 'ticks' to zero                     │
      >│40          ticks = 0;                                                     │
       │41                                                                         │
       │42          cprintf("++ setup timer interrupts\n");                        │
       │43          pic_enable(IRQ_TIMER);                                         │
       │44      }                                                                  │
       │45                                                                         │
       │46                                                                         │
       │47                                                                         │
       └───────────────────────────────────────────────────────────────────────────┘
    remote Thread 1 In: clock_init                          Line: 40   PC: 0x100cdd 
    (gdb) continue
    Continuing.
    
    Breakpoint 3, clock_init () at libs/x86.h:57
    (gdb) next
    (gdb) p ticks
    $2 = 0
    (gdb) 
    ```