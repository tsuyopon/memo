# 概要
vmstatコマンドについて

# 詳細

### N秒ごとに統計情報を表示する
以下の例では2秒毎に表示しています。一般的に最初に出力される行は値がおかしいので捨ててください。
```
$ vmstat 2
procs -----------memory---------- ---swap-- -----io---- -system-- ------cpu-----
 r  b   swpd   free   buff  cache   si   so    bi    bo   in   cs us sy id wa st
 2  0   4696 119392    532 782644    0    0    49   179   41   43  0  0 99  0  0
 0  0   4696 119392    532 782656    0    0     0     0   51   53  0  0 100  0  0
 0  0   4696 119392    532 782656    0    0     0     0   49   50  0  0 100  0  0
 0  0   4696 119392    532 782656    0    0     0     0   51   55  0  0 100  0  0
```

tオプションでタイムスタンプを追加することもできます
```
$ vmstat -t 2
procs -----------memory---------- ---swap-- -----io---- -system-- ------cpu----- -----timestamp-----
 r  b   swpd   free   buff  cache   si   so    bi    bo   in   cs us sy id wa st                 JST
 2  0   4696 122368    532 782500    0    0    49   178   41   43  0  0 99  0  0 2017-12-01 21:41:14
 1  0   4696 122384    532 782500    0    0     0     9   52   64  0  0 100  0  0 2017-12-01 21:41:16
 0  0   4696 122368    532 782500    0    0     0     0   47   50  0  0 100  0  0 2017-12-01 21:41:18
```

表示情報をk(キロバイト)かm(メガバイト)に変更できる
```
// キロバイト表示
$ vmstat -S k 2
procs -----------memory---------- ---swap-- -----io---- -system-- ------cpu-----
 r  b   swpd   free   buff  cache   si   so    bi    bo   in   cs us sy id wa st
 2  0   4808 125321    544 801284    0    0    49   178   41   43  0  0 99  0  0
 0  0   4808 125304    544 801284    0    0     0     0   54   59  0  0 100  0  0

// メガバイト表示
$ vmstat -S m 2
procs -----------memory---------- ---swap-- -----io---- -system-- ------cpu-----
 r  b   swpd   free   buff  cache   si   so    bi    bo   in   cs us sy id wa st
 2  0      4    125      0    801    0    0    49   178   41   43  0  0 99  0  0
 0  0      4    125      0    801    0    0     0     0   48   51  0  0 100  0  0
```

wオプションを付与すると画面を幅広く出力します
```
$ vmstat -w 2
procs -----------------------memory---------------------- ---swap-- -----io---- -system-- --------cpu--------
 r  b         swpd         free         buff        cache   si   so    bi    bo   in   cs  us  sy  id  wa  st
 2  0         4696       122088          532       782604    0    0    49   177   41   43   0   0  99   0   0
 0  0         4696       122072          532       782604    0    0     0     0   45   48   0   0 100   0   0
```

上記フィールドの意味について
```
FIELD DESCRIPTION FOR VM MODE
   Procs
       r: The number of runnable processes (running or waiting for run time).
       b: The number of processes in uninterruptible sleep.

   Memory
       swpd: the amount of virtual memory used.
       free: the amount of idle memory.
       buff: the amount of memory used as buffers.
       cache: the amount of memory used as cache.
       inact: the amount of inactive memory.  (-a option)
       active: the amount of active memory.  (-a option)

   Swap
       si: Amount of memory swapped in from disk (/s).
       so: Amount of memory swapped to disk (/s).

   IO
       bi: Blocks received from a block device (blocks/s).
       bo: Blocks sent to a block device (blocks/s).

   System
       in: The number of interrupts per second, including the clock.
       cs: The number of context switches per second.

   CPU
       These are percentages of total CPU time.
       us: Time spent running non-kernel code.  (user time, including nice time)
       sy: Time spent running kernel code.  (system time)
       id: Time spent idle.  Prior to Linux 2.5.41, this includes IO-wait time.
       wa: Time spent waiting for IO.  Prior to Linux 2.5.41, included in idle.
       st: Time stolen from a virtual machine.  Prior to Linux 2.6.11, unknown.
```

