crashを使ったカーネルダンプについて
============================

## パッケージインストール
crashパッケージとkernelのdebuginfoパッケージが必要と思われる。

以下は自身のパッケージ構成例
```
$ rpm -qa | grep -i "kernel-"
kernel-3.3.4-5.fc17.x86_64
kernel-devel-3.9.10-100.fc17.x86_64
kernel-debuginfo-common-x86_64-3.3.4-5.fc17.x86_64
kernel-headers-3.9.10-100.fc17.x86_64
kernel-devel-3.3.4-5.fc17.x86_64
kernel-debuginfo-3.3.4-5.fc17.x86_64
```

debuginfoパッケージが存在しないとエラーになります。
```
$ crash

crash 7.1.9-2.el7
Copyright (C) 2002-2016  Red Hat, Inc.
Copyright (C) 2004, 2005, 2006, 2010  IBM Corporation
Copyright (C) 1999-2006  Hewlett-Packard Co
Copyright (C) 2005, 2006, 2011, 2012  Fujitsu Limited
Copyright (C) 2006, 2007  VA Linux Systems Japan K.K.
Copyright (C) 2005, 2011  NEC Corporation
Copyright (C) 1999, 2002, 2007  Silicon Graphics, Inc.
Copyright (C) 1999, 2000, 2001, 2002  Mission Critical Linux, Inc.
This program is free software, covered by the GNU General Public License,
and you are welcome to change it and/or distribute copies of it under
certain conditions.  Enter "help copying" to see the conditions.
This program has absolutely no warranty.  Enter "help warranty" for details.
 
crash: cannot find booted kernel -- please enter namelist argument


Usage:

  crash [OPTION]... NAMELIST MEMORY-IMAGE[@ADDRESS]	(dumpfile form)
  crash [OPTION]... [NAMELIST]             		(live system form)

Enter "crash -h" for details.
```

パッケージをインストールしたらあとは引数なしでsudo権限でcrashコマンドを実行する。
crashコマンドを実行しただけでcrashのインタプリタに遷移しない場合には、debuginfo等の必要なパッケージが不足していると思われる。
```
$ sudo crash
crash 6.1.0-1.fc17
Copyright (C) 2002-2012  Red Hat, Inc.
Copyright (C) 2004, 2005, 2006, 2010  IBM Corporation
Copyright (C) 1999-2006  Hewlett-Packard Co
Copyright (C) 2005, 2006, 2011, 2012  Fujitsu Limited
Copyright (C) 2006, 2007  VA Linux Systems Japan K.K.
Copyright (C) 2005, 2011  NEC Corporation
Copyright (C) 1999, 2002, 2007  Silicon Graphics, Inc.
Copyright (C) 1999, 2000, 2001, 2002  Mission Critical Linux, Inc.
This program is free software, covered by the GNU General Public License,
and you are welcome to change it and/or distribute copies of it under
certain conditions.  Enter "help copying" to see the conditions.
This program has absolutely no warranty.  Enter "help warranty" for details.
 
GNU gdb (GDB) 7.3.1
Copyright (C) 2011 Free Software Foundation, Inc.
License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.  Type "show copying"
and "show warranty" for details.
This GDB was configured as "x86_64-unknown-linux-gnu"...

      KERNEL: /usr/lib/debug/lib/modules/3.3.4-5.fc17.x86_64/vmlinux
    DUMPFILE: /dev/crash
        CPUS: 1
        DATE: Mon Dec 21 09:10:58 2015
      UPTIME: 1 days, 01:02:25
LOAD AVERAGE: 0.19, 0.06, 0.06
       TASKS: 130
    NODENAME: localhost.localdomain
     RELEASE: 3.3.4-5.fc17.x86_64
     VERSION: #1 SMP Mon May 7 17:29:34 UTC 2012
     MACHINE: x86_64  (2217 Mhz)
      MEMORY: 511.5 MB
         PID: 3404
     COMMAND: "crash"
        TASK: ffff88001f205c80  [THREAD_INFO: ffff88001d7b6000]
         CPU: 0
       STATE: TASK_RUNNING (ACTIVE)
crash>
```

vmlinux vmcoreを指定する場合には、その２つのファイルが存在するディレクトリに移動して次のコマンドを実行する。
```
$ crash vmlinux vmcore
```

## ヘルプを表示する(重要)
crashコマンドはコマンドやその中のサブコマンドの数が大量にあるのでヘルプの使い方はマスターしておくのが重要となる。  　　

どのようなコマンドがあるのかを調べるために最初はhelpを打ってみると良い。
```
crash> help

*              files          mach           repeat         timer          
alias          foreach        mod            runq           tree           
ascii          fuser          mount          search         union          
bt             gdb            net            set            vm             
btop           help           p              sig            vtop           
dev            ipcs           ps             struct         waitq          
dis            irq            pte            swap           whatis         
eval           kmem           ptob           sym            wr             
exit           list           ptov           sys            q              
extend         log            rd             task           

crash version: 6.1.0-1.fc17   gdb version: 7.3.1
For help on any command above, enter "help <command>".
For help on input options, enter "help input".
For help on output options, enter "help output".
```

setサブコマンドのヘルプを表示するにはhelpのあとにsetを打つ。
コマンドの実行例なども表示してくれます。
```
crash> help set

NAME
  set - set a process context or internal crash variable

SYNOPSIS
  set [[-a] [pid | taskp] | [-c cpu] | -p] | [crash_variable [setting]] | -v

DESCRIPTION
  This command either sets a new context, or gets the current context for
  display.  The context can be set by the use of:

      pid  a process PID.
    taskp  a hexadecimal task_struct pointer.
       -a  sets the pid or task as the active task on its cpu (dumpfiles only).
   -c cpu  sets the context to the active task on a cpu (dumpfiles only).
       -p  sets the context to the panic task, or back to the crash task on
           a live system.
       -v  display the current state of internal crash variables.
(snip)
```


### ログを表示する
```
crash> log
(snip)
[85028.393510] e1000: p2p1 NIC Link is Down
[85032.404587] e1000: p2p1 NIC Link is Up 1000 Mbps Full Duplex, Flow Control: RX
[88108.402490] e1000: p2p1 NIC Link is Down
[88118.438147] e1000: p2p1 NIC Link is Up 1000 Mbps Full Duplex, Flow Control: RX
[88601.052356] e1000: p2p1 NIC Link is Down
[88607.064721] e1000: p2p1 NIC Link is Up 1000 Mbps Full Duplex, Flow Control: RX
[88902.320673] crash memory driver: version 1.0
[89310.236792] crash memory driver: version 1.0
```


### タスク状態などを確認する。
```
crash> bt
PID: 3265   TASK: ffff88001f205c80  CPU: 0   COMMAND: "crash"
(active)

tオプションを付与するとレジストリ情報も確認することができる。
crash> bt -t
PID: 3265   TASK: ffff88001f205c80  CPU: 0   COMMAND: "crash"
              START: __schedule at ffffffff815ea165
  [ffff88000b951f00] vfs_read at ffffffff8117e529
  [ffff88000b951f30] sys_read at ffffffff8117e64a
  [ffff88000b951f80] system_call_fastpath at ffffffff815f38e9
    RIP: 0000003897ae48f0  RSP: 00007fff8ef30570  RFLAGS: 00010246
    RAX: 0000000000000000  RBX: ffffffff815f38e9  RCX: 0000000000000004
    RDX: 0000000000001000  RSI: 0000000000d96020  RDI: 0000000000000004
    RBP: 0000000000001000   R8: 000000000b951000   R9: 0000000000000002
    R10: 000000000082b680  R11: 0000000000000246  R12: 0000000000d96020
    R13: 0000000000000004  R14: 0000000000001000  R15: 0000000000000004
    ORIG_RAX: 0000000000000000  CS: 0033  SS: 002b
```

#### プロセスを表示する。
```
crash> ps
   PID    PPID  CPU       TASK        ST  %MEM     VSZ    RSS  COMM
      0      0   0  ffffffff81a0d020  RU   0.0       0      0  [swapper/0]
      1      0   0  ffff88001fb78000  IN   0.4   41548   1904  systemd
      2      0   0  ffff88001fb79720  IN   0.0       0      0  [kthreadd]
      3      2   0  ffff88001fb7ae40  IN   0.0       0      0  [ksoftirqd/0]
      6      2   0  ffff88001fb98000  IN   0.0       0      0  [migration/0]
      7      2   0  ffff88001fb99720  IN   0.0       0      0  [watchdog/0]
      8      2   0  ffff88001fb9ae40  IN   0.0       0      0  [cpuset]
      9      2   0  ffff88001fb9c560  IN   0.0       0      0  [khelper]
     10      2   0  ffff88001fb9dc80  IN   0.0       0      0  [kdevtmpfs]
     11      2   0  ffff88001fbb0000  IN   0.0       0      0  [netns]
     12      2   0  ffff88001fbb1720  IN   0.0       0      0  [sync_supers]
  (以下略)
```

### 調査するプロセスを切り替える + バックトレースを表示する

psコマンドで以下のように表示されるPID=2443のsendmailプロセスを調査する。
```
   2443      1   0  ffff88001d6f2e40  IN   0.4   95552   2132  sendmail
```

この場合にはsetコマンドで対象のPIDを指定する。
```
crash> set 2443
    PID: 2443
COMMAND: "sendmail"
   TASK: ffff88001d6f2e40  [THREAD_INFO: ffff88001f04e000]
    CPU: 0
  STATE: TASK_INTERRUPTIBLE 
```


