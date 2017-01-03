# 概要
メモリ関連について

### /proc/meminfo
メモリに関連する様々な統計情報を表示してくれます。
```
$ cat /proc/meminfo 
MemTotal:        1020048 kB
MemFree:          287044 kB
Buffers:           49348 kB
Cached:           270504 kB
SwapCached:        13184 kB
Active:           217712 kB
Inactive:         403200 kB
Active(anon):      28616 kB
Inactive(anon):   276512 kB
Active(file):     189096 kB
Inactive(file):   126688 kB
Unevictable:           0 kB
Mlocked:               0 kB
SwapTotal:       1015804 kB
SwapFree:         884628 kB
Dirty:                28 kB
Writeback:             0 kB
AnonPages:        290240 kB
Mapped:            19908 kB
Shmem:              4068 kB
Slab:              68340 kB
SReclaimable:      51348 kB
SUnreclaim:        16992 kB
KernelStack:        1960 kB
PageTables:        26172 kB
NFS_Unstable:          0 kB
Bounce:                0 kB
WritebackTmp:          0 kB
CommitLimit:     1525828 kB
Committed_AS:    1673092 kB
VmallocTotal:   34359738367 kB
VmallocUsed:        8864 kB
VmallocChunk:   34359726752 kB
HardwareCorrupted:     0 kB
AnonHugePages:    114688 kB
HugePages_Total:       0
HugePages_Free:        0
HugePages_Rsvd:        0
HugePages_Surp:        0
Hugepagesize:       2048 kB
DirectMap4k:       73664 kB
DirectMap2M:      974848 kB
```

### slabinfoを確認する
```
$ sudo cat /proc/slabinfo  | head -10
slabinfo - version: 2.1
# name            <active_objs> <num_objs> <objsize> <objperslab> <pagesperslab> : tunables <limit> <batchcount> <sharedfactor> : slabdata <active_slabs> <num_slabs> <sharedavail>
nf_conntrack_ffff88003c788000      0      0    312   13    1 : tunables    0    0    0 : slabdata      0      0      0
fuse_request          13     13    608   13    2 : tunables    0    0    0 : slabdata      1      1      0
fuse_inode            11     11    704   11    2 : tunables    0    0    0 : slabdata      1      1      0
nf_conntrack_expect      0      0    240   17    1 : tunables    0    0    0 : slabdata      0      0      0
nf_conntrack_ffffffff81d87840    104    104    312   13    1 : tunables    0    0    0 : slabdata      8      8      0
ext4_groupinfo_1k     64     64    128   32    1 : tunables    0    0    0 : slabdata      2      2      0
ip6_dst_cache         24     24    320   12    1 : tunables    0    0    0 : slabdata      2      2      0
UDPLITEv6              0      0   1088   15    4 : tunables    0    0    0 : slabdata      0      0      0
```

### /proc/buddyinfo
```
$ cat /proc/buddyinfo 
Node 0, zone      DMA     14     11     10      1      2      2      2      3      0      1      0 
Node 0, zone    DMA32  12280  10267   3308    870    289    131     55     18      2      2      1 
```

### /proc/vmallocinfo
```
$ sudo cat /proc/vmallocinfo  | head -10
0xffffc90000000000-0xffffc90000101000 1052672 alloc_large_system_hash+0x152/0x216 pages=256 vmalloc N0=256
0xffffc90000101000-0xffffc90000182000  528384 alloc_large_system_hash+0x152/0x216 pages=128 vmalloc N0=128
0xffffc90000182000-0xffffc90000185000   12288 mem_cgroup_create+0x1d/0x4f0 pages=2 vmalloc N0=2
0xffffc90000186000-0xffffc90000188000    8192 usb_hcd_pci_probe+0x232/0x460 phys=f0804000 ioremap
0xffffc90000188000-0xffffc9000018c000   16384 acpi_os_map_memory+0x106/0x165 phys=3fff0000 ioremap
0xffffc9000018c000-0xffffc900001cd000  266240 alloc_large_system_hash+0x152/0x216 pages=64 vmalloc N0=64
0xffffc900001cd000-0xffffc900003ce000 2101248 alloc_large_system_hash+0x152/0x216 pages=512 vmalloc N0=512
0xffffc900003ce000-0xffffc900004cf000 1052672 alloc_large_system_hash+0x152/0x216 pages=256 vmalloc N0=256
0xffffc900004cf000-0xffffc900004d4000   20480 alloc_large_system_hash+0x152/0x216 pages=4 vmalloc N0=4
0xffffc900004d4000-0xffffc900004d9000   20480 alloc_large_system_hash+0x152/0x216 pages=4 vmalloc N0=4
```

### /proc/kallsyms
Linux2.6では/proc/kallsyms、それ以前では/proc/ksymsファイルとなるようです。
Linuxカーネルでどのようなシンボルを利用しているかを確認できます。
例えば、iptables_natモジュールを確認するには次のようにします。

