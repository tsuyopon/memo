# 概要
メモリについてまとめておく  ( proc/memory.mdにも同名ファイルが存在するので参照のこと )

メモリ関連の調べ方としては以下のような方法がある
- /proc/<pid>/maps
- /proc/meminfo
- /proc/slabinfo
- /proc/sys/fs/dentry-state
- free
- top
- slabtop 
- sar
- vmstat
- ps

各種コマンドは/proc/meminfoなどを元に算出しているのでlinuxカーネルのソースコードfs/proc/meminfo.cあたりを眺めるとわかります(codereadingレポジトリ参照)

# 調査方法など

### 基本概念
- STACK
  - プログラムなどに配置される
- malloc(glibc)
  - 128KB未満brk, sbrkシステムコールを使ってHEAPを扱う
  - 128KB以上の場合にはmmapシステムコールを使って取得する
- vmalloc
  - 論理的に連続するアドレスを確保する。
- kmalloc
  - 物理的にも連続した領域を確保する
  - スタブアロケータと呼ばれる領域はこれに該当する。inodeキャッシュ, dentryキャッシュの構造体はこれを使っている。
  - slabキャッシュにはSReclaimable(回収可能)とSUnreclaim(回収不可)なものがある

STACK、mallocはユーザープログラムで使われ、vmalloc、kmallocなどはカーネルで利用される。

### 論理アドレスから物理ページへの変換方法について
レイアウト変換は次のようにしておこなわれる。
- 1. LinearAddressとして32bitsがあり、物理アドレスの算出には先頭bitから次のようにして分割します。
  - (a) 先頭10bits(PageDirecotry offset)
  - (b) 次の10bits(PageTable offset:  PageTableはPageFileと呼ばれることもあるらしい)
  - (c) 次の12bits(Frame offset)
- 2. CR3に登録された相対アドレスはPDの先頭ポインタをさしている。
- 3. 2の先頭ポインタとPD offset(10bits)を加算して、ページディレクトリの該当アドレスからPTへの先頭ポインタを取得する。
- 4. PT先頭ポインタとPT offset(10bits)を加算して、実アドレスの先頭ポインタを取得する
- 5. 実アドレスの先頭ポインタとFrame Offset(12bits)を加算して実際の物理アドレスを取得する
```
  ------------------------------------------------------------------
   L    I    N    E    A    R         A    D    D    R    E    S    S
   ------------------------------------------------------------------
        \___/                 \___/                     \_____/ 
 
     PD offset              PT offset                 Frame offset 
     [10 bits]              [10 bits]                 [12 bits]       
          |                     |                          |
          |                     |     -----------          |        
          |                     |     |  Value  |----------|---------
          |     |         |     |     |---------|   /|\    |        |
          |     |         |     |     |         |    |     |        |
          |     |         |     |     |         |    | Frame offset |
          |     |         |     |     |         |   \|/             |
          |     |         |     |     |---------|<------            |
          |     |         |     |     |         |      |            |
          |     |         |     |     |         |      | x 4096     |
          |     |         |  PT offset|_________|-------            |
          |     |         |       /|\ |         |                   |
      PD offset |_________|-----   |  |         |          _________|
            /|\ |         |    |   |  |         |          | 
             |  |         |    |  \|/ |         |         \|/
 _____       |  |         |    ------>|_________|   PHYSICAL ADDRESS 
|     |     \|/ |         |    x 4096 |         |
| CR3 |-------->|         |           |         |
|_____|         | ....... |           | ....... |
                |         |           |         |    
 
               Page Directory          Page File

                       Linux i386 Paging
```

上記だと２段テーブルとなっていますが、３段テーブル、４段テーブルもあります。(Linear Addressのbitもそれ専用に分割されます)
- 2段テーブル(PD, PT)
  - IA-32
- 3段テーブル(PDポインタテーブル, PD, PT)
  - IA-32(PAE)   // PAE(Physical Address Extension)で64GBまで扱うことができる
- 4段テーブル(PGD, PUD, PMD, PT)
  - 64bit
  - 実はカーネル2.6.11以前では3段テーブル(PGD, PMD, PT)構成で行われていました。

