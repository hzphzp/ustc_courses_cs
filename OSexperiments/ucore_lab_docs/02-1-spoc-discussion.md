##3.5 ucore系统调用分析
1. `ucore`的系统调用中*参数传递*代码分析。

    ```C
    void
    syscall(void) {
        struct trapframe *tf = current->tf;
        uint32_t arg[5];
        int num = tf->tf_regs.reg_eax;
        if (num >= 0 && num < NUM_SYSCALLS) {
            if (syscalls[num] != NULL) {
                arg[0] = tf->tf_regs.reg_edx;
                arg[1] = tf->tf_regs.reg_ecx;
                arg[2] = tf->tf_regs.reg_ebx;
                arg[3] = tf->tf_regs.reg_edi;
                arg[4] = tf->tf_regs.reg_esi;
                tf->tf_regs.reg_eax = syscalls[num](arg);
                return ;
            }
        }
        print_trapframe(tf);
        panic("undefined syscall %d, pid = %d, name = %s.\n",
                num, current->pid, current->name);
    }
    ```
2. 以getpid为例，分析ucore的系统调用中返回结果的传递代码。
3. 以ucore lab8的answer为例，分析ucore 应用的系统调用编写和含义。
4. 以ucore lab8的answer为例，尝试修改并运行ucore OS kernel代码，使其具有类似Linux应用工具strace的功能，即能够显示出应用程序发出的系统调用，从而可以分析ucore应用的系统调用执行过程。