```
$ lsmod | egrep ^iptable_nat
iptable_nat            13383  1 
$ cat /proc/kallsyms | grep -i iptable_nat
ffffffffa0117000 t nf_nat_rule_net_exit	[iptable_nat]
ffffffffa0117020 t nf_nat_rule_net_init	[iptable_nat]
ffffffffa0118040 r nat_table	[iptable_nat]
ffffffffa0117090 t ipt_snat_checkentry	[iptable_nat]
ffffffffa01170c0 t ipt_dnat_checkentry	[iptable_nat]
ffffffffa01170f0 t ipt_snat_target	[iptable_nat]
ffffffffa0117120 t ipt_dnat_target	[iptable_nat]
ffffffffa0119038 d descriptor.44613	[iptable_nat]
ffffffffa0119000 d nf_nat_rule_net_ops	[iptable_nat]
ffffffffa01190c0 d ipt_snat_reg	[iptable_nat]
ffffffffa0119140 d ipt_dnat_reg	[iptable_nat]
ffffffffa0118090 r __func__.44614	[iptable_nat]
ffffffffa0117240 t nat_decode_session	[iptable_nat]
ffffffffa0117320 t nf_nat_fn	[iptable_nat]
ffffffffa0119060 d descriptor.44642	[iptable_nat]
ffffffffa0119088 d descriptor.44636	[iptable_nat]
ffffffffa0117510 t nf_nat_local_fn	[iptable_nat]
ffffffffa0117600 t nf_nat_out	[iptable_nat]
ffffffffa01176d0 t nf_nat_in	[iptable_nat]
ffffffffa01191c0 d nf_nat_ops	[iptable_nat]
ffffffffa0117758 t nf_nat_standalone_fini	[iptable_nat]
ffffffffa01180a3 r __func__.44637	[iptable_nat]
ffffffffa01181e0 r .LC4	[iptable_nat]
ffffffffa0117150 t nf_nat_rule_find	[iptable_nat]
ffffffffa0119280 d __this_module	[iptable_nat]
ffffffffa0117758 t cleanup_module	[iptable_nat]
ffffffffa0117210 t nf_nat_rule_cleanup	[iptable_nat]
```

特定のシステムコールなどを調べる場合にも重宝しそうです。
```
$ cat /proc/kallsyms | grep -i fanotify_init
ffffffff811bf610 T sys_fanotify_init
ffffffff81a4bc00 d event_exit__fanotify_init
ffffffff81a4bca0 d event_enter__fanotify_init
ffffffff81a4bd40 d __syscall_meta__fanotify_init
ffffffff81a4bd80 d types__fanotify_init
ffffffff81a4bd90 d args__fanotify_init
ffffffff81bb8878 t __event_exit__fanotify_init
ffffffff81bb8880 t __event_enter__fanotify_init
ffffffff81bb9880 t __p_syscall_meta__fanotify_init
```

- 参考
 - https://linuxjm.osdn.jp/html/LDP_man-pages/man5/slabinfo.5.html


### メモリマップドIOアドレスを確認する(/proc/iomem)
CPUから見た場合にメモリも入出力機器も同じようにアクセスすることができる仕組みです。
```
$ cat /proc/iomem 
00000000-0000ffff : reserved
00010000-0009fbff : System RAM
0009fc00-0009ffff : reserved
000c0000-000c7fff : Video ROM
000e2000-000ef3ff : Adapter ROM
000f0000-000fffff : reserved
  000f0000-000fffff : System ROM
00100000-3ffeffff : System RAM
  01000000-015f795e : Kernel code
  015f795f-01ad6eff : Kernel data
  01bd9000-01d8dfff : Kernel bss
3fff0000-3fffffff : ACPI Tables
e0000000-e0ffffff : 0000:00:02.0
  e0000000-e012ffff : vesafb
f0000000-f001ffff : 0000:00:03.0
  f0000000-f001ffff : e1000
f0400000-f07fffff : 0000:00:04.0
f0800000-f0803fff : 0000:00:04.0
f0804000-f0804fff : 0000:00:06.0
  f0804000-f0804fff : ohci_hcd
f0806000-f0807fff : 0000:00:0d.0
  f0806000-f0807fff : ahci
fec00000-fec003ff : IOAPIC 0
fee00000-fee00fff : Local APIC
fffc0000-ffffffff : reserved
```

ポートマップドI/Oでは、入出力用の特別なCPU命令を使用する。  
例えば、インテルのX86の場合だと、入出力専用のIN命令とOUT命令があり、入出力機器の1つのバイトに読み書きを行います。

- 参考
 - https://ja.wikipedia.org/wiki/%E3%83%A1%E3%83%A2%E3%83%AA%E3%83%9E%E3%83%83%E3%83%97%E3%83%89I/O
 - http://www.linuxmania.jp/mem_mapped_io.html
 - http://www.cs.nmsu.edu/~pfeiffer/classes/473/notes/io.html
