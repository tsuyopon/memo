# 概要
OOM Killerはシステムが実メモリと仮想メモリ空間(スワップ領域)を使い切り、必要なメモリ領域が確保できなくなった場合にプロセスを強制終了させて空きメモリを確保する仕組みです。

特徴は次の通り
- initやカーネルスレッドは対象外とのこと
- カーネル内部のbadness()またはoom_badness() (バージョンにより異なる)によって行われます。
  - badness()の評価は、メモリ空間の使用状況、CPU使用時間、動作時間、プライオリティをベースにして算出されています。その評価値はpointsに積算され返り値ろしています。
  - oom_killer_process()では選択されたプロセスに対してSIGKILLが行われています。
- 強制終了するプロセスがなるべく少なくなるように選択される
- CAP_SYS_ADMIN というケーパビリティを持っているプロセスは優遇されます (前述の oom_score_adj が -30 されます)。


# 詳細
### OOM Killer の Kill 対象プロセスの選出方法
最終スコア」が最も高いプロセスが、OOM Killer で Kill される対象となる。
- 1. ユーザー設定によるボーナス値を算出（oom_score_adj には -1000 〜 1000 の値を設定可能）
  - root ユーザーのプロセスのボーナス値 = 各プロセスの oom_score_adj 値 - 30
  - 非root ユーザーのプロセスのボーナス値 = 各プロセスの oom_score_adj 値
- 2. プロセスのコスト（メモリ使用量）を算出
  - コスト = 物理メモリ使用量 + ページテーブルサイズ + スワップ使用量
- 3. コストにボーナス値および総メモリ容量に比例した数値を加えた最終スコアを算出
  - 最終スコア = コスト + ボーナス x M / 1000 -M は OOM に関連する総メモリ量

### OOM Killerによって削除されたプロセスを確認する
/var/log/messagesにどのプロセスが落ちたのかといったログが出力されます。
```
grep -i "invoked oom-killer" /var/log/messages
```

### /var/log/messageに出力されるログについて
次のあたりを参考にすると良い
- https://stackoverflow.com/questions/9199731/understanding-the-linux-oom-killers-logs