fオプションでスタックフレームです。スタックフレームはメモリ高位から低位に伸びていきます。  
#Nで始まるNが大きい値から順番に関数がコールされていることになります。
```
crash> bt -f
PID: 2443   TASK: ffff88001d6f2e40  CPU: 0   COMMAND: "sendmail"
 #0 [ffff88001f04f888] __schedule at ffffffff815ea165
    ffff88001f04f890: 0000000000000086 ffff88001d6f2e40 
    ffff88001f04f8a0: ffff88001f04ffd8 ffff88001f04ffd8 
    ffff88001f04f8b0: ffff88001f04ffd8 ffffffff81a0d020 
    ffff88001f04f8c0: ffff88001d6f2e40 ffff88001f04fa08 
    ffff88001f04f8d0: ffff88001f04fac0 00000000004c4b3c 
    ffff88001f04f8e0: 0000000000000000 0000000000000020 
    ffff88001f04f8f0: 0000000000000000 ffff88001f04f908 
    ffff88001f04f900: ffffffff815ea8df 
 #1 [ffff88001f04f900] schedule at ffffffff815ea8df
    ffff88001f04f908: ffff88001f04f9a8 ffffffff815e9a6c 
 #2 [ffff88001f04f910] schedule_hrtimeout_range_clock at ffffffff815e9a6c
    ffff88001f04f918: ffff88001f173eb8 ffff88001fc0e7a0 
    ffff88001f04f928: ffff88001ec49a68 0000518ef6cc88e7 
    ffff88001f04f938: 0000518ef6803dab ffffffff8107c5f0 
    ffff88001f04f948: ffff88001fc0e440 0000000000000001 
    ffff88001f04f958: 000000000000098b ffffffff8107d104 
    ffff88001f04f968: 6c69616d646e6573 0000000000000000 
    ffff88001f04f978: ffff88001d6f2e40 000000002414c629 
    ffff88001f04f988: ffff88001d6f2e40 ffff88001f04fac8 
    ffff88001f04f998: 0000000000000005 0000000000000005 
    ffff88001f04f9a8: ffff88001f04f9b8 ffffffff815e9ac3 
 (snip)
```

### 特定のCPUが実行しているタスクに切り替える
cオプションのあとにCPU番号を入れるとそのCPUが実行するプロセスに切り替えます。
```
crash> set -c 0
    PID: 1696
COMMAND: "insmod"
   TASK: c74de000
    CPU: 0
  STATE: TASK_RUNNING (PANIC)
```

### カーネルパニックとなったプロセスに切り替える
panicオプションを付与するとカーネルパニックとなったプロセスに切り替えます。
```
crash> set -p
    PID: 1696
COMMAND: "insmod"
   TASK: c74de000
    CPU: 0
  STATE: TASK_RUNNING (PANIC)
```

### システム情報を表示する
```
crash> sys
      KERNEL: /usr/lib/debug/lib/modules/3.3.4-5.fc17.x86_64/vmlinux
    DUMPFILE: /dev/crash
        CPUS: 1
        DATE: Mon Dec 21 08:54:13 2015
      UPTIME: 1 days, 00:45:40
LOAD AVERAGE: 0.07, 0.08, 0.05
       TASKS: 131
    NODENAME: localhost.localdomain
     RELEASE: 3.3.4-5.fc17.x86_64
     VERSION: #1 SMP Mon May 7 17:29:34 UTC 2012
     MACHINE: x86_64  (2217 Mhz)
      MEMORY: 511.5 MB
```

システムコールテーブルを表示する
```
crash> sys -c
NUM  SYSTEM CALL                FILE AND LINE NUMBER
  0  sys_read                   ../fs/read_write.c: 461
  1  sys_write                  ../fs/read_write.c: 479
  2  sys_open                   ../fs/open.c: 998
  3  sys_close                  ../fs/open.c: 1069
  4  sys_newstat                ../fs/stat.c: 245
  5  sys_newfstat               ../fs/stat.c: 282
  6  sys_newlstat               ../fs/stat.c: 256
  7  sys_poll                   ../fs/select.c: 912
(snip)
310  sys_process_vm_readv       ../mm/process_vm_access.c: 401
311  sys_process_vm_writev      ../mm/process_vm_access.c: 409
```

システムコールテーブルから特定の文言にマッチするものを表示する。以下はreadでマッチしたものを表示する。
```
crash> sys -c read
NUM  SYSTEM CALL                FILE AND LINE NUMBER
  0  sys_read                   ../fs/read_write.c: 461
 17  sys_pread64                ../fs/read_write.c: 497
 19  sys_readv                  ../fs/read_write.c: 790
 89  sys_readlink               ../fs/stat.c: 322
187  sys_readahead              ../mm/filemap.c: 1501
267  sys_readlinkat             ../fs/stat.c: 294
295  sys_preadv                 ../fs/read_write.c: 838
310  sys_process_vm_readv       ../mm/process_vm_access.c: 401
```

システム設定情報を表示する(if CONFIG_IKCONFIG)
```
crash> sys config
#
# Automatically generated make config: don't edit
# Linux kernel version: 2.6.16
# Mon Apr 10 07:58:06 2006
#
CONFIG_X86_64=y
CONFIG_64BIT=y
CONFIG_X86=y
CONFIG_SEMAPHORE_SLEEPERS=y
CONFIG_MMU=y
CONFIG_RWSEM_GENERIC_SPINLOCK=y
CONFIG_GENERIC_CALIBRATE_DELAY=y
```


### モジュールを表示する
```
crash> mod -S
     MODULE       NAME                 SIZE  OBJECT FILE
ffffffffa0003060  uinput              17673  /lib/modules/3.3.4-5.fc17.x86_64/kernel/drivers/input/misc/uinput.ko 
ffffffffa000c120  binfmt_misc         17463  /lib/modules/3.3.4-5.fc17.x86_64/kernel/fs/binfmt_misc.ko 
ffffffffa00193e0  parport             40375  /lib/modules/3.3.4-5.fc17.x86_64/kernel/drivers/parport/parport.ko 
ffffffffa001f060  soundcore           14491  /lib/modules/3.3.4-5.fc17.x86_64/kernel/sound/soundcore.ko 
ffffffffa00272e0  parport_pc          28035  /lib/modules/3.3.4-5.fc17.x86_64/kernel/drivers/parport/parport_pc.ko 
ffffffffa002cce0  i2c_piix4           13694  /lib/modules/3.3.4-5.fc17.x86_64/kernel/drivers/i2c/busses/i2c-piix4.ko 
ffffffffa004d680  e1000              145411  /lib/modules/3.3.4-5.fc17.x86_64/kernel/drivers/net/ethernet/intel/e1000/e1000.ko 
ffffffffa005a240  ip6_tables          27073  /lib/modules/3.3.4-5.fc17.x86_64/kernel/net/ipv6/netfilter/ip6_tables.ko 
ffffffffa005f060  nf_defrag_ipv4      12673  /lib/modules/3.3.4-5.fc17.x86_64/kernel/net/ipv4/netfilter/nf_defrag_ipv4.ko 
ffffffffa006f320  snd                 78862  /lib/modules/3.3.4-5.fc17.x86_64/kernel/sound/core/snd.ko 
ffffffffa007a040  snd_page_alloc      18101  /lib/modules/3.3.4-5.fc17.x86_64/kernel/sound/core/snd-page-alloc.ko 
ffffffffa0084080  snd_timer           28690  /lib/modules/3.3.4-5.fc17.x86_64/kernel/sound/core/snd-timer.ko 
ffffffffa008a080  ac97_bus            12718  /lib/modules/3.3.4-5.fc17.x86_64/kernel/sound/ac97_bus.ko 
ffffffffa0094600  i2c_core            38028  /lib/modules/3.3.4-5.fc17.x86_64/kernel/drivers/i2c/i2c-core.ko 
ffffffffa00ae540  snd_pcm             97129  /lib/modules/3.3.4-5.fc17.x86_64/kernel/sound/core/snd-pcm.ko 
ffffffffa00b8200  ppdev               17635  /lib/modules/3.3.4-5.fc17.x86_64/kernel/drivers/char/ppdev.ko 
ffffffffa00be3a0  microcode           19252  /lib/modules/3.3.4-5.fc17.x86_64/kernel/arch/x86/kernel/microcode.ko 
ffffffffa00c3060  ip6table_filter     12815  /lib/modules/3.3.4-5.fc17.x86_64/kernel/net/ipv6/netfilter/ip6table_filter.ko 
ffffffffa00cb460  nf_conntrack_ipv4   14622  /lib/modules/3.3.4-5.fc17.x86_64/kernel/net/ipv4/netfilter/nf_conntrack_ipv4.ko 
ffffffffa00e9720  snd_ac97_codec     133281  /lib/modules/3.3.4-5.fc17.x86_64/kernel/sound/pci/ac97/snd-ac97-codec.ko 
ffffffffa00f3080  xt_state            12578  /lib/modules/3.3.4-5.fc17.x86_64/kernel/net/netfilter/xt_state.ko 
ffffffffa0101780  snd_intel8x0        38143  /lib/modules/3.3.4-5.fc17.x86_64/kernel/sound/pci/snd-intel8x0.ko 
ffffffffa01138a0  nf_conntrack        82339  /lib/modules/3.3.4-5.fc17.x86_64/kernel/net/netfilter/nf_conntrack.ko 
ffffffffa011fa60  nf_nat              25179  /lib/modules/3.3.4-5.fc17.x86_64/kernel/net/ipv4/netfilter/nf_nat.ko 
ffffffffa0125280  iptable_nat         13383  /lib/modules/3.3.4-5.fc17.x86_64/kernel/net/ipv4/netfilter/iptable_nat.ko 
ffffffffa012a120  ipt_MASQUERADE      12880  /lib/modules/3.3.4-5.fc17.x86_64/kernel/net/ipv4/netfilter/ipt_MASQUERADE.ko 
ffffffffa0133440  nf_defrag_ipv6      18095  /lib/modules/3.3.4-5.fc17.x86_64/kernel/net/ipv6/netfilter/nf_defrag_ipv6.ko 
ffffffffa013c3c0  nf_conntrack_ipv6   14297  /lib/modules/3.3.4-5.fc17.x86_64/kernel/net/ipv6/netfilter/nf_conntrack_ipv6.ko 
ffffffffa01451a0  ip6t_REJECT         12939  /lib/modules/3.3.4-5.fc17.x86_64/kernel/net/ipv6/netfilter/ip6t_REJECT.ko 
ffffffffa014b380  rfkill              21384  /lib/modules/3.3.4-5.fc17.x86_64/kernel/net/rfkill/rfkill.ko 
ffffffffa0151140  crash               12576  /lib/modules/3.3.4-5.fc17.x86_64/kernel/drivers/char/crash.ko 
ffffffffa0187dc0  bluetooth          273667  /lib/modules/3.3.4-5.fc17.x86_64/kernel/net/bluetooth/bluetooth.ko 
ffffffffa01ad540  bnep                19584  /lib/modules/3.3.4-5.fc17.x86_64/kernel/net/bluetooth/bnep/bnep.ko 
```

