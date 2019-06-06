# Lab1报告
2011011384  郑玉昆  计34  
## 实验报告要求
为了实现lab1的目标，lab1提供了6个基本练习和1个扩展练习，要求完成实验报告。  
对实验报告的要求：
* 基于markdown格式来完成，以文本方式为主。
* 填写各个基本练习中要求完成的报告内容
* 完成实验后，请分析ucore_lab中提供的参考答案，并请在实验报告中说明你的实现与参考答案的区别
* 列出你认为本实验中重要的知识点，以及与对应的OS原理中的知识点，并简要说明你对二者的含义，关系，差异等方面的理解（也可能出现实验中的知识点没有对应的原理知识点）
* 列出你认为OS原理中很重要，但在实验中没有对应上的知识点

## 练习1：理解通过make生成执行文件的过程
1. 操作系统镜像文件ucore.img是如何一步一步生成的？(需要比较详细地解释Makefile中每一条相关命令和命令参数的含义，以及说明命令导致的结果)
	```
	moocos-> make V=
	```  
	//生成init.o  
	```
	+ cc kern/init/init.c
	gcc -Ikern/init/ -fno-builtin -Wall -ggdb -m32 -gstabs -nostdinc  -fno-stack-protector -Ilibs/ -Ikern/debug/ -Ikern/driver/ -Ikern/trap/ -Ikern/mm/ -c kern/init/init.c -o obj/kern/init/init.o
	```
	
	参数：
	* -I<dir>	将dir作为-l链接的搜索路径加入到-l的搜索路径列表中。它的搜索顺序位于标准库之前。
	* -fno-builtin  允许加入的新函数与原先库函数冲突
	* -Wall   	显示警告信息
	* -ggdb  	尽可能的生成gdb的可以使用的调试信息
	* -m32  	生成适用于32位环境的代码
	* -gstab	此选项以stabs格式声称调试信息,但是不包括gdb调试信息
	* -nostdinc  	不使用标准库
	* -fno-stack-protector  不生成用于检测缓冲区溢出的代码
	* -c  		只激活预处理,编译,和汇编,也就是只把程序做成obj文件
	* -o  		制定目标名称

	//生成readline.o
	```
	+ cc kern/libs/readline.c
	gcc -Ikern/libs/ -fno-builtin -Wall -ggdb -m32 -gstabs -nostdinc  -fno-stack-protector -Ilibs/ -Ikern/debug/ -Ikern/driver/ -Ikern/trap/ -Ikern/mm/ -c kern/libs/readline.c -o obj/kern/libs/readline.o
	```
	//生成stdio.o
	```
	+ cc kern/libs/stdio.c
	gcc -Ikern/libs/ -fno-builtin -Wall -ggdb -m32 -gstabs -nostdinc  -fno-stack-protector -Ilibs/ -Ikern/debug/ -Ikern/driver/ -Ikern/trap/ -Ikern/mm/ -c kern/libs/stdio.c -o obj/kern/libs/stdio.o
	```
	//生成kdebug.o
	```
	+ cc kern/debug/kdebug.c
	gcc -Ikern/debug/ -fno-builtin -Wall -ggdb -m32 -gstabs -nostdinc  -fno-stack-protector -Ilibs/ -Ikern/debug/ -Ikern/driver/ -Ikern/trap/ -Ikern/mm/ -c kern/debug/kdebug.c -o obj/kern/debug/kdebug.o
	```
	//生成kmonitor.o
	```
	+ cc kern/debug/kmonitor.c
	gcc -Ikern/debug/ -fno-builtin -Wall -ggdb -m32 -gstabs -nostdinc  -fno-stack-protector -Ilibs/ -Ikern/debug/ -Ikern/driver/ -Ikern/trap/ -Ikern/mm/ -c kern/debug/kmonitor.c -o obj/kern/debug/kmonitor.o
	```
	//生成panic.o
	```
	+ cc kern/debug/panic.c
	gcc -Ikern/debug/ -fno-builtin -Wall -ggdb -m32 -gstabs -nostdinc  -fno-stack-protector -Ilibs/ -Ikern/debug/ -Ikern/driver/ -Ikern/trap/ -Ikern/mm/ -c kern/debug/panic.c -o obj/kern/debug/panic.o
	```
	//生成clock.o
	```
	+ cc kern/driver/clock.c
	gcc -Ikern/driver/ -fno-builtin -Wall -ggdb -m32 -gstabs -nostdinc  -fno-stack-protector -Ilibs/ -Ikern/debug/ -Ikern/driver/ -Ikern/trap/ -Ikern/mm/ -c kern/driver/clock.c -o obj/kern/driver/clock.o
	```
	//生成console.o
	```
	+ cc kern/driver/console.c
	gcc -Ikern/driver/ -fno-builtin -Wall -ggdb -m32 -gstabs -nostdinc  -fno-stack-protector -Ilibs/ -Ikern/debug/ -Ikern/driver/ -Ikern/trap/ -Ikern/mm/ -c kern/driver/console.c -o obj/kern/driver/console.o
	```
	//生成intr.o
	```
	+ cc kern/driver/intr.c
	gcc -Ikern/driver/ -fno-builtin -Wall -ggdb -m32 -gstabs -nostdinc  -fno-stack-protector -Ilibs/ -Ikern/debug/ -Ikern/driver/ -Ikern/trap/ -Ikern/mm/ -c kern/driver/intr.c -o obj/kern/driver/intr.o
	```
	//生成picirq.o
	```
	+ cc kern/driver/picirq.c
	gcc -Ikern/driver/ -fno-builtin -Wall -ggdb -m32 -gstabs -nostdinc  -fno-stack-protector -Ilibs/ -Ikern/debug/ -Ikern/driver/ -Ikern/trap/ -Ikern/mm/ -c kern/driver/picirq.c -o obj/kern/driver/picirq.o
	```
	//生成trap.o
	```
	+ cc kern/trap/trap.c
	gcc -Ikern/trap/ -fno-builtin -Wall -ggdb -m32 -gstabs -nostdinc  -fno-stack-protector -Ilibs/ -Ikern/debug/ -Ikern/driver/ -Ikern/trap/ -Ikern/mm/ -c kern/trap/trap.c -o obj/kern/trap/trap.o
	```
	//生成trapentry.o
	```
	+ cc kern/trap/trapentry.S
	gcc -Ikern/trap/ -fno-builtin -Wall -ggdb -m32 -gstabs -nostdinc  -fno-stack-protector -Ilibs/ -Ikern/debug/ -Ikern/driver/ -Ikern/trap/ -Ikern/mm/ -c kern/trap/trapentry.S -o obj/kern/trap/trapentry.o
	```
	//生成vectors.o
	```
	+ cc kern/trap/vectors.S
	gcc -Ikern/trap/ -fno-builtin -Wall -ggdb -m32 -gstabs -nostdinc  -fno-stack-protector -Ilibs/ -Ikern/debug/ -Ikern/driver/ -Ikern/trap/ -Ikern/mm/ -c kern/trap/vectors.S -o obj/kern/trap/vectors.o
	```
	//生成pmm.o
	```
	+ cc kern/mm/pmm.c
	gcc -Ikern/mm/ -fno-builtin -Wall -ggdb -m32 -gstabs -nostdinc  -fno-stack-protector -Ilibs/ -Ikern/debug/ -Ikern/driver/ -Ikern/trap/ -Ikern/mm/ -c kern/mm/pmm.c -o obj/kern/mm/pmm.o
	```
	//生成printfmt.o
	```
	+ cc libs/printfmt.c
	gcc -Ilibs/ -fno-builtin -Wall -ggdb -m32 -gstabs -nostdinc  -fno-stack-protector -Ilibs/  -c libs/printfmt.c -o obj/libs/printfmt.o
	```
	//生成string.o
	```
	+ cc libs/string.c
	gcc -Ilibs/ -fno-builtin -Wall -ggdb -m32 -gstabs -nostdinc  -fno-stack-protector -Ilibs/  -c libs/string.c -o obj/libs/string.o
	```
	//生成kernel，将之前生成的 .o文件链接到一起。
	```
	+ ld bin/kernel
	ld -m    elf_i386 -nostdlib -T tools/kernel.ld -o bin/kernel  obj/kern/init/init.o obj/kern/libs/readline.o obj/kern/libs/stdio.o obj/kern/debug/kdebug.o obj/kern/debug/kmonitor.o obj/kern/debug/panic.o obj/kern/driver/clock.o obj/kern/driver/console.o obj/kern/driver/intr.o obj/kern/driver/picirq.o obj/kern/trap/trap.o obj/kern/trap/trapentry.o obj/kern/trap/vectors.o obj/kern/mm/pmm.o  obj/libs/printfmt.o obj/libs/string.o
	```

	参数：  
	* -m  将创建输出文件所要处理的所有文件的名称和归档成员列到标准输出。不列出共享对象和导入文件。
	* elf_i386  规定文件的格式
	* -nostdlib  仅搜索那些在命令行上显式指定的库路径. 在连接脚本中(包含在命令行上指定的连接脚本)指定的库路径都被忽略
	* -T tools/kernel.ld  把tools/kernel.ld作为连接脚本使用.这个脚本会替代'ld'的缺省连接脚本(而不是增加它的内容),所以命令文件必须指定所有需要的东西以精确描述输出文件.如果SCRIPTFILE在当前目录下不存在,'ld'会在'-L'选项指定的所有目录下去寻找.多个'-T'选项会使内容累积.
	* -o bin/kernel  使用OUTPUT作为'ld'产生的程序的名字;如果这个选项没有指定,缺省的输出文件名是'a.out'.脚本命令'OUTPUT'也可以被用来指定输出文件的文件名.

	//生成bootasm.o
	```
	+ cc boot/bootasm.S
	gcc -Iboot/ -fno-builtin -Wall -ggdb -m32 -gstabs -nostdinc  -fno-stack-protector -Ilibs/ -Os -nostdinc -c boot/bootasm.S -o obj/boot/bootasm.o
	```
	* -Os  为减小代码大小而进行优化。

	//生成bootmain.o
	```
	+ cc boot/bootmain.c
	gcc -Iboot/ -fno-builtin -Wall -ggdb -m32 -gstabs -nostdinc  -fno-stack-protector -Ilibs/ -Os -nostdinc -c boot/bootmain.c -o obj/boot/bootmain.o
	```
	//生成sign.o和sign
	```
	+ cc tools/sign.c
	gcc -Itools/ -g -Wall -O2 -c tools/sign.c -o obj/sign/tools/sign.o
	gcc -g -Wall -O2 obj/sign/tools/sign.o -o bin/sign
	```
	* -O2  优化

	//将bootasm.o和bootmain.o链接到一起，生成bootblock.o
	```
	+ ld bin/bootblock
	ld -m    elf_i386 -nostdlib -N -e start -Ttext 0x7C00 obj/boot/bootasm.o obj/boot/bootmain.o -o obj/bootblock.o
	```
	* -N 把text和data节设置为可读写.同时,取消数据节的页对齐,同时,取消对共享库的连接.如果输出格式 
	* -e 使用符号start作为你的程序的开始执行点,而不是使用缺省的进入点
	* -Ttext  制定代码段开始位置

	//生成一个有10000个块的文件，每个块默认512字节，用0填充
	```
	dd if=/dev/zero of=bin/ucore.img count=10000
	```
	//把bootblock中的内容写到第一个块
	```
	dd if=bin/bootblock of=bin/ucore.img conv=notrunc
	```
	//从第二个块开始写kernel中的内容
	```
	dd if=bin/kernel of=bin/ucore.img seek=1 conv=notrunc
	```

2. 一个被系统认为是符合规范的硬盘主引导扇区的特征是什么？  

	```C
	char buf[512];
	memset(buf, 0, sizeof(buf));
	FILE *ifp = fopen(argv[1], "rb");
	int size = fread(buf, 1, st.st_size, ifp);
	if (size != st.st_size) {
		fprintf(stderr, "read '%s' error, size is %d.\n", argv[1], size);
        	return -1;
        }
        fclose(ifp);
    	buf[510] = 0x55;
    	buf[511] = 0xAA;
    	FILE *ofp = fopen(argv[2], "wb+");
    	size = fwrite(buf, 1, 512, ofp);
    	if (size != 512) {
        	fprintf(stderr, "write '%s' error, size is %d.\n", argv[2], size);
        	return -1;
	}
	```
	
	由上述sign.c中的代码可知，硬盘主引导扇区大小为512 byte，且最后两位分别为0x55和 0xAA .