```
[11686.040460] flasherav invoked oom-killer: gfp_mask=0x201da, order=0, oom_adj=0, oom_score_adj=0
[11686.040467] flasherav cpuset=/ mems_allowed=0
[11686.040472] Pid: 2859, comm: flasherav Not tainted 3.0.0-12-generic #20-Ubuntu
[11686.040476] Call Trace:
[11686.040488]  [<c10e1c15>] dump_header.isra.7+0x85/0xc0
[11686.040493]  [<c10e1e6c>] oom_kill_process+0x5c/0x80
[11686.040498]  [<c10e225f>] out_of_memory+0xbf/0x1d0
[11686.040503]  [<c10e6123>] __alloc_pages_nodemask+0x6c3/0x6e0
[11686.040509]  [<c10e78d3>] ? __do_page_cache_readahead+0xe3/0x170
[11686.040514]  [<c10e0fc8>] filemap_fault+0x218/0x390
[11686.040519]  [<c1001c24>] ? __switch_to+0x94/0x1a0
[11686.040525]  [<c10fb5ee>] __do_fault+0x3e/0x4b0
[11686.040530]  [<c1069971>] ? enqueue_hrtimer+0x21/0x80
[11686.040535]  [<c10fec2c>] handle_pte_fault+0xec/0x220
[11686.040540]  [<c10fee68>] handle_mm_fault+0x108/0x210
[11686.040546]  [<c152fa00>] ? vmalloc_fault+0xee/0xee
[11686.040551]  [<c152fb5b>] do_page_fault+0x15b/0x4a0
[11686.040555]  [<c1069a90>] ? update_rmtp+0x80/0x80
[11686.040560]  [<c106a7b6>] ? hrtimer_start_range_ns+0x26/0x30
[11686.040565]  [<c106aeaf>] ? sys_nanosleep+0x4f/0x60
[11686.040569]  [<c152fa00>] ? vmalloc_fault+0xee/0xee
[11686.040574]  [<c152cfcf>] error_code+0x67/0x6c
[11686.040580]  [<c1520000>] ? reserve_backup_gdb.isra.11+0x26d/0x2c0
[11686.040583] Mem-Info:
[11686.040585] DMA per-cpu:
[11686.040588] CPU    0: hi:    0, btch:   1 usd:   0
[11686.040592] CPU    1: hi:    0, btch:   1 usd:   0
[11686.040594] Normal per-cpu:
[11686.040597] CPU    0: hi:  186, btch:  31 usd:   5
[11686.040600] CPU    1: hi:  186, btch:  31 usd:  30
[11686.040603] HighMem per-cpu:
[11686.040605] CPU    0: hi:   42, btch:   7 usd:   7
[11686.040608] CPU    1: hi:   42, btch:   7 usd:  22
[11686.040613] active_anon:113150 inactive_anon:113378 isolated_anon:0
[11686.040615]  active_file:86 inactive_file:1964 isolated_file:0
[11686.040616]  unevictable:0 dirty:0 writeback:0 unstable:0
[11686.040618]  free:13274 slab_reclaimable:2239 slab_unreclaimable:2594
[11686.040619]  mapped:1387 shmem:4380 pagetables:1375 bounce:0
[11686.040627] DMA free:4776kB min:784kB low:980kB high:1176kB active_anon:5116kB inactive_anon:5472kB active_file:0kB inactive_file:0kB unevictable:0kB isolated(anon):0kB isolated(file):0kB present:15804kB mlocked:0kB dirty:0kB writeback:0kB mapped:0kB shmem:0kB slab_reclaimable:80kB slab_unreclaimable:168kB kernel_stack:96kB pagetables:64kB unstable:0kB bounce:0kB writeback_tmp:0kB pages_scanned:6 all_unreclaimable? yes
[11686.040634] lowmem_reserve[]: 0 865 1000 1000
[11686.040644] Normal free:48212kB min:44012kB low:55012kB high:66016kB active_anon:383196kB inactive_anon:383704kB active_file:344kB inactive_file:7884kB unevictable:0kB isolated(anon):0kB isolated(file):0kB present:885944kB mlocked:0kB dirty:0kB writeback:0kB mapped:5548kB shmem:17520kB slab_reclaimable:8876kB slab_unreclaimable:10208kB kernel_stack:1960kB pagetables:3976kB unstable:0kB bounce:0kB writeback_tmp:0kB pages_scanned:930 all_unreclaimable? yes
[11686.040652] lowmem_reserve[]: 0 0 1078 1078
[11686.040662] HighMem free:108kB min:132kB low:1844kB high:3560kB active_anon:64288kB inactive_anon:64336kB active_file:0kB inactive_file:0kB unevictable:0kB isolated(anon):0kB isolated(file):0kB present:138072kB mlocked:0kB dirty:0kB writeback:0kB mapped:0kB shmem:0kB slab_reclaimable:0kB slab_unreclaimable:0kB kernel_stack:0kB pagetables:1460kB unstable:0kB bounce:0kB writeback_tmp:0kB pages_scanned:61 all_unreclaimable? yes
[11686.040669] lowmem_reserve[]: 0 0 0 0
[11686.040675] DMA: 20*4kB 24*8kB 34*16kB 26*32kB 19*64kB 13*128kB 1*256kB 0*512kB 0*1024kB 0*2048kB 0*4096kB = 4784kB
[11686.040690] Normal: 819*4kB 607*8kB 357*16kB 176*32kB 99*64kB 49*128kB 23*256kB 4*512kB 0*1024kB 0*2048kB 2*4096kB = 48212kB
[11686.040704] HighMem: 16*4kB 0*8kB 1*16kB 0*32kB 0*64kB 0*128kB 0*256kB 0*512kB 0*1024kB 0*2048kB 0*4096kB = 80kB
[11686.040718] 14680 total pagecache pages
[11686.040721] 8202 pages in swap cache
[11686.040724] Swap cache stats: add 2191074, delete 2182872, find 1247325/1327415
[11686.040727] Free swap  = 0kB
[11686.040729] Total swap = 524284kB
[11686.043240] 262100 pages RAM
[11686.043244] 34790 pages HighMem
[11686.043246] 5610 pages reserved
[11686.043248] 2335 pages shared
[11686.043250] 240875 pages non-shared
[11686.043253] [ pid ]   uid  tgid total_vm      rss cpu oom_adj oom_score_adj name
[11686.043266] [ 1084]     0  1084      662        1   0       0             0 upstart-udev-br
[11686.043271] [ 1094]     0  1094      743       79   0     -17         -1000 udevd
[11686.043276] [ 1104]   101  1104     7232       42   0       0             0 rsyslogd
[11686.043281] [ 1149]   103  1149     1066      188   1       0             0 dbus-daemon
[11686.043286] [ 1165]     0  1165     1716       66   0       0             0 modem-manager
[11686.043291] [ 1220]   106  1220      861       42   0       0             0 avahi-daemon
[11686.043296] [ 1221]   106  1221      829        0   1       0             0 avahi-daemon
[11686.043301] [ 1255]     0  1255     6880      117   0       0             0 NetworkManager
[11686.043306] [ 1308]     0  1308     5988      144   0       0             0 polkitd
[11686.043311] [ 1334]     0  1334      723       85   0     -17         -1000 udevd
[11686.043316] [ 1335]     0  1335      730      108   0     -17         -1000 udevd
[11686.043320] [ 1375]     0  1375      663       37   0       0             0 upstart-socket-
[11686.043325] [ 1464]     0  1464     1333      120   1       0             0 login
[11686.043330] [ 1467]     0  1467     1333      135   1       0             0 login
[11686.043335] [ 1486]     0  1486     1333      135   1       0             0 login
[11686.043339] [ 1487]     0  1487     1333      136   1       0             0 login
[11686.043344] [ 1493]     0  1493     1333      134   1       0             0 login
[11686.043349] [ 1528]     0  1528      496       45   0       0             0 acpid
[11686.043354] [ 1529]     0  1529      607       46   1       0             0 cron
[11686.043359] [ 1549]     0  1549    10660      100   0       0             0 lightdm
[11686.043363] [ 1550]     0  1550      570       28   0       0             0 atd
[11686.043368] [ 1584]     0  1584      855       35   0       0             0 irqbalance
[11686.043373] [ 1703]     0  1703    17939     9653   0       0             0 Xorg
[11686.043378] [ 1874]     0  1874     7013      174   0       0             0 console-kit-dae
[11686.043382] [ 1958]     0  1958     1124       52   1       0             0 bluetoothd
[11686.043388] [ 2048]   999  2048     2435      641   1       0             0 bash
[11686.043392] [ 2049]   999  2049     2435      595   0       0             0 bash
[11686.043397] [ 2050]   999  2050     2435      587   1       0             0 bash
[11686.043402] [ 2051]   999  2051     2435      634   1       0             0 bash
[11686.043406] [ 2054]   999  2054     2435      569   0       0             0 bash
[11686.043411] [ 2155]     0  2155     1333      128   0       0             0 login
[11686.043416] [ 2222]     0  2222      684       67   1       0             0 dhclient
[11686.043420] [ 2240]   999  2240     2435      415   0       0             0 bash
[11686.043425] [ 2244]     0  2244     3631       58   0       0             0 accounts-daemon
[11686.043430] [ 2258]   999  2258    11683      277   0       0             0 gnome-session
[11686.043435] [ 2407]   999  2407      964       24   0       0             0 ssh-agent
[11686.043440] [ 2410]   999  2410      937       53   0       0             0 dbus-launch
[11686.043444] [ 2411]   999  2411     1319      300   1       0             0 dbus-daemon
[11686.043449] [ 2413]   999  2413     2287       88   0       0             0 gvfsd
[11686.043454] [ 2418]   999  2418     7867      123   1       0             0 gvfs-fuse-daemo
[11686.043459] [ 2427]   999  2427    32720      804   0       0             0 gnome-settings-
[11686.043463] [ 2437]   999  2437    10750      124   0       0             0 gnome-keyring-d
[11686.043468] [ 2442]   999  2442     2321      244   1       0             0 gconfd-2
[11686.043473] [ 2447]     0  2447     6490      156   0       0             0 upowerd
[11686.043478] [ 2467]   999  2467     7590       87   0       0             0 dconf-service
[11686.043482] [ 2529]   999  2529    11807      211   0       0             0 gsd-printer
[11686.043487] [ 2531]   999  2531    12162      587   0       0             0 metacity
[11686.043492] [ 2535]   999  2535    19175      960   0       0             0 unity-2d-panel
[11686.043496] [ 2536]   999  2536    19408     1012   0       0             0 unity-2d-launch
[11686.043502] [ 2539]   999  2539    16154     1120   1       0             0 nautilus
[11686.043506] [ 2540]   999  2540    17888      534   0       0             0 nm-applet
[11686.043511] [ 2541]   999  2541     7005      253   0       0             0 polkit-gnome-au
[11686.043516] [ 2544]   999  2544     8930      430   0       0             0 bamfdaemon
[11686.043521] [ 2545]   999  2545    11217      442   1       0             0 bluetooth-apple
[11686.043525] [ 2547]   999  2547      510       16   0       0             0 sh
[11686.043530] [ 2548]   999  2548    11205      301   1       0             0 gnome-fallback-
[11686.043535] [ 2565]   999  2565     6614      179   1       0             0 gvfs-gdu-volume
[11686.043539] [ 2567]     0  2567     5812      164   1       0             0 udisks-daemon
[11686.043544] [ 2571]     0  2571     1580       69   0       0             0 udisks-daemon
[11686.043549] [ 2579]   999  2579    16354     1035   0       0             0 unity-panel-ser
[11686.043554] [ 2602]     0  2602     1188       47   0       0             0 sudo
[11686.043559] [ 2603]     0  2603   374634   181503   0       0             0 flasherav
[11686.043564] [ 2607]   999  2607    12673      189   0       0             0 indicator-appli
[11686.043569] [ 2609]   999  2609    19313      311   1       0             0 indicator-datet
[11686.043573] [ 2611]   999  2611    15738      225   0       0             0 indicator-messa
[11686.043578] [ 2615]   999  2615    17433      237   1       0             0 indicator-sessi
[11686.043583] [ 2627]   999  2627     2393      132   0       0             0 gvfsd-trash
[11686.043588] [ 2640]   999  2640     1933       85   0       0             0 geoclue-master
[11686.043592] [ 2650]     0  2650     2498     1136   1       0             0 mount.ntfs
[11686.043598] [ 2657]   999  2657     6624      128   1       0             0 telepathy-indic
[11686.043602] [ 2659]   999  2659     2246      112   0       0             0 mission-control
[11686.043607] [ 2662]   999  2662     5431      346   1       0             0 gdu-notificatio
[11686.043612] [ 2664]     0  2664     3716     2392   0       0             0 mount.ntfs
[11686.043617] [ 2679]   999  2679    12453      197   1       0             0 zeitgeist-datah
[11686.043621] [ 2685]   999  2685     5196     1581   1       0             0 zeitgeist-daemo
[11686.043626] [ 2934]   999  2934    16305      710   0       0             0 gnome-terminal
[11686.043631] [ 2938]   999  2938      553        0   0       0             0 gnome-pty-helpe
[11686.043636] [ 2939]   999  2939     1814      406   0       0             0 bash
[11686.043641] Out of memory: Kill process 2603 (flasherav) score 761 or sacrifice child
[11686.043647] Killed process 2603 (flasherav) total-vm:1498536kB, anon-rss:721784kB, file-rss:4228kB
```