### ディスク情報をN秒毎に表示する
以下ではsr0, sda, dm-0, dm-1といったディスク情報が２秒毎に表示されていることが確認できます
```
$ vmstat -d 2
disk- ------------reads------------ ------------writes----------- -----IO------
       total merged sectors      ms  total merged sectors      ms    cur    sec
sr0        0      0       0       0      0      0       0       0      0      0
sda    97217    930 9053532  284413  82656  41342 32755439 5654821      0    194
dm-0   96460      0 9024841  282412 115456      0 32736540 7155385      0    193
dm-1     951      0   11312    3055   1833      0   14664   80966      0      3
sr0        0      0       0       0      0      0       0       0      0      0
sda    97217    930 9053532  284413  82656  41342 32755439 5654821      0    194
dm-0   96460      0 9024841  282412 115456      0 32736540 7155385      0    193
dm-1     951      0   11312    3055   1833      0   14664   80966      0      3
sr0        0      0       0       0      0      0       0       0      0      0
sda    97217    930 9053532  284413  82656  41342 32755439 5654821      0    194
dm-0   96460      0 9024841  282412 115456      0 32736540 7155385      0    193
dm-1     951      0   11312    3055   1833      0   14664   80966      0      3
(snip)
```

```
total … 読み込み/書き込みに成功した総数
merged … グループ化した読み込み/書き込みの数
sectors … 読み込み/書き込みに成功したセクタ数
ms … 読み込み/書き込みに使用した時間(ミリ秒)
```

### メモリキャッシュのアクティブ/非アクティブ領域の内訳を確認する
通常は次のような出力となる
```
$ vmstat 1
procs -----------memory---------- ---swap-- -----io---- -system-- ------cpu-----
 r  b   swpd   free   buff  cache   si   so    bi    bo   in   cs us sy id wa st
 2  0   4696 110020    532 794088    0    0    49   176   41   43  0  0 99  0  0
 0  0   4696 110004    532 794088    0    0     0     0   53   59  0  1 99  0  0
 0  0   4696 110004    532 794088    0    0     0     0   50   48  0  1 99  0  0
```

aオプションを付与するとmemoryの箇所で上記ではbuff, cacheの箇所がinact, activeに変化していることがわかります。次の２つがわかります。
activeのメモリはすぐには利用できないので、free + inactの値が利用可能なメモリ容量だと考えるといいだろう。
- メモリキャッシュのアクティブ(利用中で、開放できない領域)
- メモリキャッシュの非アクティブ(最後に利用されてから一定時間が経過したため、すぐに廃棄できる領域)
```
$ vmstat -a 1
procs -----------memory---------- ---swap-- -----io---- -system-- ------cpu-----
 r  b   swpd   free  inact active   si   so    bi    bo   in   cs us sy id wa st
 2  0   4696 110020 644368 111580    0    0    49   176   41   43  0  0 99  0  0
 0  0   4696 110004 644368 111604    0    0     0   136   79   75  0  1 99  0  0
 0  0   4696 110004 644368 111604    0    0     0     0   53   53  0  0 100  0  0
```


### 起動時からのフォーク数を確認する
fork, vfork, cloneなどのシステムコール数が起動してからの実行数を表示する。
```
$ vmstat -f
       125046 forks
```

### 各種統計情報やメモリ情報を表示する
```
$ vmstat -s
      1016232 K total memory
       113840 K used memory
       112940 K active memory
       644308 K inactive memory
       119144 K free memory
          532 K buffer memory
       782716 K swap cache
      1482748 K total swap
         4696 K used swap
      1478052 K free swap
        32476 non-nice user cpu ticks
          212 nice user cpu ticks
        27196 system cpu ticks
      9102724 idle cpu ticks
         6294 IO-wait cpu ticks
            0 IRQ cpu ticks
         2855 softirq cpu ticks
            0 stolen cpu ticks
      4526766 pages paged in
     16377117 pages paged out
          855 pages swapped in
         1833 pages swapped out
      3762564 interrupts
      3927774 CPU context switches
   1512039232 boot time
       125100 forks
```

### ディスクに関する統計情報を表示する
```
$ vmstat -D
            4 disks 
            2 partitions 
       194628 total reads
          930 merged reads
     18089685 read sectors
       569880 milli reading
       199745 writes
        41338 merged writes
     65504765 written sectors
     12890850 milli writing
            0 inprogress IO
          390 milli spent IO
```

### パーティション情報を指定する
```
$ vmstat -p /dev/sda2 2
sda2          reads   read sectors  writes    requested writes
               96623    9039185      75664   32753490
               96623    9039185      75664   32753490
               96623    9039185      75664   32753490
```

項目の意味については
- 指定したパーティションからreadされた要求数
- 指定したパーティションからreadされたセクタ数
- 指定したパーティションからwriteされた要求数
- 指定したパーティションからwriteされたセクタ数


