#Mooc-OS-Chapter4笔记
[TOC]
##4.1 启动顺序
* x86启动顺序
	1. 启动过程
		* 寄存器初始状态
			* 启动地址：由段地址CS与EIP决定
			* EFLAGS：标志位
			* CR0：控制寄存器
			* 通用寄存器：初始值为零
			* 
	2. 实模式和保护模式
	3. 段机制
* C函数调用
* gcc内联汇编（inline assembly）
* x86-32下的中断处理
* 小结
##4.2 C函数调用的实现
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

* 参数和函数返回值可通过寄存器或者位于内存的栈来传递
* 不需要保存/恢复所有寄存器，只需保存和恢复被调函数会使用的寄存器即可

##4.3 GCC内联汇编
* 定义
	
	``在C中插入汇编，调用C语言不支持的指令，或通过汇编实现手动优化``

##4.3 x86中的中断处理
* 中断分类
	* 外部设备产生的中断
	* 软件产生的中断，通常用于系统调用
* 异常分类
	* 程序错误
	* 软件产生的异常
	* 机器检查出的异常
* ISR、IDT、IDTR
	* 每个中断或异常关联一个中断服务例程（ISR）
	* 关联关系存在中断描述符表（IDT）中
	* IDT的起始地址和大小保存在中断描述附表寄存器（IDTR）中

##4.4 x86中断处理过程