### モジュールをアンロードする
lsmodなどで表示されるモジュール名を指定してアンロードできます。アンロードはdオプションを使います。
```
crash> mod -d e1000
```

### 構造体の定義を確認する
```
crash> struct task_struct
struct task_struct {
    volatile long int state;
    void *stack;
    atomic_t usage;
    unsigned int flags;
    unsigned int ptrace;
    struct llist_node wake_entry;
    int on_cpu;
    int on_rq;
    int prio;
    int static_prio;
    int normal_prio;
    unsigned int rt_priority;
    const struct sched_class *sched_class;
    struct sched_entity se;
    struct sched_rt_entity rt;
    struct hlist_head preempt_notifiers;
    unsigned char fpu_counter;
    unsigned int btrace_seq;
    unsigned int policy;
	(snip)
```

なお、どのように割り当てされるのかはoオプションで確認することができます。
```
crash> struct -o task_struct
struct task_struct {
     [0] volatile long int state;
     [8] void *stack;
    [16] atomic_t usage;
    [20] unsigned int flags;
    [24] unsigned int ptrace;
    [32] struct llist_node wake_entry;
    [40] int on_cpu;
    [44] int on_rq;
    [48] int prio;
    [52] int static_prio;
    [56] int normal_prio;
    [60] unsigned int rt_priority;
    [64] const struct sched_class *sched_class;
...
```

### IRQ情報を確認する。
```
crash> irq
 IRQ   IRQ_DESC/_DATA      IRQACTION      NAME
  0   ffff88001f806200  ffffffff81a11e00  "timer"
  1   ffff88001f806300  ffff88001a337180  "i8042"
  2   ffff88001f806400      (unused)      
  3   ffff88001f806500      (unused)      
  4   ffff88001f806600      (unused)      
  5   ffff88001f806700      (unused)      
  6   ffff88001f806800      (unused)      
  7   ffff88001f806900      (unused)      
  8   ffff88001f806a00  ffff88001a337380  "rtc0"
  9   ffff88001f806b00  ffff88001fb63700  "acpi"
 10   ffff88001f806c00      (unused)      
 11   ffff88001f806d00      (unused)      
 12   ffff88001f806e00  ffff88001a337100  "i8042"
 13   ffff88001f806f00      (unused)      
 14   ffff88001f807000  ffff88001a26a880  "ata_piix"
 15   ffff88001f807100  ffff88001a26a900  "ata_piix"
 16   ffff88001f034a00  ffff88001a4f2880  "p7p1"
 17       (unused)          (unused)      
 18       (unused)          (unused)      
 19   ffff88001f324e00  ffff88001c466600  "p2p1"
 20       (unused)          (unused)      
 21   ffff88001b25d600  ffff88001a26a700  "ahci"
                        ffff88001b01e980  "snd_intel8x0"
 22   ffff88001d4eac00  ffff88001d541e00  "ohci_hcd:usb1"
(snip)
```


###デバイスに関する情報や構造体を表示する。
CHRDEVがキャラクタデバイス、BLKDEVがブロックデバイスを表す
```
crash> dev
CHRDEV    NAME                 CDEV        OPERATIONS      
   1      mem            ffff88001d4c0380  memory_fops
   4      /dev/vc/0      ffffffff81d2afe0  console_fops
   4      tty            ffff88001d4f7208  tty_fops
   4      ttyS           ffff88001a273c08  tty_fops
   5      /dev/tty       ffffffff81d299c0  tty_fops
   5      /dev/console   ffffffff81d29a40  console_fops
   5      /dev/ptmx      ffffffff81d29ce0  ptmx_fops
   7      vcs            ffff88001d4c0480  vcs_fops
  10      misc           ffff88001fb63a00  misc_fops
  13      input          ffff88001fb63c80  input_fops
  14      sound          ffff88001f0a4a80  soundcore_fops
  21      sg             ffff88001a337c00  sg_fops
  29      fb             ffff88001fb63600  fb_fops
  99      ppdev          ffff88001b01eb00  pp_fops
 116      alsa           ffff88001b01e400  snd_fops
 128      ptm            ffff88001a273808  tty_fops
 136      pts            ffff88001a273a08  tty_fops
 162      raw            ffffffff81d2e840  raw_fops
 180      usb            ffff88001fb63b80  usb_fops
 188      ttyUSB         ffff88001a2ddc08  tty_fops
 189      usb_device     ffffffff81d82da0  usbdev_file_operations
 202      cpu/msr        ffff88001d541780  msr_fops
 203      cpu/cpuid      ffff88001d541880  cpuid_fops
 251      hidraw         ffffffff81d852e0  hidraw_ops
 252      usbmon         ffffffff81d82ec0  mon_fops_binary
 253      bsg            ffffffff81d24900  bsg_fops
 254      rtc            ffff88001a34f2d0  rtc_dev_fops

BLKDEV    NAME                GENDISK      OPERATIONS      
 259      blkext              (none)     
   7      loop           ffff88001a2f1800  lo_fops
   8      sd             ffff88001a3b5000  sd_fops
   9      md                  (none)     
  11      sr             ffff88001a3d1000  sr_bdops
  65      sd                  (none)     
  66      sd                  (none)     
  67      sd                  (none)     
  68      sd                  (none)     
  69      sd                  (none)     
(snip)
```

たとえば、キャラクタデバイス21番のsg_fopsの定義内容を見たい場合には以下のようにすればよい。  
どの関数が設定されているのかを見ることができる。
```
crash> sg_fops
sg_fops = $9 = {
  owner = 0x0, 
  llseek = 0xffffffff8117d8d0 <no_llseek>, 
  read = 0xffffffff813d2fb0 <sg_read>, 
  write = 0xffffffff813d4f00 <sg_write>, 
  aio_read = 0, 
  aio_write = 0, 
  readdir = 0, 
  poll = 0xffffffff813d2080 <sg_poll>, 
  unlocked_ioctl = 0xffffffff813d58a0 <sg_unlocked_ioctl>, 
  compat_ioctl = 0xffffffff813d1af0 <sg_compat_ioctl>, 
  mmap = 0xffffffff813d1ba0 <sg_mmap>, 
  open = 0xffffffff813d5350 <sg_open>, 
  flush = 0, 
  release = 0xffffffff813d3880 <sg_release>, 
  fsync = 0, 
  aio_fsync = 0, 
  fasync = 0xffffffff813d1db0 <sg_fasync>, 
  lock = 0, 
  sendpage = 0, 
  get_unmapped_area = 0, 
  check_flags = 0, 
  flock = 0, 
  splice_write = 0, 
  splice_read = 0, 
  setlease = 0, 
  fallocate = 0
}
```

### mount情報を表示する
```
crash> mount
    VFSMOUNT         SUPERBLK     TYPE   DEVNAME                DIRNAME
ffff88001fadc100 ffff88001f80ac00 rootfs rootfs                 /         
ffff88001b23c300 ffff88001f80b400 proc   proc                   /proc     
ffff88001b003000 ffff88001a3ec400 sysfs  sysfs                  /sys      
ffff88001b003d00 ffff88001fbaa000 devtmpfs devtmpfs               /dev      
ffff88001b129d00 ffff88001d601c00 devpts devpts                 /dev/pts  
ffff88001b129700 ffff88001a3ec800 tmpfs  tmpfs                  /dev/shm  
ffff88001b216200 ffff88001a3ecc00 tmpfs  tmpfs                  /run      
ffff88001f0a5f00 ffff88001f30b400 ext4   /dev/mapper/vg-lv_root /         
ffff88001f09e900 ffff88001f30a000 tmpfs  tmpfs                  /sys/fs/cgroup
ffff88001f09e800 ffff88001f30a800 cgroup cgroup                 /sys/fs/cgroup/systemd
ffff88001f09e300 ffff88001f30a400 cgroup cgroup                 /sys/fs/cgroup/cpuset
ffff88001f09ec00 ffff88001a257400 cgroup cgroup                 /sys/fs/cgroup/cpu,cpuacct
ffff88001f09e500 ffff88001f0ac000 cgroup cgroup                 /sys/fs/cgroup/memory
ffff88001f09ef00 ffff88001f0ac800 cgroup cgroup                 /sys/fs/cgroup/devices
ffff88001f09ee00 ffff88001f0acc00 cgroup cgroup                 /sys/fs/cgroup/freezer
ffff88001f09e200 ffff88001f0ad000 cgroup cgroup                 /sys/fs/cgroup/net_cls
ffff88001f09e100 ffff88001f0ad400 cgroup cgroup                 /sys/fs/cgroup/blkio
ffff88001f09ed00 ffff88001f0ad800 cgroup cgroup                 /sys/fs/cgroup/perf_event
ffff88001f134800 ffff88001f24a000 autofs systemd-1              /proc/sys/fs/binfmt_misc
ffff88001f182100 ffff88001bac6000 hugetlbfs hugetlbfs              /dev/hugepages
ffff88001f03b600 ffff88001bac6400 securityfs securityfs             /sys/kernel/security
ffff88001f324300 ffff88001fbab400 debugfs debugfs                /sys/kernel/debug
ffff88001f182f00 ffff88001bac6800 configfs configfs               /sys/kernel/config
ffff88001b13aa00 ffff88001a257000 mqueue mqueue                 /dev/mqueue
ffff88001f324500 ffff88001d670400 tmpfs  tmpfs                  /media    
ffff88001b129900 ffff88001bac7c00 binfmt_misc binfmt_misc            /proc/sys/fs/binfmt_misc/
ffff88001f08bc00 ffff88001b77a000 ext4   /dev/sda1              /boot     
```


