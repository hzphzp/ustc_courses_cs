## 练习4：分析bootloader加载ELF格式的OS的过程
通过阅读bootmain.c，了解bootloader如何加载ELF文件。通过分析源代码和通过qemu来运行并调试bootloader&OS.  
* bootloader如何读取硬盘扇区的？  
  见函数readsect()和readseg()中的中文注释  
* bootloader是如何加载ELF格式的OS？  
  见函数bootmain()中的中文注释  
  ```C
    #include <defs.h>
    #include <x86.h>
    #include <elf.h>
    
    #define SECTSIZE        512
    #define ELFHDR          ((struct elfhdr *)0x10000)      // scratch space
    
    /* waitdisk - wait for disk ready */
    static void
    waitdisk(void) {
        while ((inb(0x1F7) & 0xC0) != 0x40)
            /* do nothing */;
    }
    
    /* readsect - read a single sector at @secno into @dst */
    static void
    readsect(void *dst, uint32_t secno) {
        // wait for disk to be ready
        //等待硬盘准备好
        waitdisk();
    
        //准备好后开始发出读取命令
        outb(0x1F2, 1);                         // count = 1，表明读取的扇区数量为1个
        outb(0x1F3, secno & 0xFF);              //设置扇区号
        outb(0x1F4, (secno >> 8) & 0xFF);
        outb(0x1F5, (secno >> 16) & 0xFF);
        outb(0x1F6, ((secno >> 24) & 0xF) | 0xE0);
        //读取扇区
        outb(0x1F7, 0x20);                      // cmd 0x20 - read sectors
    
        // wait for disk to be ready
        waitdisk();
    
        //读取到dst，单位为双字
        // read a sector
        insl(0x1F0, dst, SECTSIZE / 4);
    }
    
    /* *
     * readseg - read @count bytes at @offset from kernel into virtual address @va,
     * might copy more than asked.
     * */
    static void
    readseg(uintptr_t va, uint32_t count, uint32_t offset) {
        uintptr_t end_va = va + count;
    
        // round down to sector boundary
        va -= offset % SECTSIZE;
        //定位到ELF数据的位置
        // translate from bytes to sectors; kernel starts at sector 1
        uint32_t secno = (offset / SECTSIZE) + 1;
        //批量读入任意长度的数据
        // If this is too slow, we could read lots of sectors at a time.
        // We'd write more to memory than asked, but it doesn't matter --
        // we load in increasing order.
        for (; va < end_va; va += SECTSIZE, secno ++) {
            readsect((void *)va, secno);
        }
    }
    
    /* bootmain - the entry of bootloader */
    void
    bootmain(void) {
        //读取8个扇区大小的文件头部
        // read the 1st page off disk
        readseg((uintptr_t)ELFHDR, SECTSIZE * 8, 0);
        //通过文件头部中存储的e_magic判断文件是否合法
        // is this a valid ELF?
        if (ELFHDR->e_magic != ELF_MAGIC) {
            goto bad;
        }
    
        struct proghdr *ph, *eph;
        //获取文件的描述符
        // load each program segment (ignores ph flags)
        ph = (struct proghdr *)((uintptr_t)ELFHDR + ELFHDR->e_phoff);
        eph = ph + ELFHDR->e_phnum;
        //加载文件数据到内存
        for (; ph < eph; ph ++) {
            readseg(ph->p_va & 0xFFFFFF, ph->p_memsz, ph->p_offset);
        }
        //进入内核
        // call the entry point from the ELF header
        // note: does not return
        ((void (*)(void))(ELFHDR->e_entry & 0xFFFFFF))();   
    
    bad:
        outw(0x8A00, 0x8A00);
        outw(0x8A00, 0x8E00);   
    
        /* do nothing */
        while (1);
    }
    ```

提示：可阅读“硬盘访问概述”，“ELF执行文件格式概述”这两小节。