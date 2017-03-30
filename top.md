# topコマンドについて
便利なメモ
- メモリ使用量でソート
  - SHIFT + M
- 実行時間順でソート
  - SHIFT + T
- 実メモリ使用量でソート
  - → shift + o を押して n を押す
- プロセスをTREE状に表示する
  - SHIFT + V
- 複数画面
  - SHIFT + A
- 更新時間を短くする 
  - → d を押して、秒数を指定（top -d1 でもOK）
- 色を付ける 
  - → B もしくは z を押す / x を押すとソートしているカラムの色だけ反転表示 

### 起動方法
代表的な起動方法について載せておく
```
$ top              # CPU使用率順にソート
$ top -a           # メモリ使用率順にソート
$ top -p [PID]     # 特定のプロセスを監視(20個まで指定できる)
$ top -d1          # 1秒ごとに更新
$ top -c           # 実行されているコマンドをフルパスで表示する
$ top -u hoge      # ユーザーを指定して表示する
$ top -b           # バッチコマンドで実行する
$ top -i           # idleなプロセスやゾンビプロセスを無視させる。
$ top -s           # セキュアモードで実行する(killやnice値の変更などをしない)
$ top -q           # 最高優先度でこのtopを実行する
$ top -n [回数]    # 指定された回数だけ実行したらtopを終了する
```

### フィールドの説明

- PR(PRiority)
  - 優先度
- NI(NIce value)
  - 相対優先度。0が基準で、負だと優先度が高く、正だと優先度が低い。
- VIRT(VIRTual image)
  - 確保された仮想メモリ全て。スワップしたメモリ使用量を含む。
- RES(RESident size)
  - スワップしていない、使用した物理メモリのサイズ。
- SHR(SHaRed memory size)
  - 他のプロセスと共有される可能性のあるメモリのサイズ
- S(process Status)
  - D: 割り込み不能
  - R: 実行中
  - S: スリープ状態
  - T: トレース中/停止中
  - Z: ゾンビ


### 表示したい項目を選択する

fを押下して画面左に全て「*」アスタリスクを付与してEnterボタンを押下する。
```
Current Fields:  AEHIOQTWKNMBCDFGJPLRSUVYZX  for window 1:Def
Toggle fields via field letter, type any other key to return 

* A: PID        = Process Id
* E: USER       = User Name
* H: PR         = Priority
* I: NI         = Nice value               // nice値。0の場合にはnice値を設定していない。
* O: VIRT       = Virtual Image (kb)       // タスクが使用している仮想メモリの総量。 コード・データ・共有ライブラリ・スワップアウトされているページが含まれる。 
* Q: RES        = Resident size (kb)       // タスクが使用しているスワップされていない物理メモリ RES=CODE+DATA
* T: SHR        = Shared Mem size (kb)     // タスクが利用している共有メモリの総量。 他のプロセスと共有される可能性のあるメモリを単純に反映している。 
* W: S          = Process Status
* K: %CPU       = CPU usage
* N: %MEM       = Memory usage (RES)
* M: TIME+      = CPU Time, hundredths    // TIMEと同じだが、精度を 1/100 秒単位まで反映させる。
* B: PPID       = Parent Process Pid
* C: RUSER      = Real user name
* D: UID        = User Id
* F: GROUP      = Group Name
* G: TTY        = Controlling Tty
* J: P          = Last used cpu (SMP)      // 最後に使用された CPU (SMP)
* P: SWAP       = Swapped size (kb)
* L: TIME       = CPU Time
* R: CODE       = Code size (kb)           // コードサイズ (kb) 実行可能コードに割かれる物理メモリの総量
* S: DATA       = Data+Stack size (kb)     // 「データ+スタック」のサイズ
* U: nFLT       = Page Fault count         // あるタスクに対して起こったメジャーページフォールトの回数
* V: nDRT       = Dirty Pages count        // 最後に書き込まれてから変更されたページの数
* Y: WCHAN      = Sleeping in Function     // スリープしている関数(epoll_waitで待たされているなど)
* Z: Flags      = Task Flags <sched.h>     // このカラムにはタスクの現在のスケジューリングフラグが 0 を省略した 16 進数で表示される
* X: COMMAND    = Command name/line
```

様々なステータス情報が表示される。
```
  PID USER      PR  NI  VIRT  RES  SHR S %CPU %MEM    TIME+   PPID RUSER     UID GROUP    TTY      P SWAP   TIME CODE DATA nFLT nDRT WCHAN     Flags   
    3 root      20   0     0    0    0 S  4.0  0.0  28:39.20     2 root        0 root     ?        0    0  28:39    0    0    0    0 run_ksoft .42.8.4.
28029 nobody    20   0  276m  38m 3400 S  4.0  3.9  29:01.58 28028 nobody     99 nobody   pts/1    0    0  29:01 4860 186m    2    0 epoll_wai ..4.21..
 8657 tsuyoshi  20   0  129m 1996  860 S  0.3  0.2   0:00.96  8655 tsuyoshi 1000 tsuyoshi ?        0    0   0:00  536  892    0    0 poll_sche ..4.214.
 9474 root      20   0     0    0    0 S  0.3  0.0   0:00.07     2 root        0 root     ?        0    0   0:00    0    0    0    0 worker_th .42.8.6.
...
```