### スラブ情報を出力する
mオプションでスラブinfoを表示することもできる。
```
$ vmstat -m
Cache                       Num  Total   Size  Pages
ccid2_hc_tx_sock              0      0   1280     12
xfs_dqtrx                     0      0    576     14
xfs_icr                       0      0    144     28
xfs_ili                    3855   4004    152     26
xfs_inode                  9888   9888   1024     16
xfs_efd_item                160    220    400     20
xfs_da_state                 32     32    488     16
xfs_btree_cur                38     38    208     19
xfs_log_ticket              396    396    184     22
scsi_cmd_cache              324    324    448     18
kcopyd_job                    0      0   3312      9
dm_uevent                     0      0   2608     12
dm_rq_target_io               0      0    424     19
UDPLITEv6                     0      0   1152     14
UDPv6                        28     28   1152     14
tw_sock_TCPv6                32     32    256     16
TCPv6                        48     48   2048     16
cfq_queue                   374    442    232     17
bsg_cmd                       0      0    312     13
mqueue_inode_cache           18     18    896     18
hugetlbfs_inode_cache        26     26    608     13
configfs_dir_cache           92     92     88     46
dquot                         0      0    256     16
pid_namespace                 0      0   2176     15
posix_timers_cache            0      0    248     16
UDP-Lite                      0      0   1024     16
ip_fib_trie                  73     73     56     73
RAW                         187    187    960     17
UDP                          32     32   1024     16
tw_sock_TCP                  32     32    256     16
TCP                          34     34   1920     17
blkdev_queue                 34     34   1920     17
blkdev_requests            1218   1218    384     21
blkdev_ioc                   78     78    104     39
fsnotify_event_holder    121210 121210     24    170
fsnotify_event              476    476    120     34
sock_inode_cache            252    252    640     12
net_namespace                 0      0   4224      7
shmem_inode_cache           871    912    680     12
Acpi-ParseExt              5152   5152     72     56
Acpi-Namespace             4488   4488     40    102
taskstats                    24     24    328     12
proc_inode_cache           1224   1224    656     12
sigqueue                     50     50    160     25
bdev_cache                   38     38    832     19
sysfs_dir_cache           17364  17676    112     36
inode_cache               10999  12324    592     13
dentry                    44692  46599    192     21
iint_cache                    0      0     80     51
selinux_inode_security    23118  26571     80     51
buffer_head              158636 159120    104     39
vm_area_struct             8098   8280    216     18
mm_struct                    80     80   1600     20
files_cache                  96     96    640     12
signal_cache                150    210   1152     14
sighand_cache               158    165   2112     15
task_xstate                 167    266    832     19
task_struct                 181    209   2912     11
anon_vma                   4928   4928     64     64
shared_policy_node         2210   2210     48     85
numa_policy                  15     15    264     15
radix_tree_node           20739  22232    584     14
idr_layer_cache             165    165   2112     15
dma-kmalloc-8192              0      0   8192      4
dma-kmalloc-4096              0      0   4096      8
dma-kmalloc-2048              0      0   2048     16
dma-kmalloc-1024              0      0   1024     16
dma-kmalloc-512              16     16    512     16
dma-kmalloc-256               0      0    256     16
dma-kmalloc-128               0      0    128     32
dma-kmalloc-64                0      0     64     64
dma-kmalloc-32                0      0     32    128
dma-kmalloc-16                0      0     16    256
dma-kmalloc-8                 0      0      8    512
dma-kmalloc-192               0      0    192     21
dma-kmalloc-96                0      0     96     42
kmalloc-8192                 41     68   8192      4
kmalloc-4096                218    232   4096      8
kmalloc-2048                318    352   2048     16
kmalloc-1024               1219   1344   1024     16
kmalloc-512                 538    816    512     16
kmalloc-256                3230   3712    256     16
kmalloc-192                2243   2667    192     21
kmalloc-128                2238   3008    128     32
kmalloc-96                 4318   4872     96     42
kmalloc-64                37954  39808     64     64
kmalloc-32               165515 167296     32    128
kmalloc-16                50944  50944     16    256
kmalloc-8                 83456  83456      8    512
kmem_cache_node             128    128     64     64
kmem_cache                   96     96    256     16
```

カーネルがサポート対象外だと次のように表示されます。
```
$ vmstat -m
vmstat: your kernel does not support slabinfo or your permissions are insufficient
```
