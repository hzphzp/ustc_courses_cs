## 练习3：分析bootloader进入保护模式的过程

BIOS将通过读取硬盘主引导扇区到内存，并转跳到对应内存中的位置执行bootloader。请分析bootloader是如何完成从实模式进入保护模式的。  
  a.从cs = 0 && ip = 0x7c00进入bootloader启动过程，先关闭中断使能，将寄存器置零  
  ```
.code16                                             # Assemble for 16-bit mode
    cli                                             # Disable interrupts
    cld                                             # String operations increment

    # Set up the important data segment registers (DS, ES, SS).
    xorw %ax, %ax                                   # Segment number zero
    movw %ax, %ds                                   # -> Data Segment
    movw %ax, %es                                   # -> Extra Segment
    movw %ax, %ss                                   # -> Stack Segment
  ```
  b. 开启A20，以便能够通过总线访问更大的内存空间
  ```
    # Enable A20:
    #  For backwards compatibility with the earliest PCs, physical
    #  address line 20 is tied low, so that addresses higher than
    #  1MB wrap around to zero by default. This code undoes this.
seta20.1:
    inb $0x64, %al                                  # Wait for not busy(8042 input buffer empty).
    testb $0x2, %al
    jnz seta20.1

    movb $0xd1, %al                                 # 0xd1 -> port 0x64
    outb %al, $0x64                                 # 0xd1 means: write data to 8042's P2 port

seta20.2:
    inb $0x64, %al                                  # Wait for not busy(8042 input buffer empty).
    testb $0x2, %al
    jnz seta20.2

    movb $0xdf, %al                                 # 0xdf -> port 0x60
    outb %al, $0x60                                 # 0xdf = 11011111, means set P2's A20 bit(the 1 bit) to 1
  ```
  c. 初始化GDT
  ```
    # Switch from real to protected mode, using a bootstrap GDT
    # and segment translation that makes virtual addresses
    # identical to physical addresses, so that the
    # effective memory map does not change during the switch.
    lgdt gdtdesc      //初始化GDT
  ```
  d. 将cr0的PE位置1，实现从实模式切换到保护模式
  ```
    movl %cr0, %eax
    orl $CR0_PE_ON, %eax
    movl %eax, %cr0
  ```
  e. 通过跳转进入32位模式
  ```
    # Jump to next instruction, but in 32-bit code segment.
    # Switches processor into 32-bit mode.
    ljmp $PROT_MODE_CSEG, $protcseg

.code32                                             # Assemble for 32-bit mode
protcseg:
  ```
  f. 设置保护模式下的数据段寄存器
  ```
    # Set up the protected-mode data segment registers
    movw $PROT_MODE_DSEG, %ax                       # Our data segment selector
    movw %ax, %ds                                   # -> DS: Data Segment
    movw %ax, %es                                   # -> ES: Extra Segment
    movw %ax, %fs                                   # -> FS
    movw %ax, %gs                                   # -> GS
    movw %ax, %ss                                   # -> SS: Stack Segment
  ```
  g. 设置栈针，保护模式设置完毕，调用bootmain
  ```
    # Set up the stack pointer and call into C. The stack region is from 0--start(0x7c00)
    movl $0x0, %ebp
    movl $start, %esp
    call bootmain
  ```
提示：需要阅读小节“保护模式和分段机制”和lab1/boot/bootasm.S源码，了解如何从实模式切换到保护模式，需要了解：  
* 为何开启A20，以及如何开启A20
  - 为了兼容早期设备，20总线被置为0，使得此模式下能够访问的最大地址不超过1M，在ucore中最大地址为4G，故需要开启A20，以访问更大的内存空间。  
  - 开启A20：  
    等待8042 Input buffer为空；  
    发送Write 8042 Output Port （P2）命令到8042 Input buffer；  
    等待8042 Input buffer为空；  
    将8042 Output Port（P2）得到字节的第2位置1，然后写入8042 Input buffer；  
* 如何初始化GDT表
  -  一个简单的GDT表和其描述符已经静态储存在引导区中，载入即可  
    ``lgdt gdtdesc``  
* 如何使能和进入保护模式
  - 见上