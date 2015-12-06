
ソースコードは、ロングサポート版のlinux-2.6.32.65にて調査を行い、32bitのx86 CPUと仮定して調査します。


# 目的
システムコールについてどのような仕組みで実装されているのかについて調査します。
- システムブート時にinit/main.cのstart_kernel関数からtrap_initという関数が呼ばれています。
 - 32bitのx86系の場合arch/x86/kernel/head32.ci386_start_kernel()からstart_kernelが呼ばれています。
- この際にシステムコール情報をIDTテーブルに登録します。これによってシステムコールが利用できるようになります。
- int 0x80が呼び出された際にシステムコールが呼ばれます。
- 例えば、printfなどのコールが呼ばれるとwriteが呼ばれます。



# 概要
そもそもシステムコールとは、カーネル内部の機能を普通のユーザー空間にあるプロセスからでも利用できるための仕組みです。  
レジスタに決まった値をセットしてint 0x80という命令を実行すると割り込みが発生します。  


例えば、printfなどを呼び出すときにはwriteというシステムコールが利用されます。  
このようなシステムコール命令を発行する際には、レジスタにシステムコール番号と引数を指定してint 0x80命令を実行します(最近のx86だとsysenterという命令で入ることができてこちらの方が推奨されているらしいですが今回はint 0x80で進めます。)
システムコールが失敗した場合にはエラーコードがグローバル変数errnoに格納されます。

システムコールは一般ユーザが直接叩くようなことは通常なく、glibcの関数経由で呼び出したりします。


システムコールを理解するためにはシステムコールがアセンブラレベルでどのように呼び出されるのかを理解しておく必要があります。

ATT記法だと以下のように呼び出すようです。(手元Macのため、まだ試せていません)
```
.data
hello:
    .string "Hello world!\n"

.text
.globl _start
_start:
    movl $4, %eax # write(1, hello, strlen(hello))
    movl $1, %ebx
    movl $hello, %ecx
    movl $13, %edx
    int  $0x80

    movl $1, %eax # exit(0)
    movl $0, %ebx
    int  $0x80
```

レジスタへの値は何を意味しているかというと下記設定を行った後にint 0x80命令を発行していることを表します。
- EAX: システムコール番号
- EBX: 出力先ファイルディスクリプタ(標準出力は1となる)
- ECX: 出力データのアドレス
- EDX: 出力データのサイズ

これを頭に入れて進んでいきましょう。


# 詳細

## ブート時のIDT登録の流れを理解する。
システムコール一覧が定義されているファイルはsys_call_tableです。
```
./arch/x86/kernel/syscall_table_32.S 
  1 ENTRY(sys_call_table)
  2     .long sys_restart_syscall   /* 0 - old "setup()" system call, used for re    starting */
  3     .long sys_exit
  4     .long ptregs_fork
  5     .long sys_read
  6     .long sys_write
  7     .long sys_open      /* 5 */
  (以下略, 336個まで登録されていた)
```


上記ファイルの関数名はエイリアスであり、以下は関数名とシステムコール番号を紐付けています。
```
arch/x86/include/asm/unistd_32.h
  4 /*
  5  * This file contains the system call numbers.
  6  */
  7 
  8 #define __NR_restart_syscall      0
  9 #define __NR_exit         1
 10 #define __NR_fork         2
 11 #define __NR_read         3
 12 #define __NR_write        4
 13 #define __NR_open         5
 14 #define __NR_close        6
 15 #define __NR_waitpid          7
```

sys_call_table関数をコールするのはsyscall_callです。
その関数が定義されているすぐ上にはsystem_callという名前の関数が定義されている点にも着目します。

```
./arch/x86/kernel/entry_32.S 
 518 ENTRY(system_call)
 519     RING0_INT_FRAME         # can't unwind into user space anyway
 520     pushl %eax          # save orig_eax
 521     CFI_ADJUST_CFA_OFFSET 4
 522     SAVE_ALL                # レジスタ群をカーネルスタックにPUSH
 523     GET_THREAD_INFO(%ebp)
 524                     # system call tracing in operation / emulation  bpにthred_infoのポインタを取得する。
 525     testl $_TIF_WORK_SYSCALL_ENTRY,TI_flags(%ebp)
 526     jnz syscall_trace_entry # straceされていればその処理を行う
 527     cmpl $(nr_syscalls), %eax
 528     jae syscall_badsys
 529 syscall_call:
 530     call *sys_call_table(,%eax,4)   # AXコードに応じたシステム関数のコールを行う
```

syscall_callは同一ファイルのsyscall_trace_entryという関数で呼び出されているがこれは名称からトレース用と判断されるのでここではスルーします(上記アセンブラでも呼ばれていることが確認できます)  

sys_call_tableは、処理関数のアドレスが番号順に設定されているテーブルです。サイズは４バイトです。従ってAXを４倍したsys_call_tableからのオフセットに目的とする処理があり、そこをコールすることで、AXコード（システムコール）が呼び出されるようになっています。

start_kernel関数が呼び出すtrap_init関数の中でsystem_callを登録している箇所がありました。
なお、SYSCALL_VECTORは0x80と定義されています。

```
 941 void __init trap_init(void)
 942 {
 ...
1004     set_system_trap_gate(SYSCALL_VECTOR, &system_call);
1005     set_bit(SYSCALL_VECTOR, used_vectors);
```

