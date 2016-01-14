crashを使ったカーネルダンプについて
============================

### パッケージインストール
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

パッケージをインストールしたらあとは引数なしでsudo権限でcrashコマンドを実行する。
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

どのようなコマンドがあるのかを調べるために最初はhelpを打ってみると良い。
```
crash> help
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

####プロセスを表示する。
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

### 調査するプロセスを切り替える。

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


### ネットワーク情報を表示する
```
crash> net
   NET_DEVICE     NAME   IP ADDRESS(ES)
ffff88001d413000  lo     127.0.0.1
ffff88001d6b6000  p2p1   10.0.2.15
ffff88001b7ce000  p7p1   192.168.56.1
```

### プロセスが握っているファイルを確認する
```
crash> set 3404
    PID: 3404
COMMAND: "crash"
   TASK: ffff88001f205c80  [THREAD_INFO: ffff88001d7b6000]
    CPU: 0
  STATE: TASK_RUNNING (ACTIVE)
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
crash>foreach files
crash>foreach -R files /opt
```

### 出力をファイルに残したい
リダイレクトを使うことが可能です。
```
crash> foreach files > /tmp/testtest
```

### 特定プロセスのdentry構造体の値を見てみる

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