PGD, PUD, PMD, PTなどはカーネルを読むときの関数やマクロなどで頻繁に出てくるので用語を押さえておく必要がある。


### メモリレイアウト(IA-32)

以下はIA-32のカーネル空間レイアウトを表します。
```
Linux uses only 4 segments:

    2 segments (code and data/stack) for KERNEL SPACE from [0xC000 0000] (3 GB) to [0xFFFF FFFF] (4 GB)
    2 segments (code and data/stack) for USER SPACE from [0] (0 GB) to [0xBFFF FFFF] (3 GB)

                               __
   4 GB--->|                |    |
           |     Kernel     |    |  Kernel Space (Code + Data/Stack)
           |                |  __|
   3 GB--->|----------------|  __
           |                |    |
           |                |    |
   2 GB--->|                |    |
           |     Tasks      |    |  User Space (Code + Data/Stack)
           |                |    |
   1 GB--->|                |    |
           |                |    |
           |________________|  __| 
 0x00000000
          Kernel/User Linear addresses
```

### メモリレイアウト(32bit)
メモリは次のようにレイアウトされることになる。Kernel Space以外は全てUser Spaceとなる。
下に伸びるのはgrow down、上に伸びるのはgrow upとなる。
```
Kernel space(1G)
Random Stack Offset(?)
引数と環境変数
Stack(最大:RLIMIT_STACK)[grow down] (~0x7FFFFFFF)
Random Map Offset(?)
Mapping Memory Segment(dynamic libraryやmallocなどのshared memory) [grow down]
Heap[grow up] (~0x10000000)
Random brk offset
BSS Segment(未初期化された変数)
Data Segment(初期化されたstatic変数)
Text Segment(ELF)(~0x00400000)
Reserved
0x00000000
```


- 参考
  - 画像などがあるのでイメージしやすい
    - http://duartes.org/gustavo/blog/post/anatomy-of-a-program-in-memory/
  - 参考になる
    - http://th0x4c.github.io/blog/2012/10/10/os-virtual-memory-map/

### メモリレイアウト(64bit)




### freeコマンドを読み解く

```
$ free -m
             total       used       free     shared    buffers     cached
Mem:           996        822        173          0        217        169
-/+ buffers/cache:        435        560
Swap:          991        147        844
```

各項目の意味は次の通り
```
total :   メモリの総量
used :    使用したメモリ寮
shard :   共有メモリ(プロセス間で共有できる領域用のメモリ)
buffers : バッファに使われているメモリ
cached :  ページキャッシュに使われているメモリ
```

Linuxでは「-/+ buffers/cache」の行が重要となる。これはMemの行を元に計算することができる。
- used
```
Mem.used - Mem.buffers - Mem.cached = 822 - 217 - 169 = 436(435とほぼ等しい) = usedと一致
```
- free: 
```
Mem.free + Mem.buffers + Mem.cahced = 173 + 217 + 169 = 559(560とほぼ一致) = freeと一致
```

以下の資料も合わせて参考にする
- http://www.math.kobe-u.ac.jp/~kodama/tips-free-memory.html