### カーネルによってOOM Killerの挙動を制御する
カーネルパラメータによってOOM Killer発生した時にパニックにするかどうかを決定することができます。
```
vm.panic_on_oom=0：panicしない(デフォルト)
vm.panic_on_oom=1：panicする。ただし、cgroupの制限に引っかかった場合はpanicしない。
vm.panic_on_oom=2：panicする。cgroup制限も含め問答無用でpanicする。
```

### OOM Killerを停止させる
カーネルバージョンでOOM Killerの制御方法が変わってきます。
- RHEL4 は vm.oom-kill=0 で無効化できる
- RHEL5(kernel 2.6.11) 以降はプロセス単位のみ制御可能(echo -17 > /proc/[pid]/oom_adj)
- RHEL7(kernel 2.6.36) 以降は(echo -1000 > /proc/[pid]/oom_score_adj)

### procファイルシステムでOOM Killerに関連がある項目について
- /proc/[pid]/oom_adj
  - Linux 2.6.36 以降では、 このファイルの使用は非推奨とされ、 代わりに /proc/[pid]/oom_score_adj が推奨されている。
- /proc/[pid]/oom_score_adj 
  - OOM Killerによってkillされるプロセスを制御するために用いられる
- /proc/[pid]/oom_score
  - このファイルは、OOM-killer のプロセス選択用として、カーネルが このプロセス に対して与えた現在のスコアを表示する。
  - 高いスコアは、そのプロセスがOOM-killerにより選択される可能性が高いことを意味する。 
