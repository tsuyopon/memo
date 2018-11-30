# SystemTap Sample
```
$ sudo stap watch_exec.stp -c ./test
Hello!
     0 stapio(5226): -> sys_execve
     6 stapio(5226):    name    = ./test
     7 stapio(5226):    argv[0] = ./test
     8 stapio(5226):    envp[0] = HOSTNAME=localhost.localdomain
    10 stapio(5226):    envp[1] = TERM=xterm-256color
    21 stapio(5226):  -> do_execve
    24 stapio(5226):     filename  = ./test
    25 stapio(5226):     __argv[0] = ./test
    26 stapio(5226):     __envp[0] = HOSTNAME=localhost.localdomain
    28 stapio(5226):     __envp[1] = TERM=xterm-256color
    33 stapio(5226):   -> do_execve_common.isra.27
    34 stapio(5226):      filename = ./test
    38 stapio(5226):    -> unshare_files
    40 stapio(5226):       displaced=0xffff88003d3b1ec8 task=? copy=0xffffffff81169b21 error=?
    45 stapio(5226):     -> unshare_fd
    46 stapio(5226):        unshare_flags=0x400 new_fdp=0xffff88003d3b1e80 fd=? error=0xffffffffffffffff
    52 stapio(5226):     <- unshare_files ret= 0
    54 stapio(5226):    <- do_execve_common.isra.27 ret= 0
    57 stapio(5226):    -> open_exec
    59 stapio(5226):       filename = ./test
    67 stapio(5226):    <- do_execve_common.isra.27 ret= -131940677638400
    70 stapio(5226):    -> sched_exec
    72 stapio(5226):       p=? flags=? dest_cpu=?
    75 stapio(5226):    <- do_execve_common.isra.27 
    77 stapio(5226):    -> bprm_mm_init
    79 stapio(5226):       bprm=0xffff88002ac72300 err=? mm=?
    87 stapio(5226):    <- do_execve_common.isra.27 ret= 0
    89 stapio(5226):    -> count.isra.22.constprop.30
    90 stapio(5226):       i=? max=0x7fffffff
    94 stapio(5226):    <- do_execve_common.isra.27 ret= 1
    96 stapio(5226):    -> count.isra.22.constprop.30
    97 stapio(5226):       i=? max=0x7fffffff
    98 stapio(5226):    <- do_execve_common.isra.27 ret= 16
   100 stapio(5226):    -> prepare_binprm
   102 stapio(5226):       bprm=0xffff88002ac72300 mode=? inode=? retval=?
   110 stapio(5226):    <- do_execve_common.isra.27 ret= 128
   112 stapio(5226):    -> copy_strings_kernel
   113 stapio(5226):       argc=0x1 __argv=0xffff88002ac723c8 bprm=0xffff88002ac72300 r=0x80 oldfs={...} argv={...}
   118 stapio(5226):     -> copy_strings.isra.24
   120 stapio(5226):        argc=0x1 bprm=0xffff88002ac72300 kmapped_page=? kaddr=? kpos=0x0 ret=?
   130 stapio(5226):     <- copy_strings_kernel ret= 0
   132 stapio(5226):    <- do_execve_common.isra.27 ret= 0
   134 stapio(5226):    -> copy_strings.isra.24
   135 stapio(5226):       argc=0x10 bprm=0xffff88002ac72300 kmapped_page=? kaddr=? kpos=0xffff88000c7e9000 ret=?
   141 stapio(5226):    <- do_execve_common.isra.27 ret= 0
   143 stapio(5226):    -> copy_strings.isra.24
   144 stapio(5226):       argc=0x1 bprm=0xffff88002ac72300 kmapped_page=? kaddr=? kpos=0xffff88000c7e9000 ret=?
   146 stapio(5226):    <- do_execve_common.isra.27 ret= 0
   147 stapio(5226):    -> search_binary_handler
   149 stapio(5226):       bprm=0xffff88002ac72300 regs=0xffff88003d3b1f58 depth=? try=? retval=? fmt=? old_pid=0xffffffffffff8800
   160 stapio(5226):     -> open_exec
   161 stapio(5226):        filename = /lib64/ld-linux-x86-64.so.2
   168 stapio(5226):     <- load_elf_binary ret= -131941200988672
   232 test(5226):    <- do_execve_common.isra.27 ret= 0
   235 test(5226):    -> acct_update_integrals
   237 test(5226):       tsk=0xffff88000a611720
   242 test(5226):    <- do_execve_common.isra.27 
   244 test(5226):   <- do_execve ret= 0
   246 test(5226):  <- sys_execve ret= 0
   248 test(5226): <- stub_execve ret= 0
     0 sshd(3325): -> acct_update_integrals
     0 sshd(3325):    tsk=0xffff88002ac8ae40
   206 sshd(3325): <- irqtime_account_process_tick.isra.75 
     0 sshd(3325): -> acct_update_integrals
    12 sshd(3325):    tsk=0xffff88002ac8ae40
    36 sshd(3325): <- irqtime_account_process_tick.isra.75 
     0 test(5226): -> acct_update_integrals
     0 test(5226):    tsk=0xffff88000a611720
     0 test(5226): <- do_exit 
```
