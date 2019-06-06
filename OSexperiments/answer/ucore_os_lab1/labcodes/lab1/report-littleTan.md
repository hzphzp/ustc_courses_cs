# Lab 1 实验报告

## 说明
`Lab1的非编程实验中进行了一些对于工具脚本的改动。这些改动均在文中说明，但没有提交。`

`编程实验在自己的机器上测试时make grade可以得到全部分数。如果助教测试时发生Bug，希望能够进行通知。`

`由于文本编辑器的自动格式化功能，某些文件的结尾多余换行或行尾空格可能被删除。有些删除可能发生在敏感区域（如正确性检查程序），但实际上这些更改并不试图扰乱任何测试机制。`

## 练习1
Makefile中开头部分主要通过检测系统相关文件，确定有无已经安装的x86的工具链（gcc和binutils）以及qemu，如果有的话，会将正确的执行文件名称（或名称前缀）记录下来，否则会直接报错。

接下来，Makefile定义了常用的工具和目录，例如mv,cp等文件操作工具，objcopy,objdump等可执行文件处理工具，以及bin，obj等重要的文件存储目录。

后面的代码包含了一个tools/function.mk，其中包含了一些常用的内部命令，如add_files，add_objs之类。

Makefile的默认目标首先包括编译所有的源代码文件，生成.o目标文件并存储与bin目录之中，这些文件会通过ld命令进行连接。由于内核的某些符号的地址必须处于正确的位置，因此链接时需要引入连接脚本文件tools/kernel.ld。在执行完成之后，Makefile还会调用objdump生成符号表，方便打印调试栈时能够找到某一条汇编指令对应的源代码的位置。

Makefile会通过编译boot文件夹下的几个文件（如bootasm.S和bootmain.c）生成引导扇区的目标代码，这些代码再链接时没有调用ldscript，而是直接指定了代码段装入地址。此外，tools下的一些C文件与目标文件处理/自动代码生成有关的代码。例如sign.c似乎是用于生成bootloader，而vector.c则应当是用于生成中断处理代码。Makefile会编译并调用他们，用以完成对应的任务。

在所有的文件都编译、链接完成后，Makefile会调用dd命令，从/dev/zero这个linux设备文件中读取一堆0，然后填慢一个5MB的磁盘映像文件，最后把引导扇区，内核代码和调试符号三部分依此装到这个文件里去，这样就最终得到了一份能够引导真正引导一台x86架构计算机的磁盘映像文件。

## 练习2
首先，lab1中默认的tools/gdbinit脚本会让gdb继续运行知道kern_init入口点，因此需要先对该文件进行修改才能监视BIOS的运行。

gdb初始化后，执行stepi，即可跳转至BIOS的代码入口地址。由于gdb本身对于实模式下的地址支持的一些问题，此时直接使用x /10i $eip读取的指令内容存在问题。因此需要使用qemu的-d in_asm -D <log_file>参数来解决问题。得到的结果如下：

    ----------------
    IN:
    0xfffffff0:  ljmp   $0xf000,$0xe05b

    ----------------
    IN:
    0x000fe05b:  cmpl   $0x0,%cs:0x71a8

    ----------------
    IN:
    0x000fe062:  jne    0xfd2f5

    ----------------
    IN:
    0x000fe066:  xor    %dx,%dx

    ----------------
    IN:
    0x000fe068:  mov    %dx,%ss

    ----------------
    IN:
    0x000fe06a:  mov    $0x7000,%esp

    ----------------
    IN:
    0x000fe070:  mov    $0xf3647,%edx

    ----------------
    IN:
    0x000fe076:  jmp    0xfff00


执行b *0x7c00可以在引导程序的入口点设置断点，继续执行后，利用disas命令查看反汇编代码：

    => 0x7c00:      cli
       0x7c01:      cld
       0x7c02:      xor    %eax,%eax
       0x7c04:      mov    %eax,%ds
       0x7c06:      mov    %eax,%es
       0x7c08:      mov    %eax,%ss
       0x7c0a:      in     $0x64,%al
       0x7c0c:      test   $0x2,%al
       0x7c0e:      jne    0x7c0a
       0x7c10:      mov    $0xd1,%al


得到的结果，和实际bootasm.S中的代码是一致的：

    start:
    .code16                                             # Assemble for 16-bit mode
        cli                                             # Disable interrupts
        cld                                             # String operations increment
        # Set up the important data segment registers (DS, ES, SS).
        xorw %ax, %ax                                   # Segment number zero
        movw %ax, %ds                                   # -> Data Segment
        movw %ax, %es                                   # -> Extra Segment
        movw %ax, %ss                                   # -> Stack Segment
        