### ネットワーク情報を表示する(net)
ネットワークデバイスの情報を表示する
```
crash> net
   NET_DEVICE     NAME   IP ADDRESS(ES)
ffff88001d413000  lo     127.0.0.1
ffff88001d6b6000  p2p1   10.0.2.15
ffff88001b7ce000  p7p1   192.168.56.1
```

数値からIPアドレスに変換する
```
crash> net -n 1041236234
10.1.16.62
```

ARPキャッシュテーブルを表示する
```
crash> net -a
NEIGHBOUR        IP ADDRESS      HW TYPE    HW ADDRESS         DEVICE  STATE
ffff88003ac5cc00 10.0.2.2        ETHER      52:54:00:12:35:02  p2p1    REACHABLE
```

プロセスで利用するソケット情報を表示する。ここでの例はpsコマンドでdhclientというプロセスのPIDを指定しています。
```
crash> net -s 2126
PID: 2126   TASK: ffff880036e58000  CPU: 0   COMMAND: "dhclient"
FD      SOCKET            SOCK       FAMILY:TYPE SOURCE-PORT DESTINATION-PORT
 1 ffff88003bba9b80 ffff88003a16a080 UNIX:STREAM 
 3 ffff88003b9ef680 ffff88003b0d7400 UNIX:DGRAM  
 5 ffff88003b9ee500 ffff880036d6e800 PACKET:RAW 
 6 ffff88003b9eea00 ffff88003a31ae00 INET:DGRAM   0.0.0.0-68 0.0.0.0-0
20 ffff88003b9ef180 ffff88003a31aa80 INET:DGRAM   0.0.0.0-3000 0.0.0.0-0
21 ffff88003b9eec80 ffff88003a4b4000 INET6:DGRAM  0:0:0:0:0:0:0:0-38429   0:0:0:0:0:0:0:0-0 
```

特定のプロセスのソケット関連の構造体を全て表示しています(task_structなどは表示されませんでした)。  
そのままだと出力される情報量が多いので、以下では最初の３行(PIDという文字列から3行)とstructで始まるものを抽出しています。
```
crash> net -S 1094 | egrep -e "^struct " -e PID -A 3
PID: 1094   TASK: ffff88003b1fae40  CPU: 0   COMMAND: "sshd"
FD       SOCKET             SOCK      
 2  ffff88003b8cac80  ffff88003d469a00

struct socket {
  state = SS_CONNECTED, 
  type = 1, 
  flags = 0, 
--
struct inet_sock {
  sk = {
    __sk_common = {
      skc_daddr = 0, 
--
struct socket {
  state = SS_CONNECTED, 
  type = 1, 
  flags = 0, 
--
struct inet_sock {
  sk = {
    __sk_common = {
      skc_daddr = 33685514, 
--
struct socket {
  state = SS_UNCONNECTED, 
  type = 2, 
  flags = 0, 
--
struct inet_sock {
  sk = {
    __sk_common = {
      skc_daddr = 0, 
--
struct socket {
  state = SS_CONNECTED, 
  type = 1, 
  flags = 0, 
--
struct inet_sock {
  sk = {
    __sk_common = {
      skc_daddr = 0, 
```

### プロセスが握っているファイルを確認する
プロセスをセットします
```
crash> set 3404
    PID: 3404
COMMAND: "crash"
   TASK: ffff88001f205c80  [THREAD_INFO: ffff88001d7b6000]
    CPU: 0
  STATE: TASK_RUNNING (ACTIVE)
```

filesを引数なしで実行すると、PIDには先ほど指定したプロセス番号が表示され、このプロセスが握っているファイルが表示されます。
```
crash> files
PID: 3404   TASK: ffff88001f205c80  CPU: 0   COMMAND: "crash"
ROOT: /    CWD: /home/tsuyoshi
 FD       FILE            DENTRY           INODE       TYPE PATH
  0 ffff88001a093600 ffff8800172299c0 ffff880018ba3180 CHR  /dev/pts/2
  1 ffff88001a093600 ffff8800172299c0 ffff880018ba3180 CHR  /dev/pts/2
  2 ffff88001a093600 ffff8800172299c0 ffff880018ba3180 CHR  /dev/pts/2
  3 ffff88001f054a00 ffff88001db0be40 ffff88001fba6a50 CHR  /dev/null
  4 ffff880018a25f00 ffff880017197000 ffff880001e10f50 CHR  /dev/crash
  5 ffff88001a1a2500 ffff880017035c00 ffff88001e782b00 REG  /usr/lib/debug/lib/modules/3.3.4-5.fc17.x86_64/vmlinux
  6 ffff88001a1a1d00 ffff880017197900 ffff880004f0a690 FIFO 
  7 ffff88001a1a1000 ffff880017197900 ffff880004f0a690 FIFO 
  8 ffff88001c47e700 ffff880017197a80 ffff88001e7820b0 REG  /tmp/tmpfX85qAK
 10 ffff88001d752700 ffff88001bcac300 ffff880004f0a8c0 FIFO 
```

### filesで絞り込みを行いたい場合
```
# TCPソケットだけを表示
crash> foreach files -R TCP

# UDPソケットだけを表示
crash> foreach files -R UDP

# Netlinkソケットだけを表示
crash> foreach files -R NETLINK

# Unixdomainsocketだけを表示
crash> foreach files -R UNIX

# ptsを指定して表示
crash> foreach files -R pts/1
```

たとえば、該当する場合には次のように表示されます。
```
crash> foreach files -R /var/log
PID: 536    TASK: ffff88003a310000  CPU: 0   COMMAND: "auditd"
ROOT: /    CWD: / 
 FD       FILE            DENTRY           INODE       TYPE PATH
  4 ffff880036971100 ffff88003bb51cc0 ffff88003bbca790 REG  /var/log/audit/audit.log

PID: 542    TASK: ffff88003d2dae40  CPU: 0   COMMAND: "abrt-watch-log"
ROOT: /    CWD: / 
 FD       FILE            DENTRY           INODE       TYPE PATH
  4 ffff88003a40f700 ffff88003dfe50c0 ffff8800370000b0 REG  /var/log/messages
```

### メモリ内部を覗く
```
crash> kmem -v
    VM_STRUCT                 ADDRESS RANGE               SIZE
ffff88001f80d080  ffffc90000000000 - ffffc90000081000  528384
ffff88001f80d0c0  ffffc90000081000 - ffffc900000c2000  266240
ffff88001f80d200  ffffc900000c2000 - ffffc900000c5000   12288
ffff88001a320400  ffffc900000c6000 - ffffc900000c8000    8192
ffff88001f80d500  ffffc900000c8000 - ffffc900000cc000   16384
ffff88001d4e7e00  ffffc900000cc000 - ffffc900000d5000   36864
ffff88001d54d200  ffffc900000d5000 - ffffc90000116000  266240
  (snip)
```


構造体が利用している箇所を取得する
```
crash> kmem -S task_struct
CACHE            NAME                 OBJSIZE  ALLOCATED     TOTAL  SLABS  SSIZE
ffff88003e007500 task_struct             5912        130       150     30    32k
CPU 0 SLAB:
  SLAB              MEMORY            NODE  TOTAL  ALLOCATED  FREE
  ffffea0000ec5c00  ffff88003b170000     0      5          1     4
  FREE / [ALLOCATED]
   ffff88003b170000  (cpu 0 cache)
   ffff88003b171720  (cpu 0 cache)
   ffff88003b172e40  (cpu 0 cache)
  [ffff88003b174560]
   ffff88003b175c80  (cpu 0 cache)
KMEM_CACHE_NODE   NODE  SLABS  PARTIAL  PER-CPU
ffff88003e001840     0     30       12        1
NODE 0 PARTIAL:
  SLAB              MEMORY            NODE  TOTAL  ALLOCATED  FREE
  ffffea0000dae800  ffff880036ba0000     0      4          4     0
  ffffea0000d92200  ffff880036488000     0      4          4     0
  ffffea0000db8600  ffff880036e18000     0      3          3     0
  ffffea0000f45600  ffff88003d158000     0      4          4     0
  ffffea0000f02e00  ffff88003c0b8000     0      3          3     0
  ffffea0000f1c600  ffff88003c718000     0      3          3     0
  ffffea0000f67c00  ffff88003d9f0000     0      4          4     0
  ffffea0000f6c800  ffff88003db20000     0      3          3     0
  ffffea0000db9600  ffff880036e58000     0      3          3     0
  ffffea0000e8ea00  ffff88003a3a8000     0      3          3     0
  ffffea0000e89000  ffff88003a240000     0      4          4     0
  ffffea0000dbf200  ffff880036fc8000     0      2          2     0
NODE 0 FULL:
  (not tracked)
```

### メモリ統計情報を表示する
```
crash> kmem -V
  VM_STAT:
          NR_FREE_PAGES: 1635
       NR_INACTIVE_ANON: 32919
         NR_ACTIVE_ANON: 30881
       NR_INACTIVE_FILE: 22208
         NR_ACTIVE_FILE: 25865
         NR_UNEVICTABLE: 0
               NR_MLOCK: 0
          NR_ANON_PAGES: 61800
         NR_FILE_MAPPED: 26597
          NR_FILE_PAGES: 50508
          NR_FILE_DIRTY: 0
           NR_WRITEBACK: 0
    NR_SLAB_RECLAIMABLE: 3769
  NR_SLAB_UNRECLAIMABLE: 3135
           NR_PAGETABLE: 3209
        NR_KERNEL_STACK: 128
        NR_UNSTABLE_NFS: 0
  (snip)
```

### メモリ詳細な統計情報を表示する
```
crash> kmem -s
  CACHE            NAME                 OBJSIZE  ALLOCATED     TOTAL  SLABS  SSIZE
ffff88001b129600 nf_conntrack_expect      240          0         0      0     4k
ffff88001b129a00 nf_conntrack_ffffffff81d87840 304    65        65      5     4k
ffff88001f183000 ext4_groupinfo_1k        128         64        64      2     4k
ffff88001b23c900 ip6_dst_cache            320         36        36      3     4k
ffff88001b23ca00 UDPLITEv6               1032          0         0      0    16k
ffff88001b23cb00 UDPv6                   1032         15        15      1    16k
ffff88001b23cc00 tw_sock_TCPv6            280          0         0      0     4k
ffff88001b23cd00 TCPv6                   1896          8         8      1    16k
ffff88001b23ce00 dm_raid1_read_record    1064          0         0      0    16k
ffff88001b23cf00 kcopyd_job              3240          0         0      0    32k
ffff88001b25d000 dm_uevent               2608          0         0      0    32k
ffff88001b25d100 dm_rq_target_io          408          0         0      0     4k
ffff88001b25d900 cfq_io_cq                104         78        78      2     4k
ffff88001b25da00 cfq_queue                232         68        68      4     4k
```