- /proc/sys/vm/oom_dump_tasks
  - カーネルが OOM-killing を実行する際に、システム全体のタスクダンプ (カーネルスレッドを除く) を生成するかを制御する。
- /proc/sys/vm/oom_kill_allocating_task
  - このファイルは、メモリー不足 (OOM) の状況が起こった際に、 メモリー不足のきっかけとなったタスクを kill するかどうかを制御する。
- /proc/sys/vm/panic_on_oom
  - このファイルは、メモリー不足時にカーネルパニックを 起こすか起こさないかを制御する。
  - このファイルに値 1 を設定すると、 メモリー不足の状況が発生すると、カーネルは普通はパニックする。

上記では概略しか記載していないが、詳細については次のページに記載されています。
- https://linuxjm.osdn.jp/html/LDP_man-pages/man5/proc.5.html

### OOM KillerでKillさせる優先度を変更する

各プロセスは/proc/<pid>/oom_score_adjを持っているが、この中の値でOOM Killerによってプロセス削除されるかどうかの順番を決定している。
oom_score_adj の値の範囲は -1000～1000 で、低い値ほど kill されにくい。
デフォルト値は 0 で、-1000 だと kill されない。

### スタートスクリプト時などにスコアを設定する
```
# 以下の4行を追加
set_oom_score_adj () {
    [ -f /var/run/mysqld/mysqld.pid ] && \
    echo -100 > /proc/`cat /var/run/mysqld/mysqld.pid`/oom_score_adj
}

case "$1" in
    start)
        # ===< 中略 >===
        set_oom_score_adj  # <= 追加
        ;;
(snip)
```

# 参考URL
- http://wiki.bit-hive.com/north/pg/OOM%A5%AD%A5%E9%A1%BC