### /proc/meminfo
ネットから拝借した情報などを元に整理しておく
```
$ sudo cat /proc/meminfo 
MemTotal:        1020048 kB     # 認識している全物理メモリ
MemFree:           63484 kB     # 使われていないメモリ
Buffers:           27092 kB     # ファイルバッファとして使用されるメモリ
Cached:           540176 kB     # キャッシュメモリとして利用される。共有メモリやtmpfsもここに含まれる、SwapCachedは含まないようだ。
SwapCached:        11256 kB     # swap outした後にswap inしてそのまま残されているスワップページの容量
Active:           366220 kB     # Active = Active(anon) + Active(file)       最近アクセスした物理メモリの容量
Inactive:         488464 kB     # Inactive = Inactive(anon) + Inactive(file) 最近アクセスしていない物理メモリの容量
Active(anon):      70768 kB     # mallocで生成される領域などを表すメモリ容量。anonはアノニマスの意味
Inactive(anon):   222040 kB     # 同上。tmpfsはここに突っ込まれるらしい
Active(file):     295452 kB     # ディスクからメモリに読み込んだファイルなど、メモリを開放したくなったら、その内容をディスクに書き戻せば開放できるタイプのメモリ容量。fileはfile-backedの意味
Inactive(file):   266424 kB     # 同上
Unevictable:           0 kB     # mlockやshmlockはここに分類されるようだ
Mlocked:               0 kB     # mlockなどのシステムコールで使われているものでは(とstackoverflowが言っている)
SwapTotal:       1015804 kB     # 全体で準備されているswapメモリ容量
SwapFree:         862152 kB     # 利用可能なswapメモリ容量
Dirty:               100 kB     # ページキャッシュがdiskにsyncされていない容量。書き出す必要がある
Writeback:             0 kB     # ページキャッシュがdiskにsync中の状態の容量
AnonPages:        281016 kB     # 
Mapped:            19564 kB     # mmapシステムコールを利用してファイルやライブラリにマップするために使用しているメモリ容量(AnonPagesとMappedに分離されていることに注意)
Shmem:              5392 kB     # 共有メモリで使用している容量。tmpfsなどもここに含まれるらしい
Slab:              56084 kB     # Slab = SReclaimable + SUnreclaim つまり、SLABのメモリ使用量を表す
SReclaimable:      38708 kB     # SLABキャッシュで回収可能な項目
SUnreclaim:        17376 kB     # SLABキャッシュで回収不可能な項目
KernelStack:        2024 kB     # カーネル空間で使うスタック領域
PageTables:        27912 kB     # ページテーブルエントリで使用されている物理メモリの容量
NFS_Unstable:          0 kB
Bounce:                0 kB
WritebackTmp:          0 kB
CommitLimit:     1525828 kB     # 仮想メモリを取得できるかどうかの判断に使われる閾値（vm.overcommit_ratio×物理メモリ量）＋スワップ量）の値
Committed_AS:    1743080 kB     # 全プロセスによって確保された仮想メモリの総容量
VmallocTotal:   34359738367 kB  # vmallocで確保された空間の総容量
VmallocUsed:        8864 kB     # vmallocで割り当て済み
VmallocChunk:   34359726752 kB  # vmalloc用の連続した領域で最も大きい連続領域サイズを表す
HardwareCorrupted:     0 kB     # ECC(Error Correcting Code)対応のメモリで検出されたものであればpoioned pageとしてマークをつけた容量を表す
AnonHugePages:    110592 kB
HugePages_Total:       0
HugePages_Free:        0
HugePages_Rsvd:        0
HugePages_Surp:        0
Hugepagesize:       2048 kB
DirectMap4k:       81856 kB      # TLBロードのために存在する
DirectMap2M:      966656 kB      # TLBロードのために存在する
```

使用しているメモリ量を求める式は次のようになる。
```
Active＋Inactive＝AnonPages＋Cached＋Buffers＋SwapCached
```

一般的にはメモリは次のよう計算式となる
```
MemTotal = MemFree + File-backed(Active+Inactive) + Anonymous(Active+Inactive) + カーネル空間が使うメモリ(slab, vmalloc, pagetables)
```

ページキャッシュは次であらわされる
```
Cached＋Buffers = Active(file) + Inactive(file) + Shmem
```

以下のURLが大変参考になったので載せておく
- /proc/meminfoを考える
  - http://enakai00.hatenablog.com/entry/20110906/1315315488
- prox.txt
  - http://git.kernel.org/cgit/linux/kernel/git/torvalds/linux.git/tree/Documentation/filesystems/proc.txt?id=HEAD#n866
- SystemTapで真犯人を捕まえろ！
  - http://www.atmarkit.co.jp/ait/articles/0903/25/news131.html
- Entries in /proc/meminfo
  - http://stackoverflow.com/questions/658411/entries-in-proc-meminfo
- HardwareCorrupted, DirectMap4k, DirectMap2Mの参考
  - http://unix.stackexchange.com/questions/204286/what-does-mean-by-hardwarecorrupted-directmap4k-directmap2m-fields-in-proc-m