### 特定のプロセスに関するVM情報を全て表示する。
利用しているファイルやそのアドレス(VMA)を表示しています。
```
crash> vm
PID: 1176   TASK: ffff88003648c560  CPU: 0   COMMAND: "crash"
       MM               PGD          RSS    TOTAL_VM
	   ffff880036f60e00  ffff88003649d000  282908k  333752k 
	         VMA           START       END     FLAGS FILE
			 ffff880036e6f0b0     400000     a1c000 8001875 /usr/bin/crash
			 ffff880036e6f160     c1c000     c3e000 8101873 /usr/bin/crash
			 ffff880036e6f210     c3e000     dd3000 100073 
			 ffff880036e6f2c0     e3d000     e5c000 8101873 /usr/bin/crash
			 ffff88003b141580    28bb000    bbe3000 100073 
			 ffff880036e6fa50 3606200000 3606225000 8000075 /usr/lib64/libtinfo.so.5.9
			 ffff880036e6f9a0 3606225000 3606424000 8000070 /usr/lib64/libtinfo.so.5.9
			 ffff880036e6fb00 3606424000 3606428000 8100071 /usr/lib64/libtinfo.so.5.9
			 ffff88003b1418f0 3606428000 3606429000 8100073 /usr/lib64/libtinfo.so.5.9
(snip)
```


# 特定の番地から指定された分だけメモリを覗き見る
次のe1000のモジュールのメモリを覗いてみることにする。
```
crash> mod -S
     MODULE       NAME                 SIZE  OBJECT FILE
ffffffffa0003180  video               18980  /lib/modules/3.3.4-5.fc17.x86_64/kernel/drivers/acpi/video.ko 
ffffffffa0008ce0  i2c_piix4           13694  /lib/modules/3.3.4-5.fc17.x86_64/kernel/drivers/i2c/busses/i2c-piix4.ko 
ffffffffa000e060  uinput              17673  /lib/modules/3.3.4-5.fc17.x86_64/kernel/drivers/input/misc/uinput.ko 
ffffffffa0017120  binfmt_misc         17463  /lib/modules/3.3.4-5.fc17.x86_64/kernel/fs/binfmt_misc.ko 
ffffffffa001c060  soundcore           14491  /lib/modules/3.3.4-5.fc17.x86_64/kernel/sound/soundcore.ko 
ffffffffa0028600  i2c_core            38028  /lib/modules/3.3.4-5.fc17.x86_64/kernel/drivers/i2c/i2c-core.ko 
ffffffffa004a680  e1000              145411  /lib/modules/3.3.4-5.fc17.x86_64/kernel/drivers/net/ethernet/intel/e1000/e1000.ko 
```

上記でe1000はffffffffa004a680なのでrd(read)コマンドを使って
```
crash> rd ffffffffa004a680 10
ffffffffa004a680:  0000000000000000 ffffffffa0008ce8   ................
ffffffffa004a690:  ffffffffa0069328 0000003030303165   (.......e1000...
ffffffffa004a6a0:  0000000000000000 0000000000000000   ................
ffffffffa004a6b0:  0000000000000000 0000000000000000   ................
ffffffffa004a6c0:  0000000000000000 0000000000000000   ................
```

### シグナルを確認する
```
crash> set 2235     // <PID>を指定すること
crash> sig
PID: 2235   TASK: ffff88001baf0000  CPU: 0   COMMAND: "bash"
SIGNAL_STRUCT: ffff88001f0fccc0  NR_THREADS: 1
 SIG    SIGACTION        HANDLER       MASK       FLAGS           
 [1] ffff88001c921088     456710 0000000043807efb 4000000 (SA_RESTORER)
 [2] ffff88001c9210a8     49af20 0000000000000000 4000000 (SA_RESTORER)
 [3] ffff88001c9210c8    SIG_IGN 0000000000000000 4000000 (SA_RESTORER)
 [4] ffff88001c9210e8     456710 0000000043807efb 4000000 (SA_RESTORER)
 [5] ffff88001c921108     456710 0000000043807efb 4000000 (SA_RESTORER)
 [6] ffff88001c921128     456710 0000000043807efb 4000000 (SA_RESTORER)
 [7] ffff88001c921148     456710 0000000043807efb 4000000 (SA_RESTORER)
 [8] ffff88001c921168     456710 0000000043807efb 4000000 (SA_RESTORER)
 [9] ffff88001c921188    SIG_DFL 0000000000000000 0 
```

### task_struct構造体を表示する
```
crash> set 2235
crash> task
PID: 2235   TASK: ffff88001baf0000  CPU: 0   COMMAND: "bash"
struct task_struct {
  state = 1, 
  stack = 0xffff88001a8fe000, 
  usage = {
    counter = 2
  }, 
  flags = 4202496, 
  ptrace = 0, 
  wake_entry = {
    next = 0x0
  }, 
  on_cpu = 0, 
  on_rq = 0, 
  prio = 120, 
  static_prio = 120, 
  normal_prio = 120, 
  rt_priority = 0, 
  sched_class = 0xffffffff81607f00, 
  se = {
    load = {
      weight = 1024, 
      inv_weight = 4194304
    }, 
    run_node = {
      rb_parent_color = 1, 
      rb_right = 0x0, 
      rb_left = 0x0
    }, 
    group_node = {
      next = 0xffff88001baf0070, 
      prev = 0xffff88001baf0070
    }, 

    (snip)
```


### すべてのPIDに対しての情報を表示したい。
foreachを使うと良い。
```
crash>foreach bt
crash>foreach vm
crash>foreach task
crash>foreach files
crash>foreach net
crash>foreach set
crash>foreach sig
crash>foreach vtop
crash>foreach -R files /opt
```

### 出力をファイルに残したい
リダイレクトを使うことが可能です。
```
crash> foreach files > /tmp/testtest
```

### 特定プロセスのtask_struct構造体の値を見てみる
```
crash> ps
   PID    PPID  CPU       TASK        ST  %MEM     VSZ    RSS  COMM
      0      0   0  ffffffff81a0d020  RU   0.0       0      0  [swapper/0]
      1      0   0  ffff88001fb78000  IN   0.3   41548   1820  systemd
      2      0   0  ffff88001fb79720  IN   0.0       0      0  [kthreadd]
      3      2   0  ffff88001fb7ae40  IN   0.0       0      0  [ksoftirqd/0]
      6      2   0  ffff88001fb98000  IN   0.0       0      0  [migration/0]
      7      2   0  ffff88001fb99720  IN   0.0       0      0  [watchdog/0]
      8      2   0  ffff88001fb9ae40  IN   0.0       0      0  [cpuset]
      9      2   0  ffff88001fb9c560  IN   0.0       0      0  [khelper]
     10      2   0  ffff88001fb9dc80  IN   0.0       0      0  [kdevtmpfs]
     11      2   0  ffff88001fbb0000  IN   0.0       0      0  [netns]
     12      2   0  ffff88001fbb1720  IN   0.0       0      0  [sync_supers]
     13      2   0  ffff88001fbb2e40  IN   0.0       0      0  [bdi-default]
     14      2   0  ffff88001fbb4560  IN   0.0       0      0  [kintegrityd]
     15      2   0  ffff88001fbb5c80  IN   0.0       0      0  [kblockd]
     16      2   0  ffff88001d448000  IN   0.0       0      0  [ata_sff]
     17      2   0  ffff88001d449720  IN   0.0       0      0  [khubd]
   (snip)
```

systemdのTASKポインタを指定して、systemdプロセスのtask_struct構造体を見てみる。
```
crash> task ffff88001fb78000
PID: 1      TASK: ffff88001fb78000  CPU: 0   COMMAND: "systemd"
struct task_struct {
  state = 1, 
  stack = 0xffff88001fb74000, 
  usage = {
    counter = 2
  }, 
  flags = 4202752, 
  ptrace = 0, 
  wake_entry = {
    next = 0x0
  }, 
  on_cpu = 0, 
  on_rq = 0, 
  prio = 120, 
  static_prio = 120, 
  normal_prio = 120, 
  rt_priority = 0, 
  sched_class = 0xffffffff81607f00, 
  se = {
    load = {
      weight = 1024, 
      inv_weight = 4194304
    }, 
    run_node = {
      rb_parent_color = 1, 
      rb_right = 0x0, 
      rb_left = 0x0
    }, 
    group_node = {
      next = 0xffff88001fb78070, 
      prev = 0xffff88001fb78070
    }, 
 (snip)
```

### 特定プロセスのfile, dentry, inode構造体の値を見てみる

```
crash> set 2469
 (snip)
crash> files
PID: 2469   TASK: ffff88001f0d4560  CPU: 0   COMMAND: "sshd"
ROOT: /    CWD: /
 FD       FILE            DENTRY           INODE       TYPE PATH
  0 ffff88001ba9c300 ffff88001db0be40 ffff88001fba6a50 CHR  /dev/null
  1 ffff88001d75c600 ffff88001db0be40 ffff88001fba6a50 CHR  /dev/null
  2 ffff88001b598100 ffff88001739a300 ffff8800173a2530 SOCK 
  3 ffff88001ccc7c00 ffff88001bf936c0 ffff880018ace7b0 SOCK 
  4 ffff8800047ba700 ffff8800172290c0 ffff880018ace530 SOCK 
  5 ffff88001a01db00 ffff88001bca0240 ffff88001a1fcf50 CHR  /dev/ptmx
  6 ffff880014451a00 ffff880004fb3480 ffff880001e11950 FIFO /run/systemd/sessions/47.ref
  7 ffff88001a093a00 ffff880017229540 ffff880018acecb0 SOCK 
```