接下来，我们可以再用b kern_init为内核初始化代码设置入口点，继续执行，程序会停在内核入口点处。此时disas命令的输出为

    remote Thread 1 In: kern_init                                                                                                                                                L17   PC: 0x100000 
    Dump of assembler code for function kern_init:
    => 0x00100000 <+0>:     push   %ebp
       0x00100001 <+1>:     mov    %esp,%ebp
       0x00100003 <+3>:     sub    $0x18,%esp
       0x00100006 <+6>:     mov    $0x10fd40,%edx
       0x0010000b <+11>:    mov    $0x10ea16,%eax
       0x00100010 <+16>:    sub    %eax,%edx
       0x00100012 <+18>:    mov    %edx,%eax
       0x00100014 <+20>:    sub    $0x4,%esp


## 练习3
A20地址线的问题源于Intel 80286的一个bug，或者说是兼容性问题。早期Intel的CPU实模式下最多支持1M的内存，即20位物理地址，地址线编号从A0到A19，超过这一范围的情况下高位地址被自动抛弃。但是80286引入保护模式，却没有在实模式下确保A20地址线的数据无效，引发兼容性问题。为了解决这一问题，只能通过一个周边电路来控制A20地址线是否有效，而这个电路的控制模块是集成到键盘控制器里的，因此开启A20的方法是向键盘控制器发送写入信号，然后写入一个特定的数据。发送信号时还要先确保键盘缓冲区已空。这个古老的兼容性措施一直持续到现在，其实，现在主板上一般集成了更快的A20控制器，并可以通过BIOS中断直接开启。

GDT表的初始化使用的是lgdt指令，bootloader中包含一个最最简单的全局描述符表，只包含三个段：空段、代码段、数据段，生成其数据的汇编码如下：

    .p2align 2                                          # force 4 byte alignment
    gdt:
        SEG_NULLASM                                     # null seg
        SEG_ASM(STA_X|STA_R, 0x0, 0xffffffff)           # code seg for bootloader and  kernel
        SEG_ASM(STA_W, 0x0, 0xffffffff)                 # data seg for bootloader and kernel
    gdtdesc:
        .word 0x17                                      # sizeof(gdt) - 1
        .long gdt                                       # address gdt
而之前汇编码中的lgdt gdtdesc指令就是用来加载gdt的。

bootloader完成了GDT的设置之后，会通过一跳ljmp指令进行长跳转。通过指定新的32位保护模式下的代码段使得系统进入保护模式。之后的汇编代码都变为针对32为模式的而非实模式的。

## 练习4

ISA定义了一组I/O端口寄存器，通过读/写这些寄存器，程序可以进行磁盘的读写控制操作。主ATA磁盘控制器的寄存器地址区间为0x01F0-0x01F7，可以看到，bootmain.c中的汇编程序利用这些寄存器，通过程序直接控制的方式，每当磁盘控制器空闲就读取一个扇区的数据，并且将它们装入到内存之中。

引导程序在读取磁盘时会将其内容的开头视作一个elf头部，如果elf的magic能够校验通过，那么冲虚就会读取elf文件中所定义的入口地址，在全部内核程序加载完成后跳转到入口地址，从而完成引导工作。

## 练习5

注意到在代码运行时esp和ebp的值确定了当前栈帧的位置，而通过ebp地址附近的数据又可以知晓上一个调用函数的ebp以及返回地址。这样可以逐层向上查找，知道某一层遇到空地址0x00000000，表明已经遇到栈顶。
此外，这个代码还需要获取当前EIP寄存器的值。不过事实上相关的汇编代码uCore已经封装好了。通过读取内核符号表查找某一地址的对应的源代码信息的代码uCore也已经提供。

## 练习6

保护模式下的中断描述符表(IDT)一个表项有64位（8字节），其中，最高的16为（48-63位）和最低的16位（0-15位）表示中断处理程序所在代码段的段内偏移量，而第16-31是段选择子，决定中断处理程序的代码段（虽然说实际上该项一般都能且只能是内核代码段）。这些项共同决定了中断处理程序代码入口最终的物理地址。

## Challenge1
Challenge1已经完成，内容见代码。主要难点在于特权级有/无切换时，iret对于栈内容理解不一致的问题。