# 目的
ここでは次の３つに着目して、どのようにこれらのシステムコールが呼び出されるのかを見ていくことにする。
- システムコール番号2: exit
- システムコール番号3: ptregs_fork
- システムコール番号4-6: sys_read, sys_write, sys_open

# 詳細

TODO: システムコール番号1番のsys_restart_syscallは追えなかったので２番のexitからにする。

### システムコール番号２番：exitを覗いてみる
続いて、上記syscall_callという関数をどのように呼び出すのかをみていく
実体についてはasmlinkageという文言でgrepをかけると定義しているヘッダファイルを見つけられるらしい。

sys_exitの場合だと以下のようになる。
```
$ grep -rinH sys_exit * | grep -i asmlinkage
./include/linux/syscalls.h:420:asmlinkage long sys_exit(int error_code);
./include/linux/syscalls.h:421:asmlinkage long sys_exit_group(int error_code);
```

exitの場合はわかりにくいが、以下が実体である。
```
kernel/exit.c
1053 SYSCALL_DEFINE1(exit, int, error_code)
1054 {
1055     do_exit((error_code&0xff)<<8);
1056 }
```

do_exit関数は同ファイルで定義されているが、ここではSYSCALL_DEFINE1という定義が不明なので追っていくことにする。
```
include/linux/syscalls.h
261 #define SYSCALL_DEFINE1(name, ...) SYSCALL_DEFINEx(1, _##name, __VA_ARGS__)
```

include/linux/syscalls.hを見ると以下のように定義されている。
```
include/linux/syscalls.h
282 #ifdef CONFIG_FTRACE_SYSCALLS
283 #define SYSCALL_DEFINEx(x, sname, ...)              \
284     static const char *types_##sname[] = {          \
285         __SC_STR_TDECL##x(__VA_ARGS__)          \
286     };                          \
287     static const char *args_##sname[] = {           \
288         __SC_STR_ADECL##x(__VA_ARGS__)          \
289     };                          \
290     SYSCALL_METADATA(sname, x);             \
291     __SYSCALL_DEFINEx(x, sname, __VA_ARGS__)
292 #else
293 #define SYSCALL_DEFINEx(x, sname, ...)              \
294     __SYSCALL_DEFINEx(x, sname, __VA_ARGS__)
295 #endif
```

ftraceは自身の今回の環境だとCONFIG_FTRACE_SYSCALLSのdefineが定義されているものとしてみていけば良い。
ということで、SYSCALL_METADATAと__SYSCAL_DEFINExをそれぞれ見ていくことにする。
```
$ cat /boot/config-3.10.0-693.el7.x86_64  | grep -i CONFIG_FTRACE_SYSCALLS
CONFIG_FTRACE_SYSCALLS=y
```

SYSCALL_METADATAは次のように定義されている。
```
229 #define SYSCALL_METADATA(sname, nb)             \
230     SYSCALL_TRACE_ENTER_EVENT(sname);           \
231     SYSCALL_TRACE_EXIT_EVENT(sname);            \
232     static const struct syscall_metadata __used     \
233       __attribute__((__aligned__(4)))           \
234       __attribute__((section("__syscalls_metadata")))   \
235       __syscall_meta_##sname = {                \
236         .name       = "sys"#sname,          \
237         .nb_args    = nb,               \
238         .types      = types_##sname,        \
239         .args       = args_##sname,         \
240         .enter_event    = &event_enter_##sname,     \
241         .exit_event = &event_exit_##sname,      \
242     };
```

__SYSCALL_DEFINExは以下のように定義されていて、CONFIG_HAVE_SYSCALL_WRAPPERSによって分岐されるようで今回はelseを見ていく。
```
include/linux/syscalls.h
297 #ifdef CONFIG_HAVE_SYSCALL_WRAPPERS
298 
299 #define SYSCALL_DEFINE(name) static inline long SYSC_##name
300 
301 #define __SYSCALL_DEFINEx(x, name, ...)                 \
302     asmlinkage long sys##name(__SC_DECL##x(__VA_ARGS__));       \
303     static inline long SYSC##name(__SC_DECL##x(__VA_ARGS__));   \
304     asmlinkage long SyS##name(__SC_LONG##x(__VA_ARGS__))        \
305     {                               \
306         __SC_TEST##x(__VA_ARGS__);              \
307         return (long) SYSC##name(__SC_CAST##x(__VA_ARGS__));    \
308     }                               \
309     SYSCALL_ALIAS(sys##name, SyS##name);                \
310     static inline long SYSC##name(__SC_DECL##x(__VA_ARGS__))
311 
312 #else /* CONFIG_HAVE_SYSCALL_WRAPPERS */
313 
314 #define SYSCALL_DEFINE(name) asmlinkage long sys_##name
315 #define __SYSCALL_DEFINEx(x, name, ...)                 \
316     asmlinkage long sys##name(__SC_DECL##x(__VA_ARGS__))
317 
318 #endif /* CONFIG_HAVE_SYSCALL_WRAPPERS */
```