FD=3のFILE構造体を表示する。
```
crash> struct file ffff88001ccc7c00
struct file {
  f_u = {
    fu_list = {
      next = 0xffff88001ccc7c00, 
      prev = 0xffff88001ccc7c00
    }, 
    fu_rcuhead = {
      next = 0xffff88001ccc7c00, 
      func = 0xffff88001ccc7c00
    }
  }, 
  f_path = {
    mnt = 0xffff88001fb67120, 
    dentry = 0xffff88001bf936c0
  }, 
  f_op = 0xffffffff8167aec0, 
  f_lock = {
    {
      rlock = {
        raw_lock = {
          {
            head_tail = 257, 
            tickets = {
              head = 1 '\001', 
              tail = 1 '\001'
            }
          }
        }
      }
    }
  }, 
(snip)
```

FD=3のDENTRYのアドレスを表示してみる。
```
crash> struct dentry ffff88001bf936c0
struct dentry {
  d_flags = 32, 
  d_seq = {
    sequence = 2
  }, 
  d_hash = {
    next = 0x0, 
    pprev = 0x0
  }, 
  d_parent = 0xffff88001bf936c0, 
  d_name = {
    hash = 0, 
    len = 0, 
    name = 0xffff88001bf936f8 ""
  }, 
  d_inode = 0xffff880018ace7b0, 
  d_iname = "\000oadavg\000\000_dOeSnotExist_.db\000root", 
  d_count = 1, 
  d_lock = {
    {
      rlock = {
        raw_lock = {
          {
            head_tail = 514, 
            tickets = {
              head = 2 '\002', 
              tail = 2 '\002'
            }
          }
        }
      }
    }
  }, 
  d_op = 0xffffffff8167b080, 
  d_sb = 0xffff88001fbaa800, 
  d_time = 8030481585640796672, 
  d_fsdata = 0x0, 
  d_lru = {
    next = 0xffff88001bf93740, 
    prev = 0xffff88001bf93740
  }, 
  d_u = {
    d_child = {
      next = 0xffff88001bf93750, 
(snip)
```

FD=3のINODEを表示させます。
```
crash> struct inode ffff880018ace7b0
struct inode {
  i_mode = 49663, 
  i_opflags = 0, 
  i_uid = 0, 
  i_gid = 0, 
  i_flags = 0, 
  i_acl = 0xffffffffffffffff, 
  i_default_acl = 0xffffffffffffffff, 
  i_op = 0xffffffff81d1cc40, 
  i_sb = 0xffff88001fbaa800, 
  i_mapping = 0xffff880018ace8f0, 
  i_security = 0x0, 
  i_ino = 105456, 
  {
    i_nlink = 1, 
    __i_nlink = 1
  }, 
  i_rdev = 0, 
  i_atime = {
    tv_sec = 0, 
    tv_nsec = 0
  }, 
(snip)
```

### 特定ネットワークデバイスのnet_device構造体を見てみる
まずは該当のデバイスを選定するためにnetコマンドを実行する。
```
crash> net
   NET_DEVICE     NAME   IP ADDRESS(ES)
ffff88001d413000  lo     127.0.0.1
ffff88001d6b6000  p2p1   10.0.2.15
ffff88001b7ce000  p7p1   192.168.56.1
```

p2p1デバイスのnet_device構造体を見てみる。  
nameには「p2p1で始まる値が指定されているので大丈夫そうだ。
```
crash> net_device ffff88001d6b6000
struct net_device {
  name = "p2p1\000\000\060:03.0\000\000\000", 
  pm_qos_req = {
    node = {
      prio = 0, 
      prio_list = {
        next = 0x0, 
        prev = 0x0
      }, 
      node_list = {
        next = 0x0, 
        prev = 0x0
      }
    }, 
    pm_qos_class = 0
  }, 
  name_hlist = {
    next = 0x0, 
    pprev = 0xffff88001d4125f8
  }, 
(snip)
```

### 特定デバイスのblock_device構造体を見てみる
devで一覧を表示する。
```
crash> dev
CHRDEV    NAME                 CDEV        OPERATIONS      
   1      mem            ffff88001d4c0380  memory_fops
   4      /dev/vc/0      ffffffff81d2afe0  console_fops
   4      tty            ffff88001d4f7208  tty_fops
   4      ttyS           ffff88001a273c08  tty_fops
   5      /dev/tty       ffffffff81d299c0  tty_fops
   5      /dev/console   ffffffff81d29a40  console_fops
   5      /dev/ptmx      ffffffff81d29ce0  ptmx_fops
   7      vcs            ffff88001d4c0480  vcs_fops
  10      misc           ffff88001fb63a00  misc_fops
  13      input          ffff88001fb63c80  input_fops
  14      sound          ffff88001f0a4a80  soundcore_fops
  21      sg             ffff88001a337c00  sg_fops
  29      fb             ffff88001fb63600  fb_fops
  99      ppdev          ffff88001b01eb00  pp_fops
 116      alsa           ffff88001b01e400  snd_fops
 128      ptm            ffff88001a273808  tty_fops
 136      pts            ffff88001a273a08  tty_fops
 162      raw            ffffffff81d2e840  raw_fops
 180      usb            ffff88001fb63b80  usb_fops
 188      ttyUSB         ffff88001a2ddc08  tty_fops
 189      usb_device     ffffffff81d82da0  usbdev_file_operations
 202      cpu/msr        ffff88001d541780  msr_fops
 203      cpu/cpuid      ffff88001d541880  cpuid_fops
 251      hidraw         ffffffff81d852e0  hidraw_ops
 252      usbmon         ffffffff81d82ec0  mon_fops_binary
 253      bsg            ffffffff81d24900  bsg_fops
 254      rtc            ffff88001a34f2d0  rtc_dev_fops

BLKDEV    NAME                GENDISK      OPERATIONS      
 259      blkext              (none)     
   7      loop           ffff88001a2f1800  lo_fops
   8      sd             ffff88001a3b5000  sd_fops
   9      md                  (none)     
  11      sr             ffff88001a3d1000  sr_bdops
```

キャラクタデバイスを指定してみる。   
アドレスは180番のUSBを指定してみる。以下の出力結果でnameにusbと表示されているので問題なさそうだ。
```
crash> struct cdev ffff88001fb63b80    // structが必要だった
struct cdev {
  kobj = {
    name = 0xffff88001f80ed58 "usb", 
    entry = {
      next = 0xffff88001fb63b88, 
      prev = 0xffff88001fb63b88
    }, 
    parent = 0x0, 
    kset = 0x0, 
    ktype = 0xffffffff81a41b00, 
    sd = 0x0, 
    kref = {
      refcount = {
        counter = 1
      }
    }, 
    state_initialized = 1, 
    state_in_sysfs = 0, 
    state_add_uevent_sent = 0, 
    state_remove_uevent_sent = 0, 
    uevent_suppress = 0
  }, 
  owner = 0x0, 
  ops = 0xffffffff816697e0, 
  list = {
    next = 0xffff88001fb63bd0, 
    prev = 0xffff88001fb63bd0
  }, 
  dev = 188743680, 
  count = 256
}
```

続いて、ブロックデバイス(番号:7)を指定指定する。
bd_devが確かに7になっている
```
struct gendisk {
  major = 7, 
  first_minor = 7, 
  minors = 1, 
  disk_name = "loop7\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000", 
  devnode = 0, 
  events = 0, 
  async_events = 0, 
  part_tbl = 0xffff88001d54dc40, 
  part0 = {
    start_sect = 0, 
    nr_sects = 0, 
    alignment_offset = 0, 
    discard_alignment = 0, 
    __dev = {
      parent = 0x0, 
      p = 0xffff88001a2d6540, 
      kobj = {
        name = 0xffff88001d527e80 "loop7", 
        entry = {
          next = 0xffff88001a2f6f18, 
          prev = 0xffff88001a2f1c18
        }, 
        parent = 0xffff88001d4ebc60, 
        kset = 0xffff88001f80f3c0, 
        ktype = 0xffffffff81a7fea0, 
        sd = 0xffff88001a2dcb40, 
        kref = {
          refcount = {
            counter = 6
          }
        }, 

```

### mountポイントのsuper_block構造体を表示する

まずは
```
crash> mount
    VFSMOUNT         SUPERBLK     TYPE   DEVNAME                DIRNAME
ffff88001fadc100 ffff88001f80ac00 rootfs rootfs                 /         
ffff88001b23c300 ffff88001f80b400 proc   proc                   /proc     
ffff88001b003000 ffff88001a3ec400 sysfs  sysfs                  /sys      
(snip)
```


### 構造体を出力させる。
zone
```
crash> zone
struct zone {
    long unsigned int watermark[3];
    long unsigned int percpu_drift_mark;
    long unsigned int lowmem_reserve[4];
    long unsigned int dirty_balance_reserve;
    int node;
    long unsigned int min_unmapped_pages;
    long unsigned int min_slab_pages;
    struct per_cpu_pageset *pageset;
    spinlock_t lock;
    int all_unreclaimable;
    struct free_area free_area[11];
    unsigned int compact_considered;
    unsigned int compact_defer_shift;
    struct zone_padding _pad1_;
    spinlock_t lru_lock;
    struct lruvec lruvec;
    struct zone_reclaim_stat reclaim_stat;
    long unsigned int pages_scanned;
    long unsigned int flags;
    atomic_long_t vm_stat[33];
    unsigned int inactive_ratio;
    struct zone_padding _pad2_;
    wait_queue_head_t *wait_table;
    long unsigned int wait_table_hash_nr_entries;
    long unsigned int wait_table_bits;
    struct pglist_data *zone_pgdat;
    long unsigned int zone_start_pfn;
    long unsigned int spanned_pages;
    long unsigned int present_pages;
    const char *name;
}
SIZE: 1792
```

### run queueに入っているリストを全て表示する 
```
crash> runq
CPU 0 RUNQUEUE: ffff88003fc13580
  CURRENT: PID: 1176   TASK: ffff88003648c560  COMMAND: "crash"
  RT PRIO_ARRAY: ffff88003fc13718
     [no tasks queued]
  CFS RB_ROOT: ffff88003fc13628
     [no tasks queued]
```