- what is significance of “Mlocked” in /proc/meminfo file in Linux (CentOS)
  - http://stackoverflow.com/questions/18094410/what-is-significance-of-mlocked-in-proc-meminfo-file-in-linux-centos


### カーネルスラブアロケータの統計を確認する(/proc/slabinfo)
Linux カーネルの内部で良く利用されるオブジェクト (バッファーヘッド、i-ノード、ディレクトリエントリーなど) は、それぞれ自分用のキャッシュを備えている。
slabinfoはこれらを表示します。
```
$ sudo cat /proc/slabinfo  | grep -ie mm_ -ie task_ -ie inode_ -ie "#"
# name            <active_objs> <num_objs> <objsize> <objperslab> <pagesperslab> : tunables <limit> <batchcount> <sharedfactor> : slabdata <active_slabs> <num_slabs> <sharedavail>
mqueue_inode_cache      9      9    896    9    2 : tunables    0    0    0 : slabdata      1      1      0
isofs_inode_cache      0      0    608   13    2 : tunables    0    0    0 : slabdata      0      0      0
hugetlbfs_inode_cache     14     14    576   14    2 : tunables    0    0    0 : slabdata      1      1      0
ext4_inode_cache   71451  71451    880    9    2 : tunables    0    0    0 : slabdata   7939   7939      0
sock_inode_cache     516    516    640   12    2 : tunables    0    0    0 : slabdata     43     43      0
shmem_inode_cache    852    852    640   12    2 : tunables    0    0    0 : slabdata     71     71      0
task_delay_info      288    288    112   36    1 : tunables    0    0    0 : slabdata      8      8      0
proc_inode_cache    1590   1807    624   13    2 : tunables    0    0    0 : slabdata    139    139      0
inode_cache         6994   7420    560   14    2 : tunables    0    0    0 : slabdata    530    530      0
selinux_inode_security   9158   9576     72   56    1 : tunables    0    0    0 : slabdata    171    171      0
mm_struct            126    126    896    9    2 : tunables    0    0    0 : slabdata     14     14      0
task_xstate          627    627    832   19    4 : tunables    0    0    0 : slabdata     33     33      0
task_struct          256    270   5920    5    8 : tunables    0    0    0 : slabdata     54     54      0
```

- name: キャッシュの名前
- active_objs: 現在アクティブ(使用中)なオブジェクトの数
- num_objs: 利用可能なオブジェクトの総数
- objsize:  オブジェクトのサイズ
- objperslab:  スラブ毎のオブジェクト数
- pagesperslab: スラブ毎に必要なページ数

tunables
- limit: ?
- batchcount: ?
- sharedfactor: ?

slabdata
- active_slabs: 使用中スラブ数
- num_slabs: スラブの総数
- sharedavail: 教養利用可能

- 参考
  - https://linuxjm.osdn.jp/html/LDP_man-pages/man5/slabinfo.5.html


### メモリ使用量でソートする
ps.mdと内容が重複するが載せておく

- RSSでソートする
```
$ ps aux --sort -rss
```
- VSZでソートする
```
$ ps aux --sort -vsize
```

### キャッシュの解放
- ページキャッシュのみ解放
```
# echo 1 > /proc/sys/vm/drop_caches
```
- Slabキャッシュのみ解放
```
# echo 2 > /proc/sys/vm/drop_caches
```
- ページキャッシュとSlabキャッシュを解放
```
# echo 3 > /proc/sys/vm/drop_caches
```

### vmstatで現在の稼働プロセスを定常的に確認する
SMは単位をメガバイトにしてるオプションで、5秒ごとに出力させています。
```
$ vmstat -SM 5
procs -----------memory---------- ---swap-- -----io---- --system-- -----cpu-----
 r  b   swpd   free   buff  cache   si   so    bi    bo   in   cs us sy id wa st
 1  0    147    174    216    169    0    0    87    39   68  143  0  1 99  0  0	
 0  0    147    174    216    169    0    0     0     2   61   98  0  0 99  0  0	
 0  0    147    174    216    169    0    0     0     0   62  102  0  0 100  0  0
```