### 選択してソートを切り替える
Shift + Oを押下したら以下の画面が現れるのであとはソートしたいのを押下するPIDでソートしたければAを押す。つまりShift +O, Aとなる。
```
Current Sort Field:  A  for window 1:Def
Select sort field via field letter, type any other key to return 

* A: PID        = Process Id
  b: PPID       = Parent Process Pid
  c: RUSER      = Real user name
  d: UID        = User Id
  e: USER       = User Name
  f: GROUP      = Group Name
  g: TTY        = Controlling Tty
  h: PR         = Priority
  i: NI         = Nice value
  j: P          = Last used cpu (SMP)
  k: %CPU       = CPU usage
  l: TIME       = CPU Time
  m: TIME+      = CPU Time, hundredths
  n: %MEM       = Memory usage (RES)
  o: VIRT       = Virtual Image (kb)
  p: SWAP       = Swapped size (kb)
  q: RES        = Resident size (kb)
  r: CODE       = Code size (kb)
  s: DATA       = Data+Stack size (kb)
  t: SHR        = Shared Mem size (kb)
  u: nFLT       = Page Fault count
  v: nDRT       = Dirty Pages count
  w: S          = Process Status
  x: COMMAND    = Command name/line
  y: WCHAN      = Sleeping in Function
  z: Flags      = Task Flags <sched.h>

Note1:
  If a selected sort field can't be
  shown due to screen width or your
  field order, the '<' and '>' keys
  will be unavailable until a field
  within viewable range is chosen.

Note2:
  Field sorting uses internal values,
  not those in column display.  Thus,
  the TTY & WCHAN fields will violate
  strict ASCII collating sequence.
  (shame on you if WCHAN is chosen)
```

### フィールド情報を見る
fを押すと次の画面を見ることができる
```
Current Fields:  AEHIOQTWKNMbcdfgJplrsuvyzX  for window 1:Def
Toggle fields via field letter, type any other key to return 

* A: PID        = Process Id
* E: USER       = User Name
* H: PR         = Priority
* I: NI         = Nice value
* O: VIRT       = Virtual Image (kb)
* Q: RES        = Resident size (kb)
* T: SHR        = Shared Mem size (kb)
* W: S          = Process Status
* K: %CPU       = CPU usage
* N: %MEM       = Memory usage (RES)
* M: TIME+      = CPU Time, hundredths
  b: PPID       = Parent Process Pid
  c: RUSER      = Real user name
  d: UID        = User Id
  f: GROUP      = Group Name
  g: TTY        = Controlling Tty
* J: P          = Last used cpu (SMP)
  p: SWAP       = Swapped size (kb)
  l: TIME       = CPU Time
  r: CODE       = Code size (kb)
  s: DATA       = Data+Stack size (kb)
  u: nFLT       = Page Fault count
  v: nDRT       = Dirty Pages count
  y: WCHAN      = Sleeping in Function
  z: Flags      = Task Flags <sched.h>
* X: COMMAND    = Command name/line

Flags field:
  0x00000001  PF_ALIGNWARN
  0x00000002  PF_STARTING
  0x00000004  PF_EXITING
  0x00000040  PF_FORKNOEXEC
  0x00000100  PF_SUPERPRIV
  0x00000200  PF_DUMPCORE
  0x00000400  PF_SIGNALED
  0x00000800  PF_MEMALLOC
  0x00002000  PF_FREE_PAGES (2.5)
  0x00008000  debug flag (2.5)
  0x00024000  special threads (2.5)
  0x001D0000  special states (2.5)
  0x00100000  PF_USEDFPU (thru 2.4)
```

### CPUで切り替える
"1"を押下するとCPUが各CPU状態に切り替わる。(よーく見ると画面が少しだけ変わっていることが確認できる)

### ヘルプを見る
hを押下するとヘルプが表示される。とりあえずhだけでも覚えておくべし。。。
```
Help for Interactive Commands - procps version 3.2.8
Window 1:Def: Cumulative mode Off.  System: Delay 3.0 secs; Secure mode Off.

  Z,B       Global: 'Z' change color mappings; 'B' disable/enable bold
  l,t,m     Toggle Summaries: 'l' load avg; 't' task/cpu stats; 'm' mem info
  1,I       Toggle SMP view: '1' single/separate states; 'I' Irix/Solaris mode

  f,o     . Fields/Columns: 'f' add or remove; 'o' change display order
  F or O  . Select sort field
  <,>     . Move sort field: '<' next col left; '>' next col right
  R,H     . Toggle: 'R' normal/reverse sort; 'H' show threads
  c,i,S   . Toggle: 'c' cmd name/line; 'i' idle tasks; 'S' cumulative time
  x,y     . Toggle highlights: 'x' sort field; 'y' running tasks
  z,b     . Toggle: 'z' color/mono; 'b' bold/reverse (only if 'x' or 'y')
  u       . Show specific user only
  n or #  . Set maximum tasks displayed

  k,r       Manipulate tasks: 'k' kill; 'r' renice
  d or s    Set update interval
  W         Write configuration file
  q         Quit
          ( commands shown with '.' require a visible task display window ) 
Press 'h' or '?' for help with Windows,
```

# 参考URL
- Manpage of Top
  - フィールドの説明などはここに載っています。
  - https://linuxjm.osdn.jp/html/procps/man1/top.1.html
- https://orebibou.com/2015/07/top%E3%82%B3%E3%83%9E%E3%83%B3%E3%83%89%E3%81%A7%E8%A6%9A%E3%81%88%E3%81%A6%E3%81%8A%E3%81%8D%E3%81%9F%E3%81%84%E4%BD%BF%E3%81%84%E6%96%B914%E5%80%8B/