なお、SYSCALL_DEFINE1〜SYSCALL_DEFINE5まで存在していてこの数字はシステムコールの引数の数を表しているようだ。　

CONFIG_HAVE_SYSCALL_WRAPPERSがある場合には、ない場合と比較していくつか定義が増えているようだ(検索してみたけど不明。読むしかなさそう)  
とりあえずは、両方とも以下の実体は定義しているので以下と考えて進めていくいことにする。
```
asmlinkage long sys##name(__SC_DECL##x(__VA_ARGS__));
```

引数に値を入れると以下のようになる。
```
asmlinkage long sysexit(__SC_DECL1(int, error_code));
```

__SC_DECL1は以下で定義されている。
```
include/linux/syscalls.h
72 #define __SC_DECL1(t1, a1)  t1 a1
```

よって、先ほどの関数定義は以下のように展開されることになる。
```
asmlinkage long sysexit(int, error_code);
```

### システムコール番号３番：ptregs_forkを覗いてみる
続いて、syscall_tableの３番目に定義されたptregs_forkを覗いてみる。
```
$ grep -rinH ptregs_fork .
./arch/um/sys-i386/sys_call_table.S:12:#define ptregs_fork sys_fork
./arch/x86/kernel/syscall_table_32.S:4:	.long ptregs_fork
```

ptregs_forkはsys_forkとdefineされている。sys_fork定義は以下の通り
```
/arch/x86/kernel/process.c
217 int sys_fork(struct pt_regs *regs)
218 {
219     return do_fork(SIGCHLD, regs->sp, regs, 0, NULL, NULL);
220 }
```

なお、sys_forkが呼び出すdo_forkはkernel/fork.cに定義されている。


### システムコール番号４〜６番：sys_read, sys_write, sys_openを覗いてみる

定義は以下に記述されている。
```
include/linux/syscalls.h
586 asmlinkage long sys_open(const char __user *filename,
587                 int flags, int mode);
...
631 asmlinkage long sys_read(unsigned int fd, char __user *buf, size_t count);
...
636 asmlinkage long sys_write(unsigned int fd, const char __user *buf,
637               size_t count);
```

sys_readやsys_writeについては、fs/read_write.cは以下で定義されている。  
SYSCALL_DEFINE3というdefineが利用されているという規則を知っていないと見つけにくいかもしれない。
```
fs/read_write.c
372 SYSCALL_DEFINE3(read, unsigned int, fd, char __user *, buf, size_t, count)
373 {
374     struct file *file;
375     ssize_t ret = -EBADF;
376     int fput_needed;
377 
378     file = fget_light(fd, &fput_needed);
379     if (file) {
380         loff_t pos = file_pos_read(file);
381         ret = vfs_read(file, buf, count, &pos);
382         file_pos_write(file, pos);
383         fput_light(file, fput_needed);
384     }
385 
386     return ret;
387 }
388 
389 SYSCALL_DEFINE3(write, unsigned int, fd, const char __user *, buf,
390         size_t, count)
391 {
392     struct file *file;
393     ssize_t ret = -EBADF;
394     int fput_needed;
395 
396     file = fget_light(fd, &fput_needed);
397     if (file) {
398         loff_t pos = file_pos_read(file);
399         ret = vfs_write(file, buf, count, &pos);
400         file_pos_write(file, pos);
401         fput_light(file, fput_needed);
402     }
403 
404     return ret;
405 }
```

sys_openについてはfs/open.cに以下のように定義されています。
```
fs/open.c
1053 SYSCALL_DEFINE3(open, const char __user *, filename, int, flags, int, mode)
1054 {
1055     long ret;
1056 
1057     if (force_o_largefile())
1058         flags |= O_LARGEFILE;
1059 
1060     ret = do_sys_open(AT_FDCWD, filename, flags, mode);
1061     /* avoid REGPARM breakage on x86: */
1062     asmlinkage_protect(3, ret, filename, flags, mode);
1063     return ret;
1064 }
```