### ディレクトリキャッシュを確認する
```
$ cat /proc/sys/fs/dentry-state
67102	58623	45	0	0	0
```
- 1番目: nr_dentry. 割り当てられたdentryの数
- 2番目: nr_unused. 未使用のdentry数
- 3番目: age_limit. メモリが不足している場合に
- 4番目: want_pages. システムがリクエストしたページ数
- 5番目: 予約
- 6番目: 予約

### プロセスのマッピングを確認する
pmapでわかりやすい表記で確認することができる
```
$ pmap -x `pidof layout`
20287:   ./layout
Address           Kbytes     RSS   Dirty Mode   Mapping
0000000000400000       4       4       0 r-x--  layout
0000000000600000       4       4       4 rw---  layout
000000000174d000     132       8       8 rw---    [ anon ]
0000003897600000     128     108       0 r-x--  ld-2.15.so
000000389781f000       4       4       4 r----  ld-2.15.so
0000003897820000       4       4       4 rw---  ld-2.15.so
0000003897821000       4       4       4 rw---    [ anon ]
0000003897a00000    1712     272       0 r-x--  libc-2.15.so
0000003897bac000    2048       0       0 -----  libc-2.15.so
0000003897dac000      16      12       8 r----  libc-2.15.so
0000003897db0000       8       8       8 rw---  libc-2.15.so
0000003897db2000      20      12      12 rw---    [ anon ]
00007f344d644000     412      24      24 rw---    [ anon ]
00007f344d6bf000       4       4       4 rw-s-    [ shmid=0xe8002 ]
00007f344d6c0000       4       4       4 rw---    [ anon ]
00007fffccfb6000     132      12      12 rw---    [ stack ]
00007fffccfff000       4       4       0 r-x--    [ anon ]
ffffffffff600000       4       0       0 r-x--    [ anon ]
----------------  ------  ------  ------
total kB            4644     488      96
```

/procでは上記プロセスは次のように表されることが確認できるのでpmap結果と比較してみると良い
```
$ sudo cat /proc/`pidof layout`/maps
00400000-00401000 r-xp 00000000 fd:01 933203                             /home/tsuyoshi/git/cpp/memory/mapping_layout/layout
00600000-00601000 rw-p 00000000 fd:01 933203                             /home/tsuyoshi/git/cpp/memory/mapping_layout/layout
0174d000-0176e000 rw-p 00000000 00:00 0                                  [heap]
3897600000-3897620000 r-xp 00000000 fd:01 135298                         /usr/lib64/ld-2.15.so
389781f000-3897820000 r--p 0001f000 fd:01 135298                         /usr/lib64/ld-2.15.so
3897820000-3897821000 rw-p 00020000 fd:01 135298                         /usr/lib64/ld-2.15.so
3897821000-3897822000 rw-p 00000000 00:00 0 
3897a00000-3897bac000 r-xp 00000000 fd:01 135311                         /usr/lib64/libc-2.15.so
3897bac000-3897dac000 ---p 001ac000 fd:01 135311                         /usr/lib64/libc-2.15.so
3897dac000-3897db0000 r--p 001ac000 fd:01 135311                         /usr/lib64/libc-2.15.so
3897db0000-3897db2000 rw-p 001b0000 fd:01 135311                         /usr/lib64/libc-2.15.so
3897db2000-3897db7000 rw-p 00000000 00:00 0 
7f344d644000-7f344d6ab000 rw-p 00000000 00:00 0 
7f344d6bf000-7f344d6c0000 rw-s 00000000 00:04 950274                     /SYSV00000000 (deleted)
7f344d6c0000-7f344d6c1000 rw-p 00000000 00:00 0 
7fffccfb6000-7fffccfd7000 rw-p 00000000 00:00 0                          [stack]
7fffccfff000-7fffcd000000 r-xp 00000000 00:00 0                          [vdso]
ffffffffff600000-ffffffffff601000 r-xp 00000000 00:00 0                  [vsyscall]
```


# 参考URL
- http://enakai00.hatenablog.com/entry/20110906/1315315488