そのCPUで最終実行されたタイムスタンプを表示するにはtオプションを付与します。
```
crash> runq -t
 CPU 0: 1016980844734
        1016981513482  PID: 1145   TASK: ffff880036c91720  COMMAND: "crash"
```

### grepを使う
実はパイプ経由で普通に使えます
```
crash> task | grep uid
  loginuid = 1000, 
```

試してみたところheadも使えました。

### ファイルから入力させる
```
$ sudo crash -i inputfile
```

またはインタプリタから
```
crash> < inputfile
```

### ファイルに出力させる
```
crash> foreach bt > bt.all
crash> ps >> process.data
crash> kmem -i | grep SLAB > slab.pages
```


### crashコマンドの設定値を確認する
```
crash> set -v
        scroll: off (/usr/bin/less)
         radix: 10 (decimal)
       refresh: on
     print_max: 256
       console: (not assigned)
         debug: 0
          core: off
          hash: on
        silent: off
          edit: vi
      namelist: /usr/lib/debug/lib/modules/3.3.4-5.fc17.x86_64/vmlinux
      dumpfile: (null)
        unwind: off
 zero_excluded: off
     null-stop: off
           gdb: off
         scope: 0 (not set)
```

これらの設定値は.crashrcファイルなどでデフォルト設定可能である

### 構造体のサイズを確認する
たとえば、intだと
```
crash> whatis int
SIZE: 4
```

vm_area_structの場合は次の通り
```
crash> whatis vm_area_struct
struct vm_area_struct {
    struct mm_struct *vm_mm;
    long unsigned int vm_start;
    long unsigned int vm_end;
    struct vm_area_struct *vm_next;
    struct vm_area_struct *vm_prev;
    pgprot_t vm_page_prot;
    long unsigned int vm_flags;
    struct rb_node vm_rb;
    union {
        struct {...} vm_set;
        struct raw_prio_tree_node prio_tree_node;
    } shared;
    struct list_head anon_vma_chain;
    struct anon_vma *anon_vma;
    const struct vm_operations_struct *vm_ops;
    long unsigned int vm_pgoff;
    struct file *vm_file;
    void *vm_private_data;
    struct mempolicy *vm_policy;
}
SIZE: 176
```

### 画面表示文字数を超過した場合の表示方法
たとえば、psなどを出力すると出力画面が多いので1画面に収まらない。このような場合scrollを固定にしたり、解除したりできる。
```
crash> set scroll on    // スクロールを固定する(moreで表示されるイメージ)
crash> set scroll off   // スクロールを解除する(catで表示されるイメージ)
```

### サーバ情報を表示する
```
crash> mach
          MACHINE TYPE: x86_64
           MEMORY SIZE: 1 GB
                  CPUS: 1
       PROCESSOR SPEED: 2295 Mhz
                    HZ: 1000
             PAGE SIZE: 4096
   KERNEL VIRTUAL BASE: ffff880000000000
   KERNEL VMALLOC BASE: ffffc90000000000
   KERNEL VMEMMAP BASE: ffffea0000000000
      KERNEL START MAP: ffffffff80000000
   KERNEL MODULES BASE: ffffffffa0000000
     KERNEL STACK SIZE: 8192
        IRQ STACK SIZE: 16384
            IRQ STACKS:
                 CPU 0: ffff88003fc00000
 STACKFAULT STACK SIZE: 4096
     STACKFAULT STACKS:
                 CPU 0: ffff88003fc05000
DOUBLEFAULT STACK SIZE: 4096
    DOUBLEFAULT STACKS:
                 CPU 0: ffff88003fc06000
        NMI STACK SIZE: 4096
            NMI STACKS:
                 CPU 0: ffff88003fc07000
      DEBUG STACK SIZE: 8192
          DEBUG STACKS:
                 CPU 0: ffff88003fc08000
        MCE STACK SIZE: 4096
            MCE STACKS:
                 CPU 0: ffff88003fc0a000
```

### タイマーキューを確認する。
実行順でタイマーキュー及び実行される関数及びそのアドレスなどが表示されます。
```
crash> timer
TVEC_BASES[0]: ffffffff81c61ac0
  JIFFIES 
4297232386
  EXPIRES      TIMER_LIST         FUNCTION    
4297232510  ffff88003a77d7a0  ffffffff81535180  <tcp_write_timer>
4297232842  ffffffff81c66720  ffffffff810a5870  <clocksource_watchdog>
4297233004  ffff88003fc10420  ffffffff81073990  <delayed_work_timer_fn>
4297233408  ffff88003ac0f578  ffffffff81073990  <delayed_work_timer_fn>
4297233864  ffff88003d03ef18  ffffffff81073990  <delayed_work_timer_fn>
4297235008  ffffffff81d067c0  ffffffff8113d220  <sync_supers_timer_fn>
4297235008  ffff88003d03e380  ffffffff814fcb60  <dev_watchdog>
4297235200  ffffffff81a95d00  ffffffff81073990  <delayed_work_timer_fn>
4297238883  ffff88003a3ffd08  ffffffff81064d40  <process_timeout>
4297239872  ffffffff81a9f228  ffffffff81073990  <delayed_work_timer_fn>
4297246400  ffffffff81a9a3e8  ffffffff81073990  <delayed_work_timer_fn>
4297247872  ffff88003ac5cc50  ffffffff814ea700  <neigh_timer_handler>
4297251840  ffffffff81d89e40  ffffffff81073990  <delayed_work_timer_fn>
4297256064  ffff88003687c778  ffffffff812a71c0  <blk_rq_timed_out_timer>
4297265920  ffffffff81d89d60  ffffffff81073990  <delayed_work_timer_fn>
4297331200  ffffffff81a9e5e0  ffffffff81588710  <addrconf_verify>
4297368000  ffff88003fc0da20  ffffffff8102afe0  <mce_start_timer>
4297373988  ffff88003da93dd8  ffffffff81064d40  <process_timeout>
4297379840  ffff88003fc0e2f8  ffffffff810719a0  <idle_worker_timeout>
4297496576  ffff88003c2a9088  ffffffffa00e66a0  <death_by_timeout>
4297497277  ffff88003c2a92f8  ffffffffa00e66a0  <death_by_timeout>
4297674752  ffffffff81d8a0b0  ffffffff815559b0  <inet_frag_secret_rebuild>
4297674752  ffffffff81d88cd0  ffffffff814f2510  <flow_cache_new_hashrnd>
4297674752  ffffffff81d8c9d0  ffffffff815559b0  <inet_frag_secret_rebuild>
4297682944  ffffffffa011c8f0  ffffffff815559b0  <inet_frag_secret_rebuild>
4301914112  ffff88003a77d5f8  ffffffff81534640  <tcp_keepalive_timer>
4380688384  ffff88003a9ddd00  ffffffff81584b90  <ipv6_regen_rndid>
4729232309  ffff88003c2a9430  ffffffffa00e66a0  <death_by_timeout>
```

### ASCIIを表示する
ASCII文字列に変換
```
crash> ascii 62696c2f7273752f
62696c2f7273752f: /usr/lib
```

ASCII表を表示
```
crash> ascii

      0    1   2   3   4   5   6   7
    +-------------------------------
  0 | NUL DLE  SP  0   @   P   '   p
  1 | SOH DC1  !   1   A   Q   a   q
  2 | STX DC2  "   2   B   R   b   r
  3 | ETX DC3  #   3   C   S   c   s
  4 | EOT DC4  $   4   D   T   d   t
  5 | ENQ NAK  %   5   E   U   e   u
  6 | ACK SYN  &   6   F   V   f   v
  7 | BEL ETB  `   7   G   W   g   w
  8 |  BS CAN  (   8   H   X   h   x
  9 |  HT  EM  )   9   I   Y   i   y
  A |  LF SUB  *   :   J   Z   j   z
  B |  VT ESC  +   ;   K   [   k   {
  C |  FF  FS  ,   <   L   \   l   |
  D |  CR  GS  _   =   M   ]   m   }
  E |  SO  RS  .   >   N   ^   n   ~
  F |  SI  US  /   ?   O   -   o  DEL
```

### SWAP情報を表示する
```
crash> swap
FILENAME           TYPE         SIZE      USED   PCT  PRIORITY
/dev/dm-0        PARTITION    1015804k       0k   0%     0
```

### jiffiesを表示する(時刻情報)
```
crash> rd jiffies
ffffffff81ad7000:  00000001002e7d81                    .}......
crash> rd -d jiffies
ffffffff81ad7000:       4298020376 
```

### カーネルシンボルを表示する。

lオプションによりカーネルに含まれるシンボル一覧を全て表示する。grepやheadなどを使わないと画面出力で膨大になる。  
以下はksoftirqでgrepした例
```
crash> sym -l | grep -i ksoftirq
e080 (D) ksoftirqd
ffffffff8105ddb0 (t) run_ksoftirqd
ffffffff81b04c8d (t) spawn_ksoftirqd
ffffffff81bbb0f0 (t) __initcall_spawn_ksoftirqdearly
```

上記ではgrepを使いましたが、qオプションの後に文字列を指定するとその文字列が含まれているシンボルのみを表示します。
```
crash> sym -q ksoftirq  
e080 (D) ksoftirqd
ffffffff8105ddb0 (t) run_ksoftirqd
ffffffff81b04c8d (t) spawn_ksoftirqd
ffffffff81bbb0f0 (t) __initcall_spawn_ksoftirqdearly
```

### 特定のモジュールに含まれるシンボルを確認する。
lsmodで表示されるモジュールのシンボルを確認したい場合にはmオプションの後にモジュールを指定します。
```
crash> sym -m e1000
ffffffffa001a000 MODULE START: e1000
ffffffffa001a000 (t) e1000_fix_features
ffffffffa001a020 (t) e1000_setup_rctl
ffffffffa001a0d0 (t) e1000_configure_rx
ffffffffa001a310 (t) e1000_get_stats
ffffffffa001a330 (t) e1000_update_itr
ffffffffa001a440 (t) netif_tx_stop_queue
ffffffffa001a480 (t) e1000_vlan_used
ffffffffa001a4a0 (t) e1000_receive_skb
...
```

### virtualアドレスからphysicalアドレスへと変換する
vtop(virtual to physical)コマンドを利用するとvirtualアドレスからphysicalアドレスに変換します。
```
crash> vtop 80b4000
VIRTUAL     PHYSICAL        
80b4000     138b4000        

   PML: 3649d000 => 3655c067
   PUD: 3655c000 => 36ebf067
   PMD: 36ebf200 => 80000000138000e7
  PAGE: 13800000  (2MB)

      PTE         PHYSICAL  FLAGS