set_system_trap_gateが何をしているのか深くみていきましょう。
```
arch/x86/include/asm/desc.h
365 static inline void set_system_trap_gate(unsigned int n, void *addr)
366 {        
367     BUG_ON((unsigned)n > 0xFF);
368     _set_gate(n, GATE_TRAP, addr, 0x3, 0, __KERNEL_CS);
369 }
```

GATE_TRAPはenumで0xFと定義されています。
__KERNEL_CSは以下のように定義されています。
```
#define __KERNEL_CS (GDT_ENTRY_KERNEL_CS * 8)
149 #define GDT_ENTRY_KERNEL_CS 2
```

BUG_ONはgrepすると以下の２行設定がある。CONFIG_BUGが定義されているかどうかでわかれるようだ(詳細不明)
これはLinuxカーネルにおいて引数に与えられた式が真にならバグとして扱われる。つまりassertのようなものらしい。
```
include/asm-generic/bug.h
 50 #define BUG_ON(condition) do { if (unlikely(condition)) BUG(); } while(0)  // CONFIG_BUGがある場合
112 #define BUG_ON(condition) do { if (condition) ; } while(0)                 // CONFIG_BUGがない場合
```

_set_gateは以下のような定義となっている。
pack_gateは次に実行するために必要なデータを詰め込んで、write_idt_entryでIDTを書き込んでいるものと考えられる。さらに深追いする。
```
arch/x86/include/asm/desc.h
312 static inline void _set_gate(int gate, unsigned type, void *addr,
313                  unsigned dpl, unsigned ist, unsigned seg)
314 {
315     gate_desc s;
316     pack_gate(&s, type, (unsigned long)addr, dpl, ist, seg);
317     /*
318      * does not need to be atomic because it is only done once at
319      * setup time
320      */
321     write_idt_entry(idt_table, gate, &s);
322 }
```

pack_gateは以下のように定義されている。CONFIG_X86_64かどうかで定義が異なるようだが今回は32bit用なのでelse側を見れば良いと思われる。
pack_gateについては下記URLを参考のこと
- https://0xax.gitbooks.io/linux-insides/content/interrupts/interrupts-2.html
```
arch/x86/include/asm/desc.h
 46 #ifdef CONFIG_X86_64
 47 
 48 static inline void pack_gate(gate_desc *gate, unsigned type, unsigned long fu    nc,
 49                  unsigned dpl, unsigned ist, unsigned seg)
 50 {
 51     gate->offset_low = PTR_LOW(func);
 52     gate->segment = __KERNEL_CS;
 53     gate->ist = ist;
 54     gate->p = 1;
 55     gate->dpl = dpl;
 56     gate->zero0 = 0;
 57     gate->zero1 = 0;
 58     gate->type = type;
 59     gate->offset_middle = PTR_MIDDLE(func);
 60     gate->offset_high = PTR_HIGH(func);
 61 }
 62 
 63 #else
 64 static inline void pack_gate(gate_desc *gate, unsigned char type,
 65                  unsigned long base, unsigned dpl, unsigned flags,
 66                  unsigned short seg)
 67 {
 68     gate->a = (seg << 16) | (base & 0xffff);
 69     gate->b = (base & 0xffff0000) |
 70           (((0x80 | type | (dpl << 5)) & 0xff) << 8);
 71 }
 72 
 73 #endif
```


write_idt_entryはマクロとして定義されていて、gateをidtテーブルに記録する。
```
arch/x86/include/asm/desc.h
101 #define write_idt_entry(dt, entry, g)       \
102     native_write_idt_entry(dt, entry, g)
(中略)
115 static inline void native_write_idt_entry(gate_desc *idt, int entry,
116                       const gate_desc *gate)
117 {
118     memcpy(&idt[entry], gate, sizeof(*gate));
119 }
```

以上でIDTの登録は完了となる。


## システムコール関数の詳細を追ってみる

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

exitの場合はわかりにくいが、いかが実体である。
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

hを見ると以下のように定義されている。ftraceはおそらくトレース用だろうということでelse側を見ていけばよい。
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


__SYSCALL_DEFINExは以下のように定義されていて、CONFIG_HAVE_SYSCALL_WRAPPERSによって分岐されるようだ。
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

CONFIG_HAVE_SYSCALL_WRAPPERSがある場合には、ない場合と比較していくつか定義が増えているようだ(検索してみたけど不明。読むしかなさそう。)  
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

# 参考URL
- asmlinkageの実体について
 - http://d.hatena.ne.jp/Yusuke_Yamamoto/20070701
- システムコール呼び出しの単純なアセンブラ
 - http://qiita.com/kure/items/5a1a114f9a37aeab255c
- BUG_ONマクロについての説明
 - http://d.hatena.ne.jp/fixme/20101030/1288433811
- pack_gateメソッドに関する説明
 - https://0xax.gitbooks.io/linux-insides/content/interrupts/interrupts-2.html
- システムコールとLinuxカーネルのソース(筑波大学)
 - http://www.coins.tsukuba.ac.jp/~yas/coins/os2-2010/2010-12-07/
- システムコールとカーネルの関数
 - 表形式になっているので眺めてみるだけでもいいかも
 - http://www.mztn.org/lxasm/syscalltb.html