80000000138000e7  13800000  (PRESENT|RW|USER|ACCESSED|DIRTY|PSE|NX)

      VMA           START       END     FLAGS FILE
ffff88003b141580    28bb000    adce000 100073 

      PAGE       PHYSICAL      MAPPING       INDEX CNT FLAGS
ffffea00004e2d00 138b4000                0        0  0 20000000008000
```

### IPCに関連する情報を表示する
何も情報がないので面白くないが詳細は「help ipcs」を見た方がいいかも
```
crash> ipcs
SHMID_KERNEL     KEY      SHMID      UID   PERMS BYTES      NATTCH STATUS
(none allocated)

SEM_ARRAY        KEY      SEMID      UID   PERMS NSEMS     
(none allocated)

MSG_QUEUE        KEY      MSQID      UID   PERMS USED-BYTES   MESSAGES    
(none allocated)
```

### 16進数アドレスをページ番号に変換する
```
crash> btop 512a000
512a000: 512a
```

### evalを使って計算する
```
crash> eval 128m
hexadecimal: 8000000  (128MB)
    decimal: 134217728  
      octal: 1000000000
     binary: 00001000000000000000000000000000
 
crash> eval 128 * 1m
hexadecimal: 8000000  (128MB)
    decimal: 134217728  
      octal: 1000000000
     binary: 00001000000000000000000000000000
 
crash> eval (1 << 27)
hexadecimal: 8000000  (128MB)
    decimal: 134217728  
      octal: 1000000000
     binary: 00001000000000000000000000000000

crash> eval (1 << 32)
hexadecimal: 100000000  (4GB)
    decimal: 4294967296
      octal: 40000000000
     binary: 0000000000000000000000000000000100000000000000000000000000000000

crash> eval -b 41dc065
hexadecimal: 41dc065
    decimal: 69058661  
      octal: 407340145
     binary: 00000100000111011100000001100101
   bits set: 26 20 19 18 16 15 14 6 5 2 0 

crash> eval -lb 64g
hexadecimal: 1000000000  (64GB)
    decimal: 68719476736
      octal: 1000000000000
     binary: 0000000000000000000000000001000000000000000000000000000000000000
   bits set: 36
```

### ライブラリを現在使っているファイル所有者を特定する
```
crash> fuser /lib64/libnss3.so
 PID         TASK        COMM             USAGE
  575  ffff88003c744560  "NetworkManager  mmap 
  668  ffff88003bff0000  "gdbus"          mmap 
  692  ffff880036e1dc80  "gmain"          mmap 
  981  ffff88003aa09720  "gnome-shell"    mmap 
 1006  ffff880036ba2e40  "sshd"           mmap 
 1007  ffff880036ba5c80  "gdbus"          mmap 
 1008  ffff880036ba1720  "dconf worker"   mmap 
 1009  ffff880036ba0000  "threaded-ml"    mmap 
 1010  ffff880036f2c560  "gnome-shell"    mmap 
 1087  ffff880036e5dc80  "threaded-ml"    mmap 
 1092  ffff88003b1f8000  "sshd"           mmap 
 1094  ffff88003b1fae40  "sshd"           mmap 
 1167  ffff88003a3adc80  "sudo"           mmap 
 2126  ffff880036e58000  "dhclient"       mmap 
 2145  ffff88003aa85c80  "sendmail"       mmap 
 2167  ffff880036fc9720  "sendmail"       mmap 
 2600  ffff880036fcdc80  "sshd"           mmap 
 2602  ffff880036f2ae40  "sshd"           mmap 
```

### 一定時間毎になにか処理を実行させる。
以下の例では1秒ごとにjiffiesを出力させています。
```
crash> repeat -1 p jiffies
jiffies = $10 = 4300991909
jiffies = $11 = 4300992916
jiffies = $12 = 4300993923
jiffies = $13 = 4300994932
jiffies = $14 = 4300995940
```

### 逆アセンブルを表示する方法

```
crash> dis do_IRQ
0xffffffff815f55a0 <do_IRQ>:    push   %rbp
0xffffffff815f55a1 <do_IRQ+1>:  mov    %rsp,%rbp
0xffffffff815f55a4 <do_IRQ+4>:  sub    $0x20,%rsp
0xffffffff815f55a8 <do_IRQ+8>:  mov    %rbx,-0x20(%rbp)
0xffffffff815f55ac <do_IRQ+12>: mov    %r12,-0x18(%rbp)
0xffffffff815f55b0 <do_IRQ+16>: mov    %r13,-0x10(%rbp)
0xffffffff815f55b4 <do_IRQ+20>: mov    %r14,-0x8(%rbp)
0xffffffff815f55b8 <do_IRQ+24>: data32 data32 data32 xchg %ax,%ax
...
```

ソースコードとアセンブリの対応付けを確認する。
```
crash> dis -l do_IRQ
/usr/src/debug/kernel-3.3.fc17/linux-3.3.4-5.fc17.x86_64/arch/x86/kernel/irq.c: 182
0xffffffff815f55a0 <do_IRQ>:    push   %rbp
0xffffffff815f55a1 <do_IRQ+1>:  mov    %rsp,%rbp
0xffffffff815f55a4 <do_IRQ+4>:  sub    $0x20,%rsp
0xffffffff815f55a8 <do_IRQ+8>:  mov    %rbx,-0x20(%rbp)
0xffffffff815f55ac <do_IRQ+12>: mov    %r12,-0x18(%rbp)
0xffffffff815f55b0 <do_IRQ+16>: mov    %r13,-0x10(%rbp)
0xffffffff815f55b4 <do_IRQ+20>: mov    %r14,-0x8(%rbp)
0xffffffff815f55b8 <do_IRQ+24>: data32 data32 data32 xchg %ax,%ax
/usr/src/debug/kernel-3.3.fc17/linux-3.3.4-5.fc17.x86_64/arch/x86/kernel/irq.c: 186
0xffffffff815f55bd <do_IRQ+29>: mov    0x78(%rdi),%r12d
/usr/src/debug/kernel-3.3.fc17/linux-3.3.4-5.fc17.x86_64/arch/x86/kernel/irq.c: 182
0xffffffff815f55c1 <do_IRQ+33>: mov    %rdi,%rbx
/usr/src/debug/kernel-3.3.fc17/linux-3.3.4-5.fc17.x86_64/arch/x86/include/asm/irq_regs.h: 18
0xffffffff815f55c4 <do_IRQ+36>: mov    %gs:0xbf10,%r14
/usr/src/debug/kernel-3.3.fc17/linux-3.3.4-5.fc17.x86_64/arch/x86/kernel/irq.c: 186
0xffffffff815f55cd <do_IRQ+45>: not    %r12d
/usr/src/debug/kernel-3.3.fc17/linux-3.3.4-5.fc17.x86_64/arch/x86/include/asm/irq_regs.h: 26
0xffffffff815f55d0 <do_IRQ+48>: mov    %rdi,%gs:0xbf10
/usr/src/debug/kernel-3.3.fc17/linux-3.3.4-5.fc17.x86_64/arch/x86/kernel/irq.c: 189
0xffffffff815f55d9 <do_IRQ+57>: callq  0xffffffff8105df20 <irq_enter>
/usr/src/debug/kernel-3.3.fc17/linux-3.3.4-5.fc17.x86_64/arch/x86/kernel/irq.c: 190
0xffffffff815f55de <do_IRQ+62>: callq  0xffffffff81012110 <exit_idle>
/usr/src/debug/kernel-3.3.fc17/linux-3.3.4-5.fc17.x86_64/arch/x86/kernel/irq.c: 192
0xffffffff815f55e3 <do_IRQ+67>: mov    %r12d,%eax
/usr/src/debug/kernel-3.3.fc17/linux-3.3.4-5.fc17.x86_64/arch/x86/kernel/irq.c: 194
```

ソースコードを確認する
```
crash> dis -s do_fork
```

なお、次の環境ではsオプションは存在しなかった
```
crash version: 6.1.0-1.fc17   gdb version: 7.3.1
```

### スクロールを変更したい
デフォルトではスクロールonとなっています。画面に表示しきれないデータを制御しています。
たとえば、デフォルトからoffに変更したい場合には次のようにします。
```
crash> set scroll off
scroll: off (/usr/bin/less)
```

### 各ノードのメンバの値を求める
```
crash> tree -t rbtree -o vmap_area.rb_node vmap_area_root -s vmap_area.va_start,va_end
ffff880036ef1100
  va_start = 18446683600576839680
  va_end = 18446683600576974848
ffff88003dbff400
  va_start = 18446683600575066112
  va_end = 18446683600575086592
ffff88003e009600
  va_start = 18446683600571629568
  va_end = 18446683600571645952
...
```

xオプションを付与することで16進数で確認することができます。
```
carsh> tree -t rbtree -o vmap_area.rb_node vmap_area_root -s vmap_area.va_start,va_end -x
ffff880036ef1100
  va_start = 0xffffc90000680000
  va_end = 0xffffc900006a1000
ffff88003dbff400
  va_start = 0xffffc900004cf000
  va_end = 0xffffc900004d4000
ffff88003e009600
  va_start = 0xffffc90000188000
  va_end = 0xffffc9000018c000
...
```

# TODO
以下のtree, listについてもっとちゃんとまとめたい
- https://qiita.com/hana_shin/items/02d8da181c8287580613

# 参考URL
- 公式github
  - https://github.com/crash-utility/crash
- ドキュメントとして存在しているのは次のドキュメントぐらい?
  - http://people.redhat.com/anderson/crash_whitepaper/

